#include <iostream>
#include <stdlib.h>

int main(int argc, char* argv[])
{
	std::cout << "begin main" << std::endl;
    int *ip = new int;
	std::cout << "ip:" << ip << std::endl;
    char *p = (char*)malloc(10);
	std::cout << "p:" << (long*)p << std::endl;
	free(ip);
}
