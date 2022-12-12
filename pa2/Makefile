CXX = g++
CXXFLAGS = -std=c++14 -g -Wall -Werror=vla
OBJECTS = main.o Lexer.o Parser.o
EXEC = pa2

${EXEC} : ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

clean :
	rm ${OBJECTS} ${EXEC}
