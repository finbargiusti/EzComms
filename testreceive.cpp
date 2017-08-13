#include "EzComms.h"
#include <iostream>

int main() {
	EzComm pipe(server);
	std::string nig = pipe.recv() + "\n";	
	printf("%s\n", nig.c_str() );
}