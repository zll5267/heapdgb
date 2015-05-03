#for WebServerTest.cc
#g++ -I ../util/ Resolver.cc WebRequestHandler.cc WebServer.cc WebServerTest.cc -o webServer
#http://127.0.0.1:7676/heapdbg
CC = g++
CFLAGS = -g
INCLUDES = -I ../util/
SOURCES = Resolver.cc WebRequestHandler.cc WebServer.cc WebServerTest.cc

test: $(SOURCES)
	${CC} ${CFLAGS} ${INCLUDES} $^ -o webServer
clean:
	rm webServer
