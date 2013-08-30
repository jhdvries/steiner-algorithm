#! /usr/bin/env python
import numpy
import matplotlib.pyplot as plt
from numpy import sqrt
a=numpy.loadtxt('results.txt')
print('the full array')
print(a)
print('the first column')
print(a[:,0])
print('the second column')
print(a[:,1])
print('the sqrt of the second column')
print(sqrt(a[:,1]))

plt.figure()
plt.plot(a[:,0],a[:,1])
plt.show()
