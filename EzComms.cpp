#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <stdexcept>
#include <signal.h>
#include "EzComms.h"

int sockfd;

void *get_in_addr(struct sockaddr *sa)
{
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }
    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

Connection::Connection(int type) {
    if (type == 0) {// is server 
        struct addrinfo hints, *res;

        memset(&hints, 0, sizeof hints);
        hints.ai_family = AF_UNSPEC;
        hints.ai_socktype = SOCK_STREAM;
        hints.ai_flags = AI_PASSIVE;

        getaddrinfo(NULL, "1337", &hints, &res);

        sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);

        bind(sockfd, res->ai_addr, res->ai_addrlen);

        listen(sockfd, 5);
    } else if (type == 1) {// is client
        struct addrinfo hints, *servinfo, *p;
        char s[INET6_ADDRSTRLEN];
        int rv;

        memset(&hints, 0, sizeof hints);
        hints.ai_family = AF_UNSPEC;
        hints.ai_socktype = SOCK_STREAM;
        hints.ai_flags = AI_PASSIVE;

        if ((rv = getaddrinfo(NULL, "1337", &hints, &servinfo)) != 0) {
        }

        for(p = servinfo; p != NULL; p = p->ai_next) {
            if ((sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1) {
                continue;
            }

            if (connect(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
                close(sockfd);
                continue; }

            break;
        }

        inet_ntop(p->ai_family, get_in_addr((struct sockaddr *)p->ai_addr),
                s, sizeof s);

        freeaddrinfo(servinfo);
    } else {// You fucked up
        throw std::out_of_range("Incompatible type ID");
    }
}


EzComm::EzComm() {
    char s[INET6_ADDRSTRLEN];
    struct sockaddr_storage their_addr;
    socklen_t addr_size = sizeof their_addr; 
    currSocket = accept(sockfd, (struct sockaddr *)&their_addr, &addr_size);
    std::cout << "Connection from: " << inet_ntop(their_addr.ss_family,((struct sockaddr_in*)(struct sockaddr *)&their_addr), s, sizeof s) << '\n';
}

std::string EzComm::EzRecv() {
    char bytesBuf[4];
    recv(currSocket, bytesBuf, 4, 0);
    std::uintptr_t bytesToRecv = (uintptr_t)bytesBuf; 
    int bytesRemain = bytesToRecv;
    std::string outp;
    while (bytesRemain > 0) {
        char buf[100];
        int bytesInMsg = recv(currSocket, buf, 100, 0);
        if (bytesInMsg != -1) {
            bytesRemain -= bytesInMsg;
            outp += buf;
        } else {
            break;
        }
    }
    return(outp);
}

int EzComm::EzSend(std::string stdinput) {
    size_t stdinlen = stdinput.size(); 
    if (write(currSocket, (char *)&stdinlen, 4) != -1) {
        return 0;
    } else {
        return 1;
    }
}