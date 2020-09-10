import numpy as np
import matplotlib.pyplot as plt

infile = open("solution.txt", 'r')
N = int(infile.readline())

#Filling the start boundaries
x = [0]    #grid points
v = [0]    #tridiagonal solutions
u = [0]    #analytic solutions

for line in infile:
    numbers = line.split()
    x.append(float(numbers[0]))
    v.append(float(numbers[1]))
    u.append(float(numbers[2]))

#Filling the end boundaries
x[N] = 1
v[N] = 0
u[N] = 0

x = np.array(x)
v = np.array(v)
u = np.array(u)

##plotting tridiagonal solutions along with analytic solutions

plt.plot(x,v,label = 'v (numerical)')
plt.plot(x,u, label = 'u (analytical)')
plt.title("Numerical and analytical solutions for N = %d" %(N))
plt.xlabel('x')
plt.ylabel('Numerical and analytical solutions')
plt.legend()
plt.show()
