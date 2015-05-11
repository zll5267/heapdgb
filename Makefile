# Make file for the heapdbg project
# TODOs means need improve
SRC_DIR := webserver mallocwrapper core

#=======================================
# begin prepare the general variable
#=======================================
#-------begin system command part-------
RM = rm
MKDIR = mkdir -p
#-------end system command part---------

#-------begin source input part--------
SOURCES := $(foreach srcdir, ${SRC_DIR}, $(wildcard ${srcdir}/*.cc))
OUTDIR := out/# the '/' must be here if not empty
OBJECTS := $(addprefix ${OUTDIR},$(patsubst %.cc, %.o, ${SOURCES}))
TARGET := ${OUTDIR}libmallocwrapper.so
#-------end source input part----------
#create the out dir
#TODO: here should check the value of OUTDIR, must end with '/'
ifneq (${OUTDIR},)
    $(foreach srcdir,$(addprefix ${OUTDIR}, ${SRC_DIR}),$(shell ${MKDIR} ${srcdir}))
endif
#-------begin complier part-------------
CXX = g++
CXXFLAGS = -g -Wall -fPIC

INCLUDES = -I ./util -I ./webserver -I ./mallocwrapper -I ./core
LIBS = -ldl -lpthread
#-------end complier part--------------

#=======================================
# end prepare the general variable
#=======================================
#=============================================
# begin general part, this part can be reused
#=============================================
#default target
all: ${OBJECTS}
	${CXX} -shared -fPIC ${OBJECTS} ${LIBS} -o ${TARGET}

$(filter %.o, ${OBJECTS}): ${OUTDIR}%.o: %.cc
	${CXX} ${INCLUDES} -c ${CXXFLAGS}  $< -o $@
#auto dependency
${OUTDIR}%.d: %.cc
	@set -e; rm -f $@; \
	${CXX} -MM -MT $*.o ${INCLUDES} $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@: ,g' $@.$$$$ > $@; \
	${RM} $@.$$$$

sinclude $(OBJECTS:.o=.d)
# clean
.PHONY : distclean clean cleantarget cleand
distclean: clean cleand
	-${RM} -rf ${OUTDIR}
clean: cleantarget
	-${RM} -f ${OBJECTS}
cleantarget:
	-${RM} -f ${OUTDIR}${TARGET}
cleand:
	-${RM} -f $(patsubst %.o,%.d,${OBJECTS})
#============================================
# end general part, this part can be reused
#============================================
