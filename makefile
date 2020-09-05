all: compile execute

compile:
	c++ -o main.out main.cpp project1.cpp -larmadillo

execute:
	./main.out

plot1:
	python3 read_sol_plot.py

plot2:
	python3 read_sol_LU_plot.py
