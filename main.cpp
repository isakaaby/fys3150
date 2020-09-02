#include "project1.hpp"
#include <iostream>     //Need it to print stuff
#include <cmath>        //Need math functions

using namespace std;

double f(double x); //We declare the function here, but specify it at the bottom.
<<<<<<< HEAD
double u(double x);  //analytical solution
=======
double u(double x); //analytical solution to poissons equation
>>>>>>> 0985e6459eb0b152e36e1e3608130e3b1e3c55fe

int main(int argc, char const *argv[]) {
  //Parameters
  double x0 = 0;   //Start point of integration
  double xn = 1;   //End point of integration
  int N = 1000;   //Number of integration points
  double ai = -1;
  double bi = 2;
  double ci = -1;

  //Solve integral
  Project1 Solver;    //Create the solver of type Trapezoidal
  Solver.Initialize(x0, xn, N, f);
  Solver.set_matrix_elements(ai, bi, ci);
  Solver.forward_sub();
  Solver.backward_sub();
<<<<<<< HEAD
  Solver.Print(u);
=======
  Solver.write_to_file(u);
>>>>>>> 7400582321905d14a00ad90df346933ea44315fb

  return 0;   //Don't worry about this one, but you should always let it stay here at the bottom of the main function.
}

//The function we want to integrate
double f(double x){
  return 100*exp(-10*x);
}

//Analytical solution
double u(double x){
  return 1 - (1-exp(-10))*x - exp(-10*x);
}
