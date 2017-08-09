#include "EzComms.h"
#include <iostream>
#include <arpa/inet.h>

int main() {
	Connection connection(0);
	EzComm pipe;
	std::string nig = pipe.EzRecv();	
	printf("%s\n", nig.c_str());
}