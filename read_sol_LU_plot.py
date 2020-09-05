import numpy as np
import matplotlib.pyplot as plt

infile = open("solution_LU.txt", 'r')
N = int(infile.readline())
x = [0]
w = [0]
v = [0]
u = [0]
for line in infile:
    numbers = line.split()
    x.append(float(numbers[0]))
    w.append(float(numbers[1]))
    v.append(float(numbers[2]))
    u.append(float(numbers[3]))

x[N] = 1
w[N] = 0
v[N] = 0
u[N] = 0

x = np.array(x)
w = np.array(w)
v = np.array(v)
u = np.array(u)

plt.plot(x,w,label = 'w (LU solution)')
plt.plot(x,u, label = 'u (analytical)')
plt.title("LU solution and analytical solutions for N = %d" %(N))
plt.xlabel('x')
plt.ylabel('Numerical and LU u(x)')
plt.legend()
plt.show()
