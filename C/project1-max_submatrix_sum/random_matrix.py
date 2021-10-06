import numpy as np
from numpy.random import *

for n in range(3, 100+1):
    filepath = r"D:\课程文件\vs-code\C\project1-max_submatrix_sum\random{}.txt".format(
        n)
    line = []
    for i in range(100):
        line.append(randint(-65535, 65535, n*n))
    np.savetxt(filepath, line, fmt='%d')
