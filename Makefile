CXX = g++
CXXFLAGS = -std=c++14 -Wall -MMD
EXEC = block_test
OBJECTS = block.o block_test.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

clean:
	rm -f ${OBJECTS} ${EXEC} ${DEPENDS}
.PHONY: clean
