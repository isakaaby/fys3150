import numpy as np
import matplotlib.pyplot as plt

infile = open("poissons_verdier.txt", 'r')
N = int(infile.readline())
x = np.zeros(N+1)
v = np.zeros(N+1)
u = np.zeros(N+1)
for i, line in enumerate(infile):
    numbers = line.split()
    x[i] = float(numbers[0])
    v[i] = float(numbers[1])
    u[i] = float(numbers[2])


plt.plot(x,v,label = 'v (numerical)')
plt.plot(x,u, label = 'u (analytical)')
plt.xlabel('x')
plt.ylabel('Numerical and analytical u(x)')
plt.legend()
plt.show()
