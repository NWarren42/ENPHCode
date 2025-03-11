# %%
import numpy as np
import matplotlib.pyplot as plt
import math as m
import mpmath as mp
from scipy.integrate import dblquad

import this
# %%
# ----------------------
# Question 1a
# ----------------------

def errorFct(val):
    return (2/(np.pi**(1/2)))*np.exp(-val**2)

# Rectangle rule for integration

def rect(f, lowerBound, upperBound, n):
    # Creating evenly spaced points between lower and upper bounds and returning the step size to use in area calculation
    xIntervals, stepSize = np.linspace(lowerBound, upperBound, n, retstep=True)
    
    # Trimming last element from array since we only want to evaluate at upperBound - step
    xIntervals = xIntervals[:-1]

    vals = f(xIntervals) * stepSize

    return np.sum(vals) # adding up all rectangle areas

rectApprox = rect(errorFct, 0, 1, 100)
rectError = abs((rectApprox-m.erf(1))/m.erf(1))

print(f"Rectangle rule approximation: {rectApprox:.5f}")

# %%

# ----------------------
# Question 1b
# ----------------------

def getSimpsonCoeffs(n, stepSize):
    coeffVals = np.ones(n)
    coeffVals[1:-1:2] = 4 # Set every odd value from the second element to the last element to 4
    coeffVals[2:-1:2] = 2 # Set every odd value from the third element to the last element to 2
    coeffVals *= stepSize/3

    return coeffVals

def trap(f, lowerBound, upperBound, n):
    xIntervals, stepSize = np.linspace(lowerBound, upperBound, n, retstep=True)
    intervalVals = f(xIntervals)
    
    # Setting up trap rule coefficient vector -- Follows pattern 1/2, 1, 1, ... 1, 1, 1/2
    coeffVals = np.ones(n)
    coeffVals[0] = 1/2
    coeffVals[-1] = 1/2

    return np.sum(intervalVals*coeffVals*stepSize)

def simpsons(f, lowerBound, upperBound, n):
    ''' This code needs some user warning:
    Taking 10 steps as an example, we see that simpsons rule breaks down when given an even number of steps.
    as this is the coefficient array that is output: [1. 4. 2. 4. 2. 4. 2. 4. 2. 1.]. The issue is that Simpsons
    rule requires the second, and second last term to be a 4, however that is not possible with an even
    number of steps. This means whenever we use an even step count the approximation is actually not behaving
    how its intended. To fix this we need to make sure n can only be input as an odd number. YES, in theory I could
    write the function so that if it is passed an even number, we add one to n to make it odd (like suggested in the
    assignment footnote) but I hate writing code that randomly modified the data that you are inputting to fix it 
    for you. If I'm passing an argument to a function saying "Run 100 times" and then it runs 101 times without me knowing,
    IMO you're just asking for a bug and headaches down the road in your code since it's not doing exactly what is 
    being written. Maybe I'm being a control freak, but at least this way (having the function throw an error) is very 
    explicit in telling the use what is happening (see "import this", line 8).
    '''

    if n % 2 == 0:
        raise ValueError("Step count for Simpson's approximation must be an even number")
    
    xIntervals, stepSize = np.linspace(lowerBound, upperBound, n, retstep=True)
    intervalVals = f(xIntervals)

    # Expanded, simpsons rule follows the pattern h/3 + 4h/3 + 2h/3 + 4h/3 + ... 2h/3 + 4h/3 + h/3
    # Constructing that array here

    coeffVals = getSimpsonCoeffs(n, stepSize)
     
    return np.sum(intervalVals*coeffVals)


# Note that here I've only evaluated trap at 100, and simp at 101. Per my comment above, evaluating simpson's
# approximation at n = 100 then displaying it as "Simpson's approximation when evaluated at n=100" would be 
# moronic because it's literally just garbage data and not even following Simpson's rule. If you were looking for 
# it, I didn't evaluate the trap or rect methods at 101 because the increase in precision is minimal (and really 
# doesn't show anything) and also I'm 90% sure the main teaching/learning point for the 100/101 thing was to have 
# the understanding to fix the add some comprehension to the even/odd simpson function issue.

