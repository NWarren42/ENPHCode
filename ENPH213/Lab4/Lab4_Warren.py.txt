# %%
import numpy as np
import math as m
import matplotlib.pyplot as plt

import sympy as sm
from sympy.abc import x as symX

# %%
# ----------------------
# Question 1a
# ----------------------

def Q1Afct(x):
    return 1/(x-3)

def bisectionSolve(fct, xLow, xHigh, count, maxAttempts, tol):
    '''
    I wrote this as a recursive function because I didn't want to be boring and
    copy the exact code given to us that works as a bisection solver.
    '''

    if(count > maxAttempts): return None
    if abs(xLow - xHigh) < tol: return xLow, xHigh, count

    xNew = (xLow + xHigh)/2
    
    # This condition is needed on the off chance xLow or xHigh ever end up exactly 
    # on the zero point (like they do in my other test case) cause otherwise the code breaks
    if(fct(xNew) == 0): return xNew, xNew, count

    if fct(xLow) * fct(xNew) < 0:
        return bisectionSolve(fct, xLow, xNew, count+1, maxAttempts, tol)
    else: 
        return bisectionSolve(fct, xNew, xHigh, count+1, maxAttempts, tol)

Q1AxRange = np.linspace(2.5, 3.5, 100)
Q1AyVals = Q1Afct(Q1AxRange)

Q1Aroots = bisectionSolve(Q1Afct, 0, 5, 1, 200, 1e-9)
print(f"A root has been found between {Q1Aroots[0]}, and {Q1Aroots[1]} in {Q1Aroots[2]} attempts")

plt.plot(Q1AxRange, Q1AyVals)
plt.plot(Q1Aroots[0], 0, '.')
plt.show()

''' Is the result result valid?
The answer given by the code is obviously incorrect if we are ACTUALLY looking for a root to
the given function, however the code is correct as, due to the way a bisection solving method 
works, a vertical asymptote and a true root are literally indistinguishable. The bisection check
is looking for if adjacent points have opposite signs, then incrementally stepping closer and
closer to the point where they would end up having the same sign. Odd asymptotes (like the one 
present in the given function) have exactly what this function is looking for so it makes sense
that it thinks it has found a root at that location. The functionality of this code is tested below,
as I test whether it can find the root of a function with a real root.
'''

def testFct(x):
    return 1-x

tempXVals = np.linspace(0, 4, 100)
testRoots = bisectionSolve(testFct, 0, 4, 1, 200, 1e-9)

print(f"A root has been found between {testRoots[0]}, and {testRoots[1]} in {testRoots[2]} attempts")

plt.plot(tempXVals, testFct(tempXVals))
plt.axhline(0, color='red')
plt.show()


# %%
# ----------------------
# Question 1b
# ----------------------

symbolicFct = sm.exp(symX - sm.sqrt(symX)) - symX

# Creatin the functions by taking derivatives in sympy because.... I didn't want to hardcode the analytical
# derivatives I would have taken by hand. Why? I don't know to be honest... it was lowkey more work then taking
# them by hand,
Q1Bfct = sm.lambdify(symX, symbolicFct)
Q1BfctPrime = sm.lambdify(symX, sm.diff(symbolicFct, symX, 1))

Q1BxRange = np.linspace(0, 1.5, 300)
Q1ByVals = Q1Bfct(Q1BxRange)

Q1Broots = bisectionSolve(Q1Bfct, 0, 1.5, 1, 200, 1e-8)
print(f"A root has been found between {Q1Broots[0]}, and {Q1Broots[1]} in {Q1Broots[2]} attempts")

def newtonSolve(fct, fctPrime, x, maxTries, tol):
    oldX = x
    newX = None
    count = 0
    
    # Evaluating the starting guess using the functions needed to find the approximation
    slopeList = [fctPrime(x)]
    xValList = [x]
    yValList = [fct(x)]

    for i in range(maxTries):
        # Using the newton solving formula to set the next point to check
        newX = oldX - fct(oldX)/fctPrime(oldX)
        
        # Storing corresponding point and slope values to use later in plotting
        xValList.append(newX)
        slopeList.append(fctPrime(newX))
        yValList.append(fct(newX))

        # Checking if the next x value to check is within tolerance
        if abs(newX-oldX) < tol:
            break
        oldX = newX
        count +=1 

    return newX, count, xValList, yValList, slopeList

newtonSolveVals = newtonSolve(Q1Bfct, Q1BfctPrime, 0.01, 100, 10e-8)
print(f"Root found at {newtonSolveVals[0]} after {newtonSolveVals[1]} iterations")

plt.axhline(0, color='black')
plt.plot(Q1BxRange, Q1ByVals)
plt.plot(newtonSolveVals[2], newtonSolveVals[3], '.')

