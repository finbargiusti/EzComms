#include "EzComms.h"
#include <iostream>

using namespace ezComms;

int main() {
	setupConn(client);
	Socket pipe;
	std::string stdinput;
	getline(std::cin, stdinput);
	uint32_t stinlen = (uint32_t)stdinput.size();
	std::cout << stinlen << std::endl;
	pipe.send(stdinput.c_str(), stinlen);
}