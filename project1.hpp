<<<<<<< HEAD

=======
>>>>>>> ae3f8d2956b26d467950c061cca4eef1d6fc5dd3
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
  void forward_sub(double f(double x));         //Forward substitution
  void backward_sub(double f(double x));       //Backward substitution
  void Print(double u(double x));
};

#endif
