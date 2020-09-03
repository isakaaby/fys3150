#include "project1.hpp"
#include <iostream>     //Need it to print stuff
#include <cmath>        //Need math functions

//made some changes
using namespace std;

double f(double x); //We declare the function here, but specify it at the bottom.
double u(double x); //analytical solution to poissons equation

int main(int argc, char const *argv[]) {
  //Parameters
  double x0 = 0;   //Start point of integration
  double xn = 1;   //End point of integration
  int N = 1000;   //Number of integration points

  Project1 Solver;
  int check;
  //oppg b)
  cout << "Press 1 to run task b): \n";
  cout << "Press 2 to run task c): \n";
  cout << "Press 3 to run task d): \n";
  cin >> check;
  if (check==1){
    double ai = -1;
    double bi = 2;
    double ci = -1;
    Solver.gen_Initialize(x0, xn, N, f);
    Solver.set_matrix_elements(ai, bi, ci);
    Solver.gen_forward_sub();
    Solver.gen_backward_sub();
    Solver.write_solutions_to_file(u);
  }
  //oppg c)
  if (check==2){
    Solver.spes_Initialize(x0, xn, N, f);
    Solver.spes_forward_sub();
    Solver.spes_backward_sub();
    Solver.write_solutions_to_file(u);
  }
  //oppg d)
  if (check==3){
    int n0 = 10;
    int N_power = 7;
    double *eps = new double[N_power];
    int *n = new int[N_power];
    for (int i = 0; i < N_power+1; i++){
      n[i] = pow(10,i)*n0;
      Solver.spes_Initialize(x0, xn, n[i], f);
      Solver.spes_forward_sub();
      Solver.spes_backward_sub();
      eps[i] = Solver.eps(u);
    }
    Solver.write_eps_to_file(eps, n, N_power);
  }

  return 0;
}

//The function we want to integrate
double f(double x){
  return 100*exp(-10*x);
}

//Analytical solution
double u(double x){
  return 1 - (1-exp(-10))*x - exp(-10*x);
}
