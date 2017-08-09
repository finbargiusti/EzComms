all:
	g++ -g testsend.cpp -o testsend EzComms.cpp -Wall -Wextra
	g++ -g testreceive.cpp -o testreceive EzComms.cpp -Wall -Wextra