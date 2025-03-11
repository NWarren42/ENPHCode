# %%
import sympy as sm
from sympy.abc import x as symX

import math

import numpy as np
import matplotlib.pyplot as plt

# %%

# ----------------------
# Question 1a
# ----------------------

# As an added challenge/coolness factor, all of the code written for part a 
# was written to be update dynamically based on the number of derivatives requested.
# The question only required 3, however if you change the number below (numDerivatives),
# you will see that the graphs and labels will all update themselves to the requested number of derivatives

numDerivatives=3

# function to return a list containing each symbolic derivative up to the nth order 
def nthOrderDerivatives(pFunction, var, n):
    derivativeList = []

    for i in range(0, n + 1):
        derivativeList.append(sm.diff(pFunction, var, i))

    return derivativeList


# Defining our parent function
symbolicF = sm.exp(sm.sin(2*symX))

# Creating an array of the valid x-values for the function (200 evenly spaced points)
Q1AB_xBounds = np.linspace(0, 2*math.pi, 200)

# Creating symbolic and lambdified derivatives to reference
symFcts = nthOrderDerivatives(symbolicF, symX, numDerivatives)

# Creating lambda functions and evaluating them at each point in the required range
lambdaFcts = []
lambdaVals = []
for i in range(0, numDerivatives + 1):
    lambdaFcts.append(sm.lambdify(symX, symFcts[i]))
    lambdaVals.append(lambdaFcts[i](Q1AB_xBounds))
    
    label="$f{}$".format("".join(['\'' for _ in range(i)])) # Creating dynamic labels for each derivative
    plt.plot(Q1AB_xBounds, lambdaVals[i], label=label) # Defining each label using LaTeX formatting is supported within python

# Miscellaneous Formatting Options
# plt.rcParams.update({"font.size": 18})
# plt.rcParams["figure.dpi"]= 120
plt.legend(loc="lower right")

plt.xlabel("x")
plt.ylabel("y")

plt.show()

# %%

# ----------------------
# Question 1b
# ----------------------

# Recall that I have already used the lamdify function up above to give me numerical outputs for the derivatives of the given function.
# This means instead of redefining that function here I can simply call the one from before, which happens to be at index 0 of the array lambdaFcts

# Functions to return the approximated first order derivatives using forward and central differentiation
def fwdDiff(f, x, h):
    return (f(x+h)-f(x))/h

def centDiff(f, x, h):
    return (f(x+(h/2))-f(x-(h/2)))/h

fwdDiffVals1 = fwdDiff(lambdaFcts[0], Q1AB_xBounds, 0.15)
fwdDiffVals2 = fwdDiff(lambdaFcts[0], Q1AB_xBounds, 0.5)
centDiffVals1 = centDiff(lambdaFcts[0], Q1AB_xBounds, 0.15)
centDiffVals2 = centDiff(lambdaFcts[0], Q1AB_xBounds, 0.5)

plt.plot(Q1AB_xBounds, fwdDiffVals1, label="f-d (0.15)")
plt.plot(Q1AB_xBounds, fwdDiffVals2, label="f-d (0.5)")
plt.plot(Q1AB_xBounds, centDiffVals1, label="c-d (0.15)")
plt.plot(Q1AB_xBounds, centDiffVals2, label="c-d (0.5)")

# Miscellaneous formatting options
# plt.rcParams.update({"font.size": 18})
# plt.rcParams["figure.dpi"]= 120
plt.legend(loc="upper right")

plt.xlabel("x")
plt.ylabel("Derivatives Output")

plt.show()

# %%

# ----------------------
# Question 1c
# ----------------------

# Recall that I have already defined numerical function outputs above in the array lambdaFcts. They are indexed so that index 0 is the 0th order
# derivative, index 1 is the 1st order derivative, and so on.

hValues = []
for i in range(0, 16 + 1):
    hValues.append(10**(-i)) 

hValues = np.array(hValues)

# Now we just have to 

fdError = abs(lambdaFcts[1](1) - fwdDiff(lambdaFcts[0], 1, hValues))
cdError = abs(lambdaFcts[1](1) - centDiff(lambdaFcts[0], 1, hValues))

