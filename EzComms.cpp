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

using namespace std;

int sockfd;

void *get_in_addr(struct sockaddr *sa)
{
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }
    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

EzComm::EzComm(ConnectionType type) {
    if (type == server) {// is server 
        struct addrinfo hints, *res;

        memset(&hints, 0, sizeof hints);
        hints.ai_family = AF_UNSPEC;
        hints.ai_socktype = SOCK_STREAM;
        hints.ai_flags = AI_PASSIVE;

        getaddrinfo(NULL, "1337", &hints, &res);

        sockfd = ::socket(res->ai_family, res->ai_socktype, res->ai_protocol);

        bind(sockfd, res->ai_addr, res->ai_addrlen);

        listen(sockfd, 5);
        connType = 0;
    } else if (type == client) {// is client
        connType = 1;
    } else {// You fucked up
        throw out_of_range("Incompatible type ID");
    }
}

EzComm::socket::socket() {
    if (connType == 1) {
        if (socketNumber != 0) {
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
                if ((new_sock = ::socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1) {
                    continue;
                }

                if (connect(new_sock, p->ai_addr, p->ai_addrlen) == -1) {
                    close(new_sock);
                    continue; }

                break;
            }

            inet_ntop(p->ai_family, get_in_addr((struct sockaddr *)p->ai_addr),
                    s, sizeof s);

            freeaddrinfo(servinfo);
        } else {
            throw "Client can only have one socket!";
        }
    } else if (connType == 0) {
        char s[INET6_ADDRSTRLEN];
        struct sockaddr_storage their_addr;
        socklen_t addr_size = sizeof their_addr; 
        new_sock = accept(sockfd, (struct sockaddr *)&their_addr, &addr_size);
    }
}

std::string EzComm::socket::recv() {
    char bytesBuf[4];
    read(currSocket, bytesBuf, 4);
    uint32_t bytesToRecv = *(uint32_t *)bytesBuf; 
    cout << "Received " << bytesToRecv << " bytes" << endl;
    int bytesRemain = bytesToRecv;
    string outp;
    while (bytesRemain > 0) {
        char buf[bytesRemain];
        int bytesInMsg = read(currSocket, buf, bytesRemain);
        if (bytesInMsg != -1) {
            bytesRemain -= bytesInMsg;
            outp += buf;
        } else {
            perror("oh shit");
            return NULL;
        }
    }
    return(outp);
}

int EzComm::socket::send(const char *stdinput, uint32_t stdinlen) {
    cout << "Sending " << stdinlen << " bytes" << endl;
    if (write(currSocket, (char *)&stdinlen, 4) != -1) {
        int bytesRemain = stdinlen;
        const char *buffer = stdinput;
        while (bytesRemain > 0) {
            bytesRemain = write(currSocket, buffer+(stdinlen - bytesRemain), bytesRemain);
            if (bytesRemain == -1) {
                perror("Uh-Oh");
            }
        }
        return 0;
    } else {
        return 1;
    }
}