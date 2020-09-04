#include "project1.hpp"
#include <iostream>     //Provides us with function to print to terminal
#include <cmath>        //Provides us with mathematical functions such as sin, cos, exp and so on.
#include <fstream>

using namespace std;

void Project1::gen_Initialize(double x0, double xn, int N, double f(double x)){
  cout << "er i gen initialize" << "\n";
  m_N = N;      //Number of integration points
  m_h = ((double)(xn - x0)/(m_N+2));   // stepsize h
  m_a = new double[m_N];
  m_b = new double[m_N];
  m_c = new double[m_N];
  m_v = new double[m_N];
  m_g = new double[m_N];
  m_x = new double[m_N];
  double hh = m_h*m_h;
  for (int i = 0; i < m_N; i++){
    m_x[i] = x0 + (i+1)*m_h;
    m_g[i] = hh*f(m_x[i]);

  }
}

void Project1::spes_Initialize(double x0, double xn, int N, double f(double x)){
  //cout << "er i spes initialize" << "\n";
  m_N = N;      //Number of integration points
  m_h = ((double)(xn - x0)/(m_N+2));   // stepsize
  m_v = new double[m_N];
  m_g = new double[m_N];
  m_x = new double[m_N];
  m_b = new double[m_N];
  double hh = m_h*m_h;
  for (int i = 0; i < m_N; i++){
    m_x[i] = x0 + (i+1)*m_h;
    m_g[i] = hh*f(m_x[i]);
    cout << m_g[i] << "\n";
  }
  m_b[0] = 2;
  for (int i = 1; i < m_N; i++){
    m_b[i] = (double)(i+2)/(i+1);
    cout << m_b[i] << "\n";
  }
}

void Project1::set_matrix_elements(double ai, double bi, double ci){
  for (int i = 0; i < m_N; i++){
    m_a[i] = ai;
    m_b[i] = bi;
    m_c[i] = ci;
  }
}

void Project1::spes_forward_sub(){
  //cout << "er i spes forward" << "\n";
  for (int i = 1; i < m_N; i++){
    m_g[i] = m_g[i] + m_g[i-1]/m_b[i-1];
    //cout << m_g[i] << "\n";

  }
}

void Project1::spes_backward_sub(){
  m_v[m_N-1] = m_g[m_N-1]/m_b[m_N-1];
  for (int i = m_N-2; i >= 0; i--){
    m_v[i] = (m_g[i] + m_v[i+1])/m_b[i];
  }
}

void Project1::gen_forward_sub(){
  //cout << "er i gen forward" << "\n";
  for (int i = 1; i < m_N; i++){
    m_b[i] = m_b[i] - (m_a[i-1]*m_c[i-1])/m_b[i-1];
    m_g[i] = m_g[i] - (m_g[i-1]*m_c[i-1])/m_b[i-1];
    //cout << m_g[i] << "\n";

  }
}
//9.86121e-05
void Project1::gen_backward_sub(){
  m_v[m_N-1] = m_g[m_N-1]/m_b[m_N-1];
  for (int i = m_N-2; i >= 0; i--){
    m_v[i] = (m_g[i] - m_c[i]*m_v[i+1])/m_b[i];
  }
}


void Project1::write_solutions_to_file(double u(double x)){
 ofstream myfile1;
 myfile1.open("poissons_verdier.txt");
 myfile1 << m_N;
 myfile1 << "\n";
 for (int i = 0; i < m_N; i++){
   myfile1 << m_x[i] << " " << m_v[i] << " " << u(m_x[i]);
   myfile1 << "\n";
 }
 myfile1.close();
}

double Project1::eps(double u(double x)){
  double epsilon_max = 0;
  double epsilon;
  for (int i = 0; i < m_N+1; i++){
    epsilon = abs((m_v[i] - u(m_x[i]))/u(m_x[i]));
    if (epsilon > epsilon_max){
      epsilon_max = epsilon;
    }
  }
  epsilon_max = log10(epsilon_max);
  return epsilon_max;
}

void Project1::write_eps_to_file(double *eps, int *n, int N_power){
  ofstream myfile2;
  myfile2.open("epsilon_verdier.txt");
  for (int i = 0; i < N_power+1; i++){
    myfile2 << n[i] << " " << eps[i];
    myfile2 << "\n";
  }
  myfile2.close();

}
