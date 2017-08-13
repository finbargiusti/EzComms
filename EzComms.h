#include <string>
#include <arpa/inet.h>

enum ConnectionType {server, client};

class EzComm {
	public:
		EzComm(ConnectionType type);
		class socket {
			public:
				socket();
				int send(const char *stdinput, uint32_t stdinlen);
				std::string recv();
			private:
				int new_sock;
		};
	private:
		static int currSocket;	
		static int connType;
		static int socketNumber;
};