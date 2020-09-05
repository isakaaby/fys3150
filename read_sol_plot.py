import numpy as np
import matplotlib.pyplot as plt

infile = open("solution.txt", 'r')
N = int(infile.readline())
x = [0]
v = [0]
u = [0]
for line in infile:
    numbers = line.split()
    x.append(float(numbers[0]))
    v.append(float(numbers[1]))
    u.append(float(numbers[2]))

x[N] = 1
v[N] = 0
u[N] = 0

x = np.array(x)
v = np.array(v)
u = np.array(u)


plt.plot(x,v,label = 'v (numerical)')
plt.plot(x,u, label = 'u (analytical)')
plt.title("Numerical and analytical solutions for N = %d" %(N))
plt.xlabel('x')
plt.ylabel('Numerical and analytical u(x)')
plt.legend()
plt.show()
