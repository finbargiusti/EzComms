#pragma once

#include <string>
#include <arpa/inet.h>

namespace ezComms {
	enum ConnectionType {server, client};

	int sockfd;

	int currSocket;	
	int connType;
	int socketNumber;

	void setupConn(ConnectionType type);

	class Socket {
		public:
			Socket();
			int send(const char *stdinput, uint32_t stdinlen);
			std::string recv();
		private:
			int new_sock;
	};
};