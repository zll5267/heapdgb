###targets: test clean run
#http://127.0.0.1:7676/heapdbg
CC = g++
CFLAGS = -g -Wall
INCLUDES = -I ../../util/ -I ../../webserver
SOURCES = ../../webserver/Resolver.cc ../../webserver/WebRequestHandler.cc \
          ../../webserver/WebServer.cc WebServerTest.cc

test: $(SOURCES)
	${CC} ${CFLAGS} ${INCLUDES} $^ -o webServer
clean:
	rm -f webServer
run:
	./webServer
