all:
	g++ -g -std=c++11 -pthread main.cpp -o airport.out
	./airport.out