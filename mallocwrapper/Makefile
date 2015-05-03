#for Wrapper.cc
#g++ -g -I ../util/ -shared -fPIC MallocInfo.cc Wrapper.cc -o libmallocwrapper.so -ldl -lpthread
#g++ -rdynamic -g WrapperTest.cc -o wrapper
#LD_PRELOAD=./libmallocwrapper.so ./wrapper
CC = g++
CFLAGS = -g
LIBS = -ldl -lpthread
INCLUDES = -I ../util/
SOURCES = MallocInfo.cc Wrapper.cc

lib: ${SOURCES}
	${CC} -shared -fPIC ${CFLAGS} ${INCLUDES} ${LIBS} $^ -o libmallocwrapper.so

test: WrapperTest.cc
	${CC} ${CFLAGS} ${INCLUDES} ${LIBS} -rdynamic $^ -o wrapper
clean:
	rm libmallocwrapper.so wrapper
