
all: matrix

matrix: main.o matrix.o 
	g++ main.o matrix.o  -g -o matrix

main.o: main.cpp
	g++ -c -g main.cpp

matrix.o: matrix.cpp
	g++ -c -g matrix.cpp 
   



clean:
	rm *.o matrix
