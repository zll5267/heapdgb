#targets:lib test clean run
#http://127.0.0.1:7676/heapdbg
CC = g++
CFLAGS = -g -Wall
LIBS = -ldl -lpthread
INCLUDES = -I ../../util/ -I ../../webserver -I ../../mallocwrapper -I ./
SOURCES = ../../core/WebServerThread.cc ../../core/MallocWrapperRequestHandler.cc \
		  ../../webserver/WebRequestHandler.cc \
          ../../webserver/WebServer.cc ../../webserver/Resolver.cc \
          ../../mallocwrapper/MallocInfo.cc \
          ../../mallocwrapper/Wrapper.cc

lib: ${SOURCES}
	${CC} ${CFLAGS} -shared -fPIC ${INCLUDES} ${SOURCES} ${LIBS} -o libmallocwrapper.so

test: WrapperTest.cc
	${CC} ${CFLAGS} -rdynamic $^ -o test
.PHONY : clean
clean:
	rm -f libmallocwrapper.so test
run:
	LD_PRELOAD=./libmallocwrapper.so ./test