plt.plot(hValues, fdError, label="f-d")
plt.plot(hValues, cdError, label="c-d")

plt.xscale("log")
plt.yscale("log")

plt.xlabel("h")
plt.ylabel("Absolute Deviation from Analytical Function")

plt.legend(loc="upper left")

plt.show()

# %%

# ----------------------
# Question 2a
# ----------------------

# Definitions for the pseudo-recursive function definitions required to take the fourth order derivative
# using the central difference approximation of a function

def centDiff1stOrder (f, x, h, n):
    return (f(x+(h/2), n)-f(x-(h/2), n))/h

def centDiff2ndOrder (f, x, h, n):
    return (centDiff1stOrder(f, x+(h/2), h, n)-centDiff1stOrder(f, x-(h/2), h, n))/h

def centDiff3rdOrder (f, x, h, n):
    return (centDiff2ndOrder(f, x+(h/2), h, n)-centDiff2ndOrder(f, x-(h/2), h, n))/h

def centDiff4thOrder (f, x, h, n):
    return (centDiff3rdOrder(f, x+(h/2), h, n)-centDiff3rdOrder(f, x-(h/2), h, n))/h


# The Rodrigues Function has been split into two different functions for clarity. "First Half"
# denotes the part of the equation that is not being differentiated, and "Second Half" denotes
# the part of the equation that is being differentiated. This was chosed arbitrarily based on 
# the way the equation was written in the notes

def firstHalfRodriguesFormula(n):
    return 1/((2**n)*math.factorial(n))

def secondHalfRodriguesFormula(x, n):
    return (x**2 - 1)**n 

# This function returns the rodrigues function for a specified n value using 
# the two half equations defined above
def cdRodriguesFormula(x, h, n):
    if (n == 1):
        return firstHalfRodriguesFormula(n) * centDiff1stOrder(secondHalfRodriguesFormula, x, h, n)
    elif(n == 2):
        return firstHalfRodriguesFormula(n) * centDiff2ndOrder(secondHalfRodriguesFormula, x, h, n)
    elif(n == 3):
        return firstHalfRodriguesFormula(n) * centDiff3rdOrder(secondHalfRodriguesFormula, x, h, n)
    elif(n == 4):
        return firstHalfRodriguesFormula(n) * centDiff4thOrder(secondHalfRodriguesFormula, x, h, n)
    
# Setting x bounds and prepping an array to keep the rodrigues functions in
Q2_xBounds = np.linspace(-1, 1, num=200)
Q2A_rodriguesValues = []


# Filling the array with each order of rodrigues function, and then plotting each one as well
for i in range(1, 4 + 1):
    Q2A_rodriguesValues.append(cdRodriguesFormula(Q2_xBounds, 0.01, i))
    plt.plot(Q2_xBounds, Q2A_rodriguesValues[i-1], label="n={}".format(i)) # Using format strings for dynamic labels


plt.xlabel("x")
plt.ylabel("y")
plt.legend()

plt.show()



# %%

# ----------------------
# Question 2b
# ----------------------

# Now we can write the proper recursive function for differentiating the Rodrigues equation instead
# of using the weird pseudo-recursive ones that we did above

def centDiffRecursive(f, x, h, n, i):
    if (i == 1): return (f(x+(h/2), n)-f(x-(h/2), n))/h
    else: return (centDiffRecursive(f, x+(h/2), h, n, i-1) - centDiffRecursive(f, x-(h/2), h, n, i-1))/h

nthOrderRodrigues = 8

# Now we are able to use the same half functions as defined above to create the rodrigues function
# using the new recursive function

def cdRodriguesFormula_recursive(x, h, n):
    return firstHalfRodriguesFormula(n) * centDiffRecursive(secondHalfRodriguesFormula, x, h, n, n)

# Prep array
Q2B_rodriguesValues = []


for i in range(1, nthOrderRodrigues + 1):
    Q2B_rodriguesValues.append(cdRodriguesFormula_recursive(Q2_xBounds, 0.01, i))
    plt.plot(Q2_xBounds, Q2B_rodriguesValues[i-1], label="n={}".format(i)) # Using format strings for dynamic labels

plt.xlabel("x")
plt.ylabel("y")
plt.legend()

plt.show()

# %%
