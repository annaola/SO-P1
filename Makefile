all:
	g++ -Wall -Werror main.cpp -o main.out -pthread -std=c++11


.PHONY: run

run:
	./main.out 