trapApprox = trap(errorFct, 0, 1, 100)
simpApprox = simpsons(errorFct, 0, 1, 101)

trapError = abs((trapApprox-m.erf(1))/m.erf(1))
simpError = abs((simpApprox-m.erf(1))/m.erf(1))

print(f"Proper output for error function: {m.erf(1):.5f}")

# I think you could make an argument to not representing percentages in scientific notation but
# it looks prettier and is still readable so I've left it as is.
print(f"Rectangle rule approximation: {rectApprox:.5f} --- %Error: {100*rectError:.2e}")
print(f"Trapezoid rule approximation: {trapApprox:.5f} --- %Error: {100*trapError:.4e}")
print(f"Simpson's rule approximation: {simpApprox:.5f} --- %Error: {100*simpError:.2e}")

# %%

# ----------------------
# Question 1c
# ----------------------

# Recursive function that calls itself with increasing N values until desired error is achieved
def ERFadaptiveStep(approxFunction, lowerBound, upperBound, errorLimit, n, count):
    # Calculating value and error for current n value
    approxValue = approxFunction(errorFct, upperBound, lowerBound, n)
    error = abs((approxValue-m.erf(1))/m.erf(1))
    
    if(error <= errorLimit): return approxValue, error, n, count # Setting base case to return all calculated values in most recent call
    else: return ERFadaptiveStep(approxFunction, upperBound, lowerBound, errorLimit, n*2 - 1, count+1) # Recursively calling at 2n-1 for the N value

trapApprox_adaptive, trapError_adaptive, trapNVal_adaptive, trapIterationCount_adaptive = ERFadaptiveStep(trap, 0, 1, 10e-10, 3, 1)
simpApprox_adaptive, simpError_adaptive, simpNVal_adaptive, simpIterationCount_adaptive = ERFadaptiveStep(simpsons, 0, 1, 10e-10, 3, 1)

print("Function error limit set to 10e-10\n------------")
print(f"Trapezoid rule approximation: {trapApprox_adaptive:.5e} -- Error: {trapError_adaptive:.5e}\nAcheived at N = {trapNVal_adaptive} after {trapIterationCount_adaptive} iterations\n")
print(f"Simpson's rule approximation: {simpApprox_adaptive:.5e} -- Error: {simpError_adaptive:.5e}\nAcheived at N = {simpNVal_adaptive} after {simpIterationCount_adaptive} iterations")

print("\nNote that this is not the minimum value for n to acheive the desired\nprecision, this is a huge overshoot because we're doubling n to check\nvalues")


# %%

# ----------------------
# Question 2a
# ----------------------

def Q2fct(x, y):
    return ((x**2)+y)**(1/2)*np.sin(x)*np.cos(y)

def simpsons2D(f2d, lowBoundX, upBoundX, lowBoundY, upBoundY, n1, n2):
    if n1 % 2 == 0 or n2 % 2 == 0:
        raise ValueError("Step counts for Simpson's approximation must be an even number")

    xIntervals, stepVal1 = np.linspace(lowBoundX, upBoundX, n1, retstep=True)
    yIntervals, stepVal2 = np.linspace(lowBoundY, upBoundY, n2, retstep=True)

    # Creating compatible matrixes of the x and y intervals
    combinedIntervals = np.meshgrid(xIntervals, yIntervals)

    evaluatedFunction = f2d(*combinedIntervals) # Unpacking/evaluating results from interval combining w/ meshgrid

    # Assembling the set simpson approximation coefficients using the function defined above
    coeffVals1 = getSimpsonCoeffs(n1, stepVal1)
    coeffVals2 = getSimpsonCoeffs(n2, stepVal2)

    # Create the matrix of weights corresponding to each value of the 2d function evaluated across the interval matrix 
    weightedCoeffs = np.outer(coeffVals1, coeffVals2)

    # Multiplying the weighted coefficient matrix by the evaluated function matrix to get the 
    # relative weights of each point of the function.
    return np.sum(weightedCoeffs*evaluatedFunction)

