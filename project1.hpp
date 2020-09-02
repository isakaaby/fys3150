#ifndef project1_HPP
#define project1_HPP

class Project1 {
private:
  double *m_a, *m_b, *m_c;      //Integration interval [a,b]
  double *m_v, *m_g, m_h;
  int m_N;      //Number of integration points.
  double *m_x;

public:
  void Initialize(double a, double b, int N, double f(double x));     //Initialize the parameters m_a, m_b  N
  void set_matrix_elements(double ai, double bi, double ci);   //Setting matrix elements
  void forward_sub();         //Forward substitution
  void backward_sub();       //Backward substitution
<<<<<<< HEAD
  void Print(double u(double x));
=======
  double write_to_file(double u(double x));
>>>>>>> 7400582321905d14a00ad90df346933ea44315fb
};

#endif
