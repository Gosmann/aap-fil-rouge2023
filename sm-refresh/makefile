all: tic_tac_toe.o mini_max.o main.o 
	g++ main.o tic_tac_toe.o mini_max.o -o output

main.o : main.cpp
	g++ -c main.cpp -o main.o

tic_tac_toe.o : tic_tac_toe.cpp
	g++ -c tic_tac_toe.cpp -o tic_tac_toe.o

mini_max.o : mini_max.cpp
	g++ -c mini_max.cpp -o mini_max.o

clean:
	rm *.o
