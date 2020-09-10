#include "project1.hpp"
#include <iostream>     //Provides us with function to print to terminal
#include <cmath>        //Provides us with mathematical functions such as sin, cos, exp and so on.
#include <fstream>
#include "armadillo"

using namespace arma;
using namespace std;

//Initializing the system for the general algorithm
void Project1::gen_Initialize(double x0, double xn, int N, double f(double x)){
  m_N = N;                              //Number of grid points
  m_h = ((double)(xn - x0)/(m_N+1));    // steplength h

  m_a = new double[m_N];
  m_b = new double[m_N];      //allocating the matrix vectors a,b and c
  m_c = new double[m_N];

  m_v = new double[m_N];     //allocating the numerical solutions v
  m_g = new double[m_N];     //allocating the right hand side of the equation g_i = h^2f_i
  m_x = new double[m_N];     //allocating the grid points
  double hh = m_h*m_h;
  for (int i = 0; i < m_N; i++){
    m_x[i] = x0 + (i+1)*m_h;       //filling the grid points from 0 to 1
    m_g[i] = hh*f(m_x[i]);         //filling g_i, using the function f_i for different x_i
  }
}

//Initializing the system for the special algorithm
void Project1::spes_Initialize(double x0, double xn, int N, double f(double x)){
  m_N = N;                              //Number of grid points
  m_h = ((double)(xn - x0)/(m_N+1));   // steplength

  m_v = new double[m_N];     //allocating the numerical solutions v
  m_g = new double[m_N];     //allocating the right hand side of the equation g_i = h^2f_i
  m_x = new double[m_N];     //allocating the grid points
  m_b = new double[m_N];     //allocating the main diagonal vector b
  double hh = m_h*m_h;
  for (int i = 0; i < m_N; i++){
    m_x[i] = x0 + (i+1)*m_h;         //filling the grid points from 0 to 1
    m_g[i] = hh*f(m_x[i]);           //filling g_i, using the function f_i for different x_i
    m_b[i] = (double)(i+2)/(i+1);    //filling the main diagonal using the Thomas-algorithm
  }
}

//setting the matrix elements for the general algorithm
void Project1::set_matrix_elements(double ai, double bi, double ci){
  for (int i = 0; i < m_N; i++){
    m_a[i] = ai;
    m_b[i] = bi;         //filling the matrix vectors with ai, bi and ci
    m_c[i] = ci;
  }
}

//special forward substitution
void Project1::spes_forward_sub(){
  for (int i = 1; i < m_N; i++){
    m_g[i] = m_g[i] + m_g[i-1]/m_b[i-1];     //updating the right hand side g_i
  }
}

//special backward substitution
void Project1::spes_backward_sub(){
  m_v[m_N-1] = m_g[m_N-1]/m_b[m_N-1];  //giving the last element of the numerical solution
  for (int i = m_N-2; i >= 0; i--){
    m_v[i] = (m_g[i] + m_v[i+1])/m_b[i];    //filling the rest of the numerical solutions
  }
}

//general forward substitution
void Project1::gen_forward_sub(){
  for (int i = 1; i < m_N; i++){
    m_b[i] = m_b[i] - (m_a[i-1]*m_c[i-1])/m_b[i-1];      //updating the main diagonal
    m_g[i] = m_g[i] - (m_g[i-1]*m_c[i-1])/m_b[i-1];      //updating the right hand side g_i
  }
}

//general backward substitution
void Project1::gen_backward_sub(){
  m_v[m_N-1] = m_g[m_N-1]/m_b[m_N-1];       //giving the last element of the numerical solution
  for (int i = m_N-2; i >= 0; i--){
    m_v[i] = (m_g[i] - m_c[i]*m_v[i+1])/m_b[i];   //filling the rest of the numerical solutions
  }
}

