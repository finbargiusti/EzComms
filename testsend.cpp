#include "EzComms.h"
#include <iostream>

using namespace ezComms;

int main() {
	setupConn(client);
	Socket pipe;
	while (true) {
		std::string stdinput;
		getline(std::cin, stdinput);
		pipe.send(stdinput.c_str(),(uint32_t)stdinput.size());
		printf("%s\n",pipe.recv().c_str());
	}
}