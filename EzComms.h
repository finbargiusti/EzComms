#include <string>
#include <arpa/inet.h>

class EzComm {
	public:
		EzComm();
		int EzSend(std::string stdinput);
		std::string EzRecv();
	private:
		int currSocket;	
};

class Connection {
	public:
		Connection(int type);	
};
