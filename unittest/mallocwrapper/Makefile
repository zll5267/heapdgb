##targets:lib test clean run
CC = g++
CFLAGS = -g -Wall
LIBS = -ldl -lpthread
INCLUDES = -I ../../util/
SOURCES = ../../mallocwrapper/MallocInfo.cc ../../mallocwrapper/Wrapper.cc

lib: ${SOURCES}
	${CC} -shared -fPIC ${CFLAGS} ${INCLUDES}  $^ ${LIBS} -o libmallocwrapper.so

test: WrapperTest.cc
	${CC} ${CFLAGS} ${INCLUDES} -rdynamic $^ ${LIBS} -o wrapper
clean:
	rm -f libmallocwrapper.so wrapper
run:
	LD_PRELOAD=./libmallocwrapper.so ./wrapper
