#include "project1.hpp"
#include <iostream>     //Provides us with function to print to terminal
#include <cmath>        //Provides us with mathematical functions such as sin, cos, exp and so on.

using namespace std;

void Project1::Initialize(double x0, double xn, int N, double f(double x)){
  m_N = N;      //Number of integration points
  m_h = (xn - x0)/m_N;   // stepsize h
  m_a = new double[m_N];
  m_b = new double[m_N];
  m_c = new double[m_N];
  m_v = new double[m_N];
  m_g = new double[m_N];
  m_x = new double[m_N];
  double hh = m_h*m_h;
  for (int i = 0; i < m_N; i++){
    m_x[i] = x0 + i*m_h;
    m_g[i] = hh*f(m_x[i]);
  }
}

void Project1::set_matrix_elements(double ai, double bi, double ci){
  for (int i = 0; i < m_N; i++){
    m_a[i] = ai;
    m_b[i] = bi;
    m_c[i] = ci;
  }
}

void Project1::forward_sub(){
  for (int i = 1; i < m_N; i++){
    m_b[i] = m_b[i] - (m_a[i-1]*m_c[i-1])/m_b[i-1];
    m_g[i] = m_g[i] - (m_g[i-1]*m_c[i-1])/m_b[i-1];
  }
}

void Project1::backward_sub(){
  m_v[m_N-1] = m_g[m_N-1]/m_b[m_N-1];
  for (int i = m_N-2; i > 0; i--){
    m_v[i] = (m_g[i] - m_c[i]*m_v[i+1])/m_b[i];
  }
}

void Project1::Print(double u(double x)){
  //This is an example on how to print to terminal in C++.
  for (int i = 0; i < m_N; i++){
    cout << "x = " << m_x[i] << "vi = " << m_v[i] << "u(x) = " << u(m_x[i]) << endl;
  }
}
