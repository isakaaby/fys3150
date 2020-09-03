
all: compile execute

compile:
	c++ -o main.out main.cpp project1.cpp

execute:
	./main.out
