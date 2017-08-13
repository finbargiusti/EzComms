#include "EzComms.h"
#include <iostream>

using namespace ezComms;

int main() {
	setupConn(client);
	Socket pipe;
	std::string stdinput;
	getline(std::cin, stdinput);
	pipe.send(stdinput.c_str(), stdinput.size());
}