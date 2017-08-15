#include "EzComms.h"
#include <iostream>

using namespace ezComms;

int main() {
	setupConn(server);
	Socket pipe;
	while (true) {
		std::string ing = pipe.recv();
		printf("%s\n", ing.c_str());
		pipe.send(ing.c_str(), (uint32_t)ing.size());
		//std::string stdin;
		//getline(std::cin, stdin);
		//pipe.send(stdin.c_str(), (uint32_t)stdin.size());
	}
}