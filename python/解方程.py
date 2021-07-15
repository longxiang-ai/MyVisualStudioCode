import matplotlib.pyplot as plt
import numpy as np
import math
x = np.linspace(-1, 5, 1000)   #分别代表最小，最大，数量， 生成一个等差数列
k = 0.0145
y = [((5+t)* math.exp(-t))for t in x]
z = [0 ]
plt.plot(x, y,z )
plt.show()
