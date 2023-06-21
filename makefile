PP=g++
CPPFLAGS= -Wall -g
OTHERS= graph.cpp

################################

OBJS=graph.o
MAIN=ep3.cpp

################################

.PHONY: clean

all: ep

graph.o: graph.h
ep3.o: ep3.cpp

ep: ${OBJS} 
		${PP} ${CPPFLAGS} -o ep3 ${MAIN} ${OTHERS}
		@rm -rf *.o

clean:
	@rm -rf ep2