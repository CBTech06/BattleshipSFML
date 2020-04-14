CXX= g++
CFLAGS= -Wall -w -g
LDFLAGS= -lsfml-graphics -lsfml-system -lsfml-window
SRC= main.cpp board.cpp computer.cpp boat.cpp game.cpp
OBJ= main.o board.o computer.o boat.o game.o
EXE= Battleship

${EXE}:${OBJ}
	${CXX} ${CFLAGS} ${LDFLAGS} ${SRC} -o ${EXE}

main.o: main.cpp
	${CXX} -c main.cpp -o main.o

board.o : board.cpp
	${CXX} -c board.cpp -o board.o

computer.o: computer.cpp
	${CXX} -c computer.cpp -o computer.o 

boat.o: boat.cpp
	${CXX} -c boat.cpp -o boat.o

game.o: game.cpp
	${CXX} -c game.cpp -o game.o

clean:
	rm -rf ${OBJ} ${EXE}
