#ifndef project1_HPP
#define project1_HPP

class Project1 {
private:
  double *m_a, *m_b, *m_c;      //Integration interval [a,b]
  double *m_v, *m_g, m_h;
  int m_N;      //Number of integration points.
  double *m_x;

public:
  void gen_Initialize(double a, double b, int N, double f(double x));     //Initialize the parameters m_a, m_b  N
  void spes_Initialize(double x0, double xn, int N, double f(double x));
  void set_matrix_elements(double ai, double bi, double ci);   //Setting matrix elements
<<<<<<< HEAD
  void forward_sub();         //Forward substitution
  void backward_sub();       //Backward substitution
  double write_to_file(double u(double x));
=======
  void gen_forward_sub();         //Forward substitution
  void gen_backward_sub();       //Backward substitution
  void spes_forward_sub();         //Forward substitution
  void spes_backward_sub();       //Backward substitution
>>>>>>> bdee25cc6413f3f0b72e5c8d9162c904004eb0a5
  double write_solutions_to_file(double u(double x));
  double eps(double u(double x));
  double write_eps_to_file(double *eps, int *n, int N_power);
};

#endif
