# Makefile for compiling and running Airport Program
all:
	g++ -g -std=c++11 -pthread main.cpp -o airport.out 
	@read -p "Enter Number of Planes: " planes; \
	./airport.out $$planes 