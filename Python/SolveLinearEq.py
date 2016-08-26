# -*- coding: utf-8 -*-
"""
Created on Wed May 11 14:52:14 2016

@author: Evert
"""

import numpy as np
import matplotlib.pyplot as plt

# Set min and max values for X-axis
xMin = -5
xMax =  5

# Set coefficients for the polynomial
C = np.array([0.2, 1, 3.2, 2.1])

def F(X,C):
    i = C.size - 1
    y = C[i]
    while i > 0:
        i = i - 1
        p = C.size - i -1
        y = y + C[i] * X ** p
    return y

# Calculate X and Y values
X = np.linspace(xMin, xMax, C.size)
Y = F(X, C)

# Create matrix A
p = C.size - 1
A = np.array( X**p)
while p > 0:
    p = p - 1
    A = np.vstack((A,X**p))

# Solve A * p = Y
P = np.linalg.solve(A.transpose(), Y.transpose())

# P should be equal to C

FX = np.linspace(xMin,xMax,1000)
FY = F(FX,P)

plt.plot(X, Y,'o',FX,FY)
plt.title('Curve Fitting')

plt.show()


