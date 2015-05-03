# heapdgb
help to debug the memory leak problem, now still under development, function is still limited.
overview

use the library injection method to capture the malloc invoke.
and save the malloc information, such as the size, stack trace info,...
also capture the free where release the malloc information saved before.
so the system has the memory information about allocated but freed.
detail see the reference.

a webserve will be started, so through a browser we can see the memory information, real time.

reference:
	C++ Memory Leak Finder   http://www.codeproject.com/Articles/393957/Cplusplus-Memory-Leak-Finder
	Computer Systems A Programmer's Perspective(second edition)