//writing the grid points x_i, the numerical solutions v_i and the analytical solutions u(x_i) to file, for a given n
void Project1::write_solutions_to_file(double u(double x)){
 ofstream myfile1;
 myfile1.open("solution.txt");
 myfile1 << m_N;
 myfile1 << "\n";
 for (int i = 0; i < m_N; i++){
   myfile1 << m_x[i] << " " << m_v[i] << " " << u(m_x[i]);
   myfile1 << "\n";
 }
 myfile1.close();
}

//writing CPU times for general and special algorithms to file, for n=10 to n=10^6
void Project1::write_CPU_to_file(int *n, double *cpu_gen, double *cpu_spes, int N_power){
  ofstream myfile2;
  myfile2.open("CPU_comparison.txt");
  for (int i = 0; i < N_power; i++){
    myfile2 << n[i] << " " << cpu_gen[i] << " " << cpu_spes[i];
    myfile2 << "\n";
  }
  myfile2.close();
}

//writing CPU times for general and special algorithms and LU to file, for n=10,100,1000
void Project1::write_CPU_LU_to_file(int *n, double *cpu_gen, double *cpu_spes, double *cpu_lu, int N_power){
  ofstream myfile3;
  myfile3.open("CPU_LU_comparison.txt");
  for (int i = 0; i < N_power; i++){
    myfile3 << n[i] << " " << cpu_gen[i] << " " << cpu_spes[i] << " " << cpu_lu[i];
    myfile3 << "\n";
  }
  myfile3.close();
}

//calculating the error of the numerical solution relative to the analytical solution
double Project1::epsilon(double u(double x)){
  double epsilon_max = 0;                   //giving a maximum relative error
  double epsilon;
  for (int i = 0; i < m_N; i++){
    epsilon = fabs((m_v[i] - u(m_x[i]))/u(m_x[i]));   //relative error
    if (epsilon > epsilon_max){
      epsilon_max = epsilon;      //setting new maximum relative error
    }
  }
  epsilon_max = log10(epsilon_max);     //taking the log10 of the final maximum relative error
  return epsilon_max;
}

//writing the relative errors for different number of grid points to file
void Project1::write_eps_to_file(double *eps, int *n, int N_power){
  ofstream myfile4;
  myfile4.open("error_solution.txt");
  for (int i = 0; i < N_power; i++){
    myfile4 << n[i] << " " << eps[i];
    myfile4 << "\n";
  }
  myfile4.close();
}

//creating the tridiagonal matrix A for solving LU
mat Project1::matrix_A(double ai, double bi, double ci, int N){
  //creating the tridiagonal matrix A with NxN elements
  mat A = mat(N,N);
  for (int i = 1; i < N-1; i++){
    A(i,i) = bi;
    A(i,i+1) = ai;
    A(i,i-1) = ci;
  }
  A(0,0) = bi;
  A(N-1,N-1) = bi;
  A(N-1,N-2) = ai;
  A(0,1) = ci;

  return A;
}

//calculating the right hand side of Poisson's equation as a armadillo vector
vec Project1::vec_g(double x0, double xn, int N, double f(double x)){
  double h;
  h = ((double)(xn - x0)/(N+2));
  double hh = h*h;
  vec g = vec(N);
  vec x = vec(N);
  for (int i = 0; i < N; i++){
    x(i) = x0 + (i+1)*h;
    g(i) = hh*f(x(i));
  }
  return g;
}

//Solving Poisson's equation by LU decomposition
vec Project1::LU_decomp(mat A, vec g){
    //doing the LU decomposition
    mat L, U, P;
    lu(L, U, A);
    vec y = solve(L,g);
    vec w  = solve(U,y);

    return w;
}

//writing grid points x_i, LU solutions and analytical solutions u(x_i) to file, for a given n
void Project1::write_LUsol_to_file(vec w, double u(double x)){
  ofstream myfile5;
  myfile5.open("solution_LU.txt");
  myfile5 << m_N;
  myfile5 << "\n";
  for (int i = 0; i < m_N; i++){
    myfile5 << m_x[i] << " " << w(i) << " " << u(m_x[i]);
    myfile5 << "\n";
  }
  myfile5.close();
 }
