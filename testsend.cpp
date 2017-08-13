#include "EzComms.h"
#include <iostream>

int main() {
	EzComm conn(client);
	EzComm::socket pipe();
	std::string stdinput;
	getline(std::cin, stdinput);
	pipe.send(stdinput.c_str(), stdinput.size());
}