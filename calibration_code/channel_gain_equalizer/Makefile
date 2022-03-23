Target		:= main
CC			:= g++
CXXFLAGS	:= -std=c++11 -O2 -g -Wall

INC			:= -I./include -I${ROOTSYS}/include
LIBS		:= $(shell root-config --glibs)

SOURCES		:= $(notdir $(wildcard src/*.cpp))
OBJECTS		:= $(patsubst %.cpp, %.o, ${SOURCES})
OBJ			:= $(addprefix obj/, ${OBJECTS})

obj/%.o:src/%.cpp
	${CC} ${CXXFLAGS} -o $@ -c $^ ${INC} ${LIBS}

${Target}:${OBJ}
	${CC} ${CXXFLAGS} ${INC} ${LIBS} -o $@ $<

clean:
	rm -rf obj/* ${Target}