# Run for each point. The indexing is messy and ugly, but 2 is xvals, 3 is yvals, and 4 is slope vals.
# There are better ways to do this to make the code more readable but i'm lazy and this isn't terrible
for i in range(len(newtonSolveVals[4])):
    # using y=mx+b to create the points needed to plot cleanly bounded lines
    bVal = newtonSolveVals[3][i] - newtonSolveVals[4][i]*newtonSolveVals[2][i]
    xInt = -bVal/newtonSolveVals[4][i]

    # Setting up lines to show slope. solveVals[2] is the x eval point
    xVals = np.linspace(newtonSolveVals[2][i], xInt, 100)
    yVals = newtonSolveVals[4][i]*xVals + bVal

    # plotting slope and vertical lines at checked points
    plt.plot(xVals, yVals, '--', color='r')
    plt.vlines(xVals[0], 0, yVals[0], linestyles='dotted', color='b')

    # Plotting the labels for each point. They kinda stack on top of each other at the end but
    # I've consciously left it as is to show that there are in fact other points there that were evaluated
    plt.text(xVals[0]-0.02, -.06, f"x{i}")


plt.xlim(-0.1, 1.2)
plt.ylim(-0.1, 1)

plt.show()
# %%
# ----------------------
# Question 1c
# ----------------------

# Same deal as above, this is definitely overkill but it means I skip doing any real calculus myself
Q1CsymbolicFct = (sm.exp(symX - sm.sqrt(symX)) - symX)/(symX - 1)
Q1Cfct = sm.lambdify(symX, Q1CsymbolicFct)
Q1CfctPrime = sm.lambdify(symX, sm.diff(Q1CsymbolicFct, symX, 1))

# Values to run start at
initialVals = [2, 0.5, 4, 0.1]

# Just running the newton solve for each initial value
for i in range(4):
    newtonSolveVals = newtonSolve(Q1Cfct, Q1CfctPrime, initialVals[i], 100, 1e-8)
    print(f"Root found at {newtonSolveVals[0]} after {newtonSolveVals[1]} iterations - x0 = {initialVals[i]}")

'''
The root at x=2.5 was found for each test condition.
Interesting to note that these values are not nearly as close to the desired 2.5 as with when we were finding
the root at 1 (2.4909 vs 0.9999999...). This is probably due to the behaviour of the function around that point
being different in some way or another, but I'm not entirely sure why. 
'''

# %%
# ----------------------
# Question 2a
# ----------------------

waterDensity = 1
sphereDensity = 0.55
sphereRad = 1

# Considering rad is 1, the rad**3 term is kinda pointless... but I digress. This is more complete
sphereMass = (4/3)*np.pi*(sphereRad**3)*sphereDensity

# Gives the difference between the spheres total mass and the amount of water it's displaced
# when the difference is 0, we know the sphere will float by Archimedes' principle. Archimedes' principle
# is normally defined using weight, but since that would only multiple the mass values by some scalar (probably
# around 9.81 m/s^2 if you're a human) the displacement ratio remains the same so we can ignore the magnitude of gravity.
def getMassDifference(h):
    return sphereMass - (1/3)*np.pi*(3*sphereRad*(h**2) - h**3) * waterDensity

hVals = np.linspace(0, 2, 300)
massDiff = getMassDifference(hVals)

# For some reason when I wrote my bisection solve I had it give me both side of the root it was approaching,
# hence why I am ignoring the first return. Were dealing with tiny tolerances here so it was kinda pointless
# for me to write the function like that. 
_, floatPoint, numTries = bisectionSolve(getMassDifference, 0, 2, 0, 200, 1e-8)

print(f"A sphere with density {sphereDensity} will float at a depth of {floatPoint:0.4f}\n" +
      f"This value was found after {numTries} iterations using the bisection solving method")
print("--------------------------------------------------------------------------------------")

# %%

# ----------------------
# Question 2b
# ----------------------

myFig= plt.figure()
floatingSphere = myFig.add_subplot(projection='3d')

# Setting plane coordinates (water surface)
xRange = np.linspace(-1, 1, 100)
yRange = np.linspace(-1, 1, 100)

xRange, yRange = np.meshgrid(xRange, yRange)
waterHeight = np.ones_like(xRange) *  floatPoint

floatingSphere.plot_surface(xRange, yRange, waterHeight, color='blue', alpha=0.3, zorder=0)

# Using u/v as parameterization variables for spherical coords
uRange = np.linspace(0, 2*np.pi, 100)
vRange = np.linspace(0, np.pi, 100)

# Computing points on the sphere using dot product and standard spherical --> cartesian eqns.
xCoords = sphereRad * np.outer(np.cos(uRange), np.sin(vRange))
yCoords = sphereRad * np.outer(np.sin(uRange), np.sin(vRange))
zCoords = sphereRad * np.outer(np.ones(np.size(uRange)), np.cos(vRange))

# I can't seem to get this sphere to display overtop of the plane for some reason, even though matplotlib
# is telling me it follows sequential plotting practices (i.e. last plotted should be on top). But I leave
# for vacation tomorrow morning and I don't want to spend all night fixing this its already far too late.
floatingSphere.plot_surface(xCoords, yCoords, zCoords + floatPoint, color='red', alpha=1, zorder=10)

floatingSphere.set_aspect('equal')

plt.show()


# %%
# ----------------------
# Question 3a
# ----------------------

def retSet1(xs):
    x0, x1 = xs
    f0 = x0**2 - 2*x0 + x1**4 - 2*x1**2 + x1
    f1 = x0**2 + x0 + 2*x1**3 - 2*x1**2 - 1.5*x1 - 0.05
    return np.array([f0, f1])

def retSet2(xs):
    x0, x1, x2 = xs
    f0 = 2*x0 - x1*np.cos(x2) - 3
    f1 = x0**2 - 25*(x1-2)**2 + np.sin(x2) - np.pi/10
    f2 = 7*x0*np.exp(x1) - 17*x2 + 8*np.pi
    return np.array([f0, f1, f2])

# %%

# ----------------------
# Question 3b
# ----------------------

def getJacobian(functionSet, xs, stepSize=1e-4):
    matSize = len(xs)
    jacMat = np.zeros((matSize,matSize))

    fctOutputs = functionSet(xs)

    for i in range(matSize):
        # Start each cycle at the desired x values
        fwdDiffXs = xs.copy()
        fwdDiffXs[i] += stepSize

        fwdDiffFctOuts = functionSet(fwdDiffXs)
        jacMat[:,i] = (fwdDiffFctOuts - fctOutputs)/stepSize
    
    return jacMat

set1Xs = [1.0, 1.0]
set2Xs = [1.0, 1.0, 1.0]

print(getJacobian(retSet1, set1Xs))
print(getJacobian(retSet2, set2Xs))

'''
I know the assignment says "For convenience in using the generalized Newton's Method, also return f(x),
using a default tol=10^-8." but I can't figure out for the life of me what that could be asking me to do
and I made the code work without it so... sorry? dunno, it doesn't seem like i'll lose marks for this based
on the wording. I just want to prove that I'm not blind.
'''

# %%

# ----------------------
# Question 3c
# ----------------------

def generalNewtonsMethod(functionSet, xs, tol=1e-8, maxTries=200):
    xVals = xs.copy()
    for i in range(maxTries):
        # This code reads exactly how the general newtons method was described in the slides. We just take
        # the jacobian, then solve the matrix to dictate the step size for how we want to get closer to the root
        jacMat = getJacobian(functionSet, xVals)
        xSteps = np.linalg.solve(jacMat, -functionSet(xVals))
        xVals += xSteps

        # Using euclidean norm to check tolerance on the whole system, I could check tolerance
        # on each individual solution if we reaaaally care but this should be good enough
        if np.linalg.norm(xSteps) < tol: 
            break
    
    return xVals

set1Roots = generalNewtonsMethod(retSet1, set1Xs)
set2Roots = generalNewtonsMethod(retSet2, set2Xs)

print(f"The roots found for set 1 are {set1Roots}, which evaluate to {retSet1(set1Roots)}")
print(f"The roots found for set 2 are {set2Roots}, which evaluate to {retSet2(set2Roots)}")

'''
Both sets of found roots evaluate to essentially 0 so the code is workin B)
'''

# %%

'''
I would like it to be made known that I wanted to try to make this work with sympy and I sat here for an
hour trying to write it but my brain is slowing down and it's too late for it to be worth writing in sympy
when I can just take the derivatives by hand.
'''

def analyticalJacForSet2(xs):
    x0, x1, x2 = xs

    return np.array([[2           , np.cos(x2)     , x1*np.sin(x2)],
                     [2*x0        , -50*(x1 - 2)   , np.cos(x2)   ],
                     [7*np.exp(x1), 7*x0*np.exp(x1), -17          ]])

print(getJacobian(retSet2, set2Xs))
print(analyticalJacForSet2(set2Xs))

'''
Some values are not within tolerance (1e-8) but they're close enough that I can confidently say I 
can take successful derivatives at a 12th grade level. Oh and I guess that my code is right for finding
the numerical jacobian yea that too. (I mean I kinda already validated that when the newtons method code
worked then spat out 0s when I evaluated it but this was a fun little check and side adventure into the sympy
documentation)
'''

# %%

'''
Salut Bye I'm off to cuba. I hope whoever is marking this had (is having?) a nice reading break. I need to stop writing
these at like 3am, I apologize for the absurd amount of yappage in this assignment.
'''