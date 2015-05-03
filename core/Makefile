#for Wrapper.cc
#g++ -g -I ../webserver -I ../util/ -I ../mallocwrapper/ -shared -fPIC WebServerThread.cc MallocWrapperRequestHandler.cc ../webserver/WebRequestHandler.cc ../webserver/WebServer.cc ../webserver/Resolver.cc ../mallocwrapper/MallocInfo.cc ../mallocwrapper/Wrapper.cc -o libmallocwrapper.so -ldl -lpthread
#g++ -rdynamic -g ../mallocwrapper/WrapperTest.cc -o wrapper
#LD_PRELOAD=./libmallocwrapper.so ./test

CC = g++
CFLAGS = -g
LIBS = -ldl -lpthread
INCLUDES = -I ../util/ -I ../webserver -I ../mallocwrapper -I ./
SOURCES = WebServerThread.cc MallocWrapperRequestHandler.cc ../webserver/WebRequestHandler.cc ../webserver/WebServer.cc ../webserver/Resolver.cc ../mallocwrapper/MallocInfo.cc ../mallocwrapper/Wrapper.cc

lib: ${SOURCES}
	${CC} ${CFLAGS} -shared -fPIC ${INCLUDES} ${SOURCES} ${LIBS} -o libmallocwrapper.so

test: WrapperTest.cc
	${CC} ${CFLAGS} -rdynamic $^ -o test
clean:
	rm libmallocwrapper.so test