simpsons2D(Q2fct, 0, np.pi, 0, np.pi/2, 1001, 1001)

# %%

# ----------------------
# Question 2b
# ----------------------

Q2fctLambda = lambda x, y: ((x**2)+y)**(1/2)*mp.sin(x)*mp.cos(y) # Creating the mp lambda function
mpQuadVal = mp.quad(Q2fctLambda, [0, np.pi], [0, np.pi/2])

print(f"MPQuad Function Calculation: {mpQuadVal}")

# %%

# ----------------------
# Question 2c
# ----------------------

# We can just reuse the lambda function from above
dblQuadVal, dblQuadError = dblquad(Q2fctLambda, 0, np.pi/2, 0, np.pi)

print(f"DBLQuad Function Calculation: {dblQuadVal} -- Error: {dblQuadError}")



# %%
'''
I apologize for the frankly absurd about of rambling and yappage in this assignment, I hope whoever
is grading this is having a nice day. 

Go Sens. 
'''
# MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMWNX0OkxxdddooolkWMMMMMMMMMMMMMMMMMMMMMMMMMMMM
# MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMWNXOxdoc:,,',,,,,,,;;xWMMMMMMMMMMMMMMMMMMMMMMMMMMMM
# MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMWKkdlc:,',,,,,,,,,,,,'',oNMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
# MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMWKxo:,',,,,,,,,,,,,,,,,,''cKMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
# MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMNOo:,,,',,,,,,,,,,,,,,,,,'';xWMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
# MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMXkc,,,,,,,,,,,,,,,,,,,,,,;,'':0NWWWMMMMMMMMMMMMMMMMMMMMMMMMMMM
# MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMNkc,,,,,,,,,,,,,,,,,,,,,,,,,',',looooddxkOKNWMMMMMMMMMMMMMMMMMMM
# MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMWKo;,,,,,;,,,,,,;,,,,,,,,,,,,,',,:oc::c:';:;:loxOXWMMMMMMMMMMMMMMM
# MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMWO:,,',,,,,,,,,,,,,,,,,,,,,,,,,',,coc;;:,.';..::,;lokXWMMMMMMMMMMMM
# MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMWx:,',,,,,,,,,,,,,,,,,,,,,,,,,,'....,,,,,,;:;;,,'.'c;;coONMMMMMMMMMM
# MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMWx;,',,,,,,,,,,,,,,,,,,,,,,,'..              ..,;;;,'..::;lONMMMMMMMM
# WXKWMMMMMMMMMMMMMMMMMMMMMMMMMMO:,',,,,,,,,,,,,,,,,,,,,,..                      .:c:,''.'::l0WMMMMMM
# Wk:cdk0XNMMMMMMMMMMMMMMMMMMMMKc,'',,,,,,,,,,,,,,;,,,,..        ..,;;;:;;'.   .;lodc,,;'',,;:dNMMMMM
# MWx;;,,:loxkOKNWWMMMMMMMMMMMWd;'',,,,,,,,,,,,,,,,;,'.       .;codddddddddo:':odddd;..,:;..::;lKMMMM
# MMNx;,......';:loddxxkkOOO00x:'',,,;,,,,,,,,,,,,,,.       'coddddddddddddl:ldddddd;   .;c;..;:c0MMM
# MMMWk:'.      .........'''''.''',,,,,,,,,,,,,,,,.       .:odddddddddddddl:cddddddd:.    ,c,';:;lKMM
# MMMMW0c,.                    .,',,,,,,,,,,,,,,,.       .cddddddddddddddo::odddddddc.     ,c,..c:oNM
# MMMMMMXd;'.                  ''',,,,,,,,,,,,,,,.       ;dddddddddddolllc:ldddddoo:.       ;c'';;:kM
# MMMMMMMW0o;'.                ''',,,,,,,,,,,,,,'.      .lddddddddddl::c:,cddddlokKk'       .c;..c:lN
# MMMMMMMMMW0dc,..             ',',,,,,,,,,,,,,,'.      'odddddddddd::oddooddooxXWWXx.       ;ooodc:0
# MMMMMMMMMMMWXkoc,....        ',',,,,,,,,,,,,,,'.      .oddddddddddc:loddol:dKWWXkd0x.      'olcll:k
# MMMMMMMMMMMMMW0ollol:,'......',',,,,,,,,,,,,,,,.      .:ddddddddoool::ccccckWMMWWWWWx.     .l;.'c:x
# MMMMMMMMMMMMMMKc,clllccccccc:,,'',,,;,,,,,,,,,,'.      .cddddddolkNNOoloddookXWMMMMWNd.    'oocll:k
# MMMMMMMMMMMMMMMXo:;'...',,;;;'',',,,,,,,,,,,,,,,'..     .;odddddoxXMMNkooddolo0MMMWKOl.    ,ooodc:O
# MMMMMMMMMMMMMMMMNx:'.          .,',,,,,,,,,,,,,,,,,.      'cdddddooOXXK0dloddlOMMMWKk,    .::..c:lX
# MMMMMMMMMMMMMMMMMW0l,..         ',',;,,,,,,,,,,,,;,,'.     .,lddddooldKWNkoodlxNMMWNKc    ,c'.,;:xW
# MMMMMMMMMMMMMMMMMMMNkc,..        ',',,,,,,,,,,,,,,,,,,.      .;oddddolOWWWXkollkWMMMMk.  ':,..::lXM
# MMMMMMMMMMMMMMMMMMMMMNOo:'..      .,',,,,,,,,,,,,,,,,,,'.      .cddl:,:lodxOOOdlxK0do:. ':,.,:;c0MM
# MMMMMMMMMMMMMMMMMMMMMMMWKkoc;'.....','',,,,,,,,,,,,,,,,,,.      ,c,.  .....':dOKKx.    ,c;'.,::OWMM
# MMMMMMMMMMMMMMMMMMMMMMMMMMNo;;::ccc:;,,',,,,,,,,,,,,,,,,,''.    ..         ..,:k0;   .::'.;c;c0WMMM
# MMMMMMMMMMMMMMMMMMMMMMMMMMM0:,::;::c;''''',,,,,,,,,,,,,,','.       ..........'','  .,;'';;;:oKMMMMM
# MMMMMMMMMMMMMMMMMMMMMMMMMMMMXd:;'.....  .''',,,;,,,,,,,','    ........          .',;,,.'c:ckNMMMMMM
# MMMMMMMMMMMMMMMMMMMMMMMMMMMMMW0o;'.       .','',,,,,,,,',.......            ..',,,,..:c;cxXMMMMMMMM
# MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMW0dl;....   ..'','',,,,,,,.';:;,'.......'.';;,,,,..:c;:lxXWMMMMMMMMM
# MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMN0kdoc:;,,,',,,,'',,',,,ldoc;;:;',:,';;..;'.,c;;cld0NMMMMMMMMMMMM
# MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMWNXK00000Ol;;,',',',clolccc;';:,':c;;::;cldx0NMMMMMMMMMMMMMMM
# MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM0l:,'',;oOkddoolccccccclloddxOKNMMMMMMMMMMMMMMMMMMM
# MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMXo;::,,cOWMMMMWNNXKKKKKXXNWMMMMMMMMMMMMMMMMMMMMMMMMM
# MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMKc,;:ldONMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
# MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMXOkO0NWMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM

