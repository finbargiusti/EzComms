#include "EzComms.h"
#include <iostream>

using namespace ezComms;

int main() {
	setupConn(server);
	Socket pipe;
	std::string nig = pipe.recv() + "\n";	
	printf("%s\n", nig.c_str() );
}