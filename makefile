
all: compile execute

compile:
	c++ -o main.out main.cpp project1.cpp -O3

execute:
	./main.out
