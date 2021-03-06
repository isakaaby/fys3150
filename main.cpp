#include "project1.hpp"
#include <iostream>
#include <cmath>
#include "time.h"
#include "armadillo"

using namespace arma;

using namespace std;

double f(double x); //declaring the f function on the right hand side of Poisson's equation
double u(double x); //declaring the closed form solution of Poisson's equation

int main(int argc, char const *argv[]) { //our main function
  double x0 = 0;   //Start point
  double xn = 1;   //End point
  int N;           //Number of grid points
  double ai = -1;  //elements on the lower diagonal
  double bi = 2;   //elements on the main diagonal
  double ci = -1;  //elements on the upper diagonal

  Project1 Solver;
  int task;
  cout << "Press 1 to run task b) \n";
  cout << "Press 2 to run task c) \n";
  cout << "Press 3 to run task d) \n";           //asking which task you want to run
  cout << "Press 4 to run task e) \n";
  cout << "Press 5 to compare CPU time between special and general algorithm \n";
  cout << "Press 6 to compare CPU time between LU decomposition and tridiagonal solver \n";
  cout << "Enter number:" << " ";
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
    double cpu_time = 1000.0 * (finish - start)/CLOCKS_PER_SEC;  //computing CPU time
    cout << "CPU time: " << cpu_time << "ms\n";
    int flops = 9*(N-1);                        //calculating number of FLOPS for the general algorithm
    cout << "FLOPS:" << " " << flops << "\n";
    cout << "Writing numerical solutions to file: solution.txt"<< "\n";
    Solver.write_solutions_to_file(u);    //writing numerical and analytical solutions to file
    cout << "Type: make plot1, in terminal to receive a plot of the numerical solutions along with the analytical solution "<< "\n";
  }

  //Solving task c) , with the special algorithm
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
    cout << "Writing numerical solutions to file: solution.txt"<< "\n";
    Solver.write_solutions_to_file(u);      //writing numerical and analytical solutions to file
    cout << "Type: make plot1, in terminal to receive a plot of the numerical solutions along with the analytical solution "<< "\n";
  }

  //Solving task d) with number of grid points from N=10 to N=10^7
  if (task==3){
    int N_power = 7;                       //the maximum power of N
    double *eps = new double[N_power];     //allocating the relative errors
    int *n = new int[N_power];             //allocating the different number of grid points
    cout << "Solving task d) using the special algorithm..." << "\n";
    cout << "Calculating relative error with number of grid points from N = 10 to N = 10^7" << "\n";
    for (int i = 0; i < N_power; i++){    //calculating the relative error for different numbers of grid points
      n[i] = pow(10,i+1);
      Solver.spes_Initialize(x0, xn, n[i], f);
      Solver.spes_forward_sub();
      Solver.spes_backward_sub();
      eps[i] = Solver.epsilon(u);
    }
    cout << "Writing the errors to file: error_solution.txt" << "\n";
    Solver.write_eps_to_file(eps, n, N_power);       //writing relative errors to file
  }
  //Solving task e)
  if (task==4){
    cout << "Number of grid points (N) = ";
    cin >> N;  //giving the number of grid points
    cout << "Solving task e) with" << " " << N << " "<< "grid points..." << "\n";
    mat A = Solver.matrix_A(ai,bi,ci,N); //calculating the tridiagonal matrix A
    vec g = Solver.vec_g(x0, xn, N, f);  //calculating the right hand side (g = h^2*f) of the equation as a armadillo vector

    cout << "Solving equation with LU decomposition..." << "\n";
    clock_t start, finish;
    start = clock();
    vec w = Solver.LU_decomp(A,g);
    finish = clock();
    double cpu_time;
    cpu_time = 1000.0 * (finish - start)/CLOCKS_PER_SEC;   //computing CPU time for LU
    cout << "CPU time for LU decomposition: " << cpu_time << "ms\n";

    Solver.spes_Initialize(x0, xn, N, f);
    start = clock();
    Solver.spes_forward_sub();
    Solver.spes_backward_sub();
    finish = clock();
    cpu_time = 1000.0 * (finish - start)/CLOCKS_PER_SEC;   //computing CPU time for special algorithm
    cout << "CPU time for special algorithm: " << cpu_time << "ms\n";
    cout << "Writing solutions to file: solution_LU.txt" << "\n";
    Solver.write_LUsol_to_file(w,u);
    cout << "Type: make plot2, in terminal to receive a plot of the LU solutions along with the analytical solution "<< "\n";
  }

  //comparing CPU time between special and general algorithm
  if (task==5){
    cout << "Running general and special algorithms... \n";
    cout << "Comparing CPU time for n = 10 to n = 10^6 grid points... \n";
    int N_power = 6;                       //the maximum power of N
    double *cpu_gen = new double[N_power];     //allocating CPU time for general algorithm
    double *cpu_spes = new double[N_power];    //allocating CPU time for special algorithm
    int *n = new int[N_power];              //allocating the different number of grid points

    for (int i = 0; i < N_power; i++){  //calculating CPU time for different number of grid points n
      clock_t start_gen, finish_gen;
      clock_t start_spes, finish_spes;
      n[i] = pow(10,i+1);
      Solver.gen_Initialize(x0, xn, n[i], f);
      Solver.set_matrix_elements(ai, bi, ci);    //setting the elements of the matrix manually
      start_gen = clock();
      Solver.gen_forward_sub();
      Solver.gen_backward_sub();
      finish_gen = clock();
      cpu_gen[i] = 1000.0 * (finish_gen - start_gen)/CLOCKS_PER_SEC;   //computing general CPU time

      Solver.spes_Initialize(x0, xn, n[i], f);
      start_spes = clock();
      Solver.spes_forward_sub();
      Solver.spes_backward_sub();
      finish_spes = clock();
      cpu_spes[i] = 1000.0 * (finish_spes - start_spes)/CLOCKS_PER_SEC;   //computing special CPU time
    }
    cout << "Writing CPU times to file: CPU_comparison.txt" << "\n";
    Solver.write_CPU_to_file(n, cpu_gen, cpu_spes, N_power);       //writing CPU times to file
  }

  //comparing CPU time between special algorithm, general algorithm and LU decomposition
  if (task==6){
    cout << "Running general and special algorithms along with LU... \n";
    cout << "Comparing CPU time for n = 10, 100 and 1000 grid points \n";
    int N_power = 3;                       //the maximum power of N
    double *cpu_gen = new double[N_power];     //allocating CPU time for general algorithm
    double *cpu_spes = new double[N_power];    //allocating CPU time special algorithm
    double *cpu_lu = new double[N_power];      //allocating CPU time for LU
    int *n = new int[N_power];              //allocating the different number of grid points

    for (int i = 0; i < N_power; i++){    //calculating CPU time for different number of grid points n
      clock_t start_gen, finish_gen;
      clock_t start_spes, finish_spes;
      clock_t start_lu, finish_lu;

      n[i] = pow(10,i+1);
      Solver.gen_Initialize(x0, xn, n[i], f);
      Solver.set_matrix_elements(ai, bi, ci);    //setting the elements of the matrix manually
      start_gen = clock();
      Solver.gen_forward_sub();
      Solver.gen_backward_sub();
      finish_gen = clock();
      cpu_gen[i] = 1000.0 * (finish_gen - start_gen)/CLOCKS_PER_SEC;   //computing general CPU time

      Solver.spes_Initialize(x0, xn, n[i], f);
      start_spes = clock();
      Solver.spes_forward_sub();
      Solver.spes_backward_sub();
      finish_spes = clock();
      cpu_spes[i] = 1000.0 * (finish_spes - start_spes)/CLOCKS_PER_SEC;   //computing special CPU time

      mat A = Solver.matrix_A(ai,bi,ci,n[i]);
      vec g = Solver.vec_g(x0, xn, n[i], f);
      start_lu = clock();
      vec w = Solver.LU_decomp(A,g);
      finish_lu = clock();
      cpu_lu[i] = 1000.0 * (finish_lu - start_lu)/CLOCKS_PER_SEC;   //computing CPU time for LU
    }
    cout << "Writing CPU times to file: CPU_LU_comparison.txt" << "\n";
    Solver.write_CPU_LU_to_file(n, cpu_gen, cpu_spes, cpu_lu, N_power);       //writing CPU times to file
  }

  return 0;
}

//Defining the f function on the right hand side of Poisson's equation
double f(double x){
  return 100*exp(-10*x);
}

//Defining the analytical solution of Poisson's equation
double u(double x){
  return 1. - (1-exp(-10))*x - exp(-10*x);
}
