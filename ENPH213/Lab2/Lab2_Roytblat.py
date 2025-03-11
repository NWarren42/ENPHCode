"""
Created on Mon Jan 22 12:57:53 2024

@author: B Roytblat, Queen's U

ENPH 213
Lab 2 - Numerical Integration

"""
#%% 1a) Calculate rectangle approximation for error function 

#import necessary modules
import numpy as np
import math as m
import mpmath as mp
from scipy.integrate import dblquad

def errorFunc(x): # deine error function integrand
    return (2/(np.pi**(1/2)))*np.exp(-x**2)

def rectangle (f,a,b,n):
    h = (b-a)/(n-1) # create equally spaced intervals
    rectArray = np.arange(n-1) # create array of n-1 elements
    xi = a + (rectArray)*h #set x values in new array
    print(xi, h)
    return np.sum(f(xi)*h) # return rectangle approximation

print("Rectangle Approximation: Area =", rectangle(errorFunc, 0, 1, 100))

#%% 1b) Calculate trapezoid and simpson's approximation for error function and error percentage

def trapezoid(f,a,b,n):
    h = (b-a)/(n-1) # create equally spaced intervals
    trapArray = np.arange(n) # create array of n elements
    xi = a+(trapArray*h) #set x values in new array
    coeff = np.ones(n) # set all coefficients to 1
    coeff[0] = 1/2 # add special case 0.5 coeffcient to first and last element
    coeff[-1] = 1/2 
    return h*np.sum(coeff*f(xi))

print("Trapezoid Approximation: Area =", trapezoid(errorFunc, 0, 1, 100))

def simpson(f,a,b,n):
    h = (b-a)/(n-1) # create equally spaced intervals
    simpArray = np.arange(n) # create array of n elements
    xi = a+(simpArray*h) # set x values in new array
    coeff = 2*np.ones(n) # set all coefficients to 2
    coeff[1::2] = 4 # add special case 4 coeffcient to every other value
    coeff[0] = 1 # add special case 1 coeffcient to first and last element
    coeff[-1] = 1
    return (h/3)*np.sum(f(xi)*coeff)

print("Simpson Approximation: Area =", simpson(errorFunc, 0, 1, 100))

# define error functions using math.erf(1)
def rectRE(a,b,n):
    return abs((rectangle(errorFunc, a, b, n)-m.erf(1))/m.erf(1))*100
def trapRE(a,b,n):
    return abs((trapezoid(errorFunc, a, b, n)-m.erf(1))/m.erf(1))*100
def simpRE(a,b,n):
    return abs((simpson(errorFunc, a, b, n)-m.erf(1))/m.erf(1))*100

print()
print("Rectangle Error:", rectRE(0,1,100))
print("Trapezoid Error:", trapRE(0,1,100))
print("Simpson Error:", simpRE(0,1,100))
print()

#%% 1c) Calculate error each method for error using precision

def adapStep(f,a,b,n,counter):
    counter =counter +1
    error = f(a,b,n)*0.01 # convert from percentage to decimal
    if (error >= 10**(-10)): # check if error value falls within error accuracy
        return adapStep(f, a, b, 2*n-1, counter) # recursive call 
    return error, counter-1 # returns error with desired precision and # of iterations
    
trapError, trapIterations = adapStep(trapRE,0,1,3,0)    
print("Trap Error: Area =", trapError)
print("Number of iterations:", trapIterations)

simpError, simpIterations = adapStep(simpRE,0,1,3,0)
print("Simp Error:  Area =", simpError)
print("Number of iterations:", simpIterations)

#%% 2a) Calculate 2d simpson's rule

#set bounds derivative
a = 0
b = np.pi
c = 0
d = np.pi*0.5

def f2d(x, y): # define integrand
    return (np.sin(x))*(np.cos(y))*(((x**2)+y)**(1/2))

def simp2d(f,a,b,c,d,n,m):
    
    hx = (b-a)/(n-1)  # create equally spaced intervals in x axis
    hy = (d-c)/(m-1)  # create equally spaced intervals in y axis
    h = hx*hy  # create equally spaced vector intervals using both x and y equally spaced intervals
    simpArrayX = np.arange(n) # create array of n elements for x values
    simpArrayY = np.arange(m) # create array of m elements for y values
    xi = a+(simpArrayX*hx) # set x values in new array
    yi = c+(simpArrayY*hy) # set y values in new array
    
    print(xi, yi)

    # set all coefficients to 2
    coeffX = 2*np.ones(n) 
    coeffY = 2*np.ones(m) 
    
    # add special case 4 coeffcient to every other value
    coeffX[1::2] = 4 
    coeffY[1::2] = 4
    
    # add special case 1 coeffcient to first and last element
    coeffX[0] = 1 
    coeffY[0] = 1
    coeffX[-1] = 1
    coeffY[-1] = 1
    
    X,Y = np.meshgrid(xi, yi, indexing='ij') # create meshgrid array
    coeff = np.outer(coeffX, coeffY) # compute products of the array values
    return (h/9)*np.sum(f(X,Y)*coeff)

print()
print ("n,m = 101,101: Area =", simp2d(f2d, a, b, c, d, 101, 101))
print ("n,m = 1001,1001: Area =", simp2d(f2d, a, b, c, d, 1001, 1001))
print ("n,m = 51,101: Area =", simp2d(f2d, a, b, c, d, 51, 101))

#%% 2b) Use mpmath.quad for 2d simpsons

lambdaf = lambda x, y: (((x**2)+y)**(1/2))*(mp.sin(x))*(mp.cos(y)) # set integrand function

quadResult = mp.quad(lambdaf, [a,b], [c,d]) # call quad function
print ("Quad Method: Area =", quadResult)

#%% 2c) Use dblquad for 2d simpsons

dblquadResult = dblquad(lambdaf,c,d,a,b, epsrel=1.e-10) # call dblquad function
print ("DBLQuad Method: (Area, Error) =", dblquadResult)



                     




# %%
