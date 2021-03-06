import numpy as np
import matplotlib.pyplot as plt

infile = open("solution_LU.txt", 'r')  #reading numerical and analytical solutions for a given N
N = int(infile.readline())    #number of grid points

#Filling the start boundaries
x = [0]   #grid points
w = [0]   #LU solutions
u = [0]   #analytic solutions

for line in infile:
    numbers = line.split()
    x.append(float(numbers[0]))
    w.append(float(numbers[1]))
    u.append(float(numbers[2]))

#Filling the end boundaries
x[N] = 1
w[N] = 0
u[N] = 0

x = np.array(x)
w = np.array(w)
u = np.array(u)

#plotting LU solutions along with analytic solutions

plt.plot(x,w,label = 'w (LU solution)')
plt.plot(x,u, label = 'u (analytical)')
plt.title("LU solution and analytical solutions for N = %d" %(N))
plt.xlabel('x')
plt.ylabel('LU and analytical solution')
plt.legend()
plt.show()
