start: main.o func.o
	g++ -o start main.o func.o

main.o: main.cpp func.h
	g++ -c main.cpp

func.o: func.cpp func.h
	g++ -c func.cpp
