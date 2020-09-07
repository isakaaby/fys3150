#include "project1.hpp"
#include <iostream>     //Need it to print stuff
#include <cmath>        //Need math functions
#include "time.h" // you have to include the time.h header
#include "armadillo"

using namespace arma;

using namespace std;

double f(double x); //declaring the f function on the right hand side of Poisson's equation
double u(double x); //declaring the closed form solution of Poisson's equation

int main(int argc, char const *argv[]) { //our main function
  double x0 = 0;   //Start point of integration
  double xn = 1;   //End point of integration
  int N;           //Number of integration points
  double ai = -1;  //elements on the lower diagonal
  double bi = 2;   //elements on the main diagonal
  double ci = -1;  //elements on the upper diagonal

  Project1 Solver;
  int task;
  cout << "Press 1 to run task b) \n";
  cout << "Press 2 to run task c) \n";          //asking whether to run task b),c),d) or e)
  cout << "Press 3 to run task d) \n";
  cout << "Press 4 to run task e) \n";
  cout << "Enter task number:" << " ";
  cin >> task;

  //Solving task b), with the general algorithm
  if (task==1){
    cout << "Number of grid points (N) = ";
    cin >> N;    //giving the number of grid points
    cout << "Solving task b) with" << " " << N << " "<< "grid points..." << "\n";
    cout << "Using the general algorithm..."<< "\n";
    Solver.gen_Initialize(x0, xn, N, f);
    Solver.set_matrix_elements(ai, bi, ci);    //setting the elements of the matrix manually
    clock_t start, finish;
    start = clock();
    Solver.gen_forward_sub();
    Solver.gen_backward_sub();
    finish = clock();
    double cpu_time = 1000.0 * (finish - start)/CLOCKS_PER_SEC;  ////computing CPU time
    cout << "CPU time: " << cpu_time << "ms\n";
    int flops = 9*(N-1);      //calculating number of FLOPS for the general algorithm
    cout << "FLOPS:" << " " << flops << "\n";
    cout << "Writing numerical solutions to file: solution.txt"<< "\n";
    Solver.write_solutions_to_file(u);    //writing numerical and analytical solutions to file
    cout << "Type <<make plot1>> in terminal to receive a plot of the numerical solutions along with the analytical solution "<< "\n";
  }

  //Solving task c), with the special algorithm
  if (task==2){
    cout << "Number of grid points (N) = ";
    cin >> N;  //giving the number of grid points
    cout << "Solving task c) with" << " " << N << " "<< "grid points..." << "\n";
    cout << "Using the special algorithm..."<< "\n";
    Solver.spes_Initialize(x0, xn, N, f);
    clock_t start, finish;
    start = clock();
    Solver.spes_forward_sub();
    Solver.spes_backward_sub();
    finish = clock();
    double cpu_time = 1000.0 * (finish - start)/CLOCKS_PER_SEC;  //computing CPU time
    cout << "CPU time: " << cpu_time << "ms\n";
    int flops = 4*(N-1);     //calculating number of FLOPS for the special algorithm
    cout << "FLOPS:" << " " << flops << "\n";
    cout << "Writing numerical solutions to file: solution.txt..."<< "\n";
    Solver.write_solutions_to_file(u);      //writing numerical and analytical solutions to file
    cout << "Type <<make plot1>> in terminal to receive a plot of the numerical solutions along with the analytical solution "<< "\n";
  }

  //Solving task d) with number of grid points from N=10 to N=10^7
  if (task==3){
    int N_power = 7;                       //the maximum power of N
    double *eps = new double[N_power];     //allocating the relative errors
    int *n = new int[N_power];             //allocating the different number of grid points
    cout << "Solving task d) using the special algorithm..." << "\n";
    cout << "Calculating relative error with number of grid points from N = 10 to N = 10^7" << "\n";
    clock_t start, finish;
    start = clock();
    for (int i = 0; i < N_power; i++){    //calculating the relative error for different numbers of grid points
      n[i] = pow(10,i+1);
      Solver.spes_Initialize(x0, xn, n[i], f);
      Solver.spes_forward_sub();
      Solver.spes_backward_sub();
      eps[i] = Solver.eps(u);
    }
    finish = clock();
    double cpu_time = 1000.0 * (finish - start)/CLOCKS_PER_SEC;   //computing CPU time
    cout << "CPU time: " << cpu_time << "ms\n";
    cout << "Writing the errors to file: error_solution.txt" << "\n";
    Solver.write_eps_to_file(eps, n, N_power);       //writing relative errors to file
  }
  //Solving task e)
  if (task==4){
    cout << "Number of grid points (N) = ";
    cin >> N;  //giving the number of grid points
    cout << "Solving task e) with" << " " << N << " "<< "grid points..." << "\n";
    mat A = Solver.matrix_A(ai,bi,ci,N);
    vec g = Solver.vec_g(x0, xn, N, f);

    cout << "Solving equation with LU decomposition..." << "\n";
    clock_t start, finish;
    start = clock();
    vec w = Solver.LU_decomp(A,g);
    finish = clock();
    double cpu_time;
    cpu_time = 1000.0 * (finish - start)/CLOCKS_PER_SEC;   //computing CPU time
    cout << "CPU time for LU decomposition: " << cpu_time << "ms\n";

    Solver.spes_Initialize(x0, xn, N, f);
    start = clock();
    Solver.spes_forward_sub();
    Solver.spes_backward_sub();
    finish = clock();
    cpu_time = 1000.0 * (finish - start)/CLOCKS_PER_SEC;   //computing CPU time
    cout << "CPU time for special algorithm: " << cpu_time << "ms\n";
    cout << "Writing solutions to file: solution_LU.txt" << "\n";
    Solver.write_LUsol_to_file(w,u);
    cout << "Type <<make plot2>> in terminal to receive a plot of the LU solutions along with the analytical solution "<< "\n";
  }

  return 0;   //Don't worry about this one, but you should always let it stay here at the bottom of the main function.
}

//Defining the f function on the right hand side of Poisson's equation
double f(double x){
  return 100*exp(-10*x);
}

//Defining the analytical solution of Poisson's equation
double u(double x){
  return 1. - (1-exp(-10))*x - exp(-10*x);
}
