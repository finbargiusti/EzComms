#include "EzComms.h"
#include <arpa/inet.h>
#include <list>
#include <iostream>

int main() {
	Connection connection(1);
	while (true) {
		EzComm pipe;
		std::string stdinput;
		std::cin >> stdinput;
		pipe.EzSend(stdinput);
	}
}