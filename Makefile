

CORE_SOURCES = core/WebServerThread.cc

CORE_OBJECTS = $(patsubst %.cc,%.o,${CORE_SOURCES})
WRAPPER_OBJECTS =
WEBSERVER_OBJECTS =
#=======================================
# begin prepare the general variable
#=======================================
#-------begin system command part-------
RM = rm
#-------end system command part---------
#-------begin complier part-------------
CXX = g++
CXXFLAGS = -g -Wall

INCLUDES = -I ./util -I ./webserver -I ./mallocwrapper -I ./core
LIBS =
#-------end complier part--------------
#-------begin source input part--------
SOURCES = ${CORE_SOURCES}
OBJECTS = ${CORE_OBJECTS}
TARGET =
OUTDIR =
#-------end source input part----------
#=======================================
# end prepare the general variable
#=======================================
#=============================================
# begin general part, this part can be reused
#=============================================
#default target
all: ${OBJECTS}

$(filter %.o, ${OBJECTS}): %.o: %.cc
	${CXX} ${INCLUDES} -c ${CXXFLAGS}  $< -o $@
#auto dependency
%.d: %.cc
	set -e; rm -f $@; \
	${CXX} -MM -MT $*.o ${INCLUDES} $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@: ,g' $@.$$$$ > $@; \
	${RM} $@.$$$$

sinclude $(OBJECTS:.o=.d)
# clean
.PHONY : distclean clean cleantarget
distclean: clean
	-${RM} $(OBJECTS:.o=.d)
clean: cleantarget
	-${RM} ${OBJECTS}
cleantarget:
	-${RM} ${TARGET}
#============================================
# end general part, this part can be reused
#============================================
## only for test ##
cleancore:
	-${RM} ${CORE_OBJECTS}
cleanwrapper:
	-${RM} ${WRAPPER_OBJECTS}
cleanwebserver:
	-${RM} ${WEBSERVER_OBJECTS}
