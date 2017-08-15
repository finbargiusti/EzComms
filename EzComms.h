#pragma once

#include <string>
#include <arpa/inet.h>

namespace ezComms {
	enum ConnectionType {server, client};

	void setupConn(ConnectionType type);

	class Socket {
		public:
			Socket();
			int send(const char *stdinput, uint32_t stdinlen);
			std::string recv();
		private:
			int sock_fd;
	};
};