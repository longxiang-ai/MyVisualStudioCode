import numpy as np
import matplotlib.pyplot as plt
import math as m
R=7.3e5
E=1200
C=6.5e-6
tau=10*R*C
t = np.arange(0,tau,0.01)
plt.plot(t,E/6)*(3-np,exp(-(2*t)/(3*R*C)))
plt.axvline(linewidth=1,color='black')
plt.grid()
plt.xlabel('t(s)',frontsize=12)
plt.ylabel('V(V)',frontsize=12)
plt.show()
