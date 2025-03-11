# Author: S Hughes, Queen's U
# Last modidied, Feb 6-13, 2024
# More Python Stuff  - Weeks 5 and 6

# usual imports to use here
import matplotlib.pyplot as plt 
import math as m 
import numpy as np
plt.rcParams['figure.dpi'] = 100 # resolution on screen
plt.rcParams.update({'font.size': 22}) # keep those fonts nice and readable


'''
Run in sections below, especially ValueError will jump out of code
'''

#%%


'''
Functions using math and numpy, and calling them with arrays
'''

# a maths function
def f1(x):
    return m.exp(x - m.sqrt(x)) - x

# a numpy function
def f2(x):
    return np.exp(x - np.sqrt(x)) - x 


# set up an x array from xmin to xmax, over npoints, call function
npoints = 1000
xmin = 2; xmax = 3.
xlist = [xmin+(i)/(npoints-1)*(xmax-xmin) for i in range(npoints)]
fun_m = [f1(xlist[i]) for i in range(npoints)]

# or if using numpy 
x_np = xmin + (xmax-xmin)*np.arange(npoints)/(npoints-1)
fun_np = f2(x_np)

# plot both and check they are the same!
fig = plt.figure(figsize=(8, 6))
plt.plot(xlist,fun_m,'r',linewidth=3)
plt.plot(xlist,fun_np,'c--',linewidth=2)
plt.grid()
plt.ylabel('$f(x)$')
plt.xlabel('$x$')
plt.xlim(xmin,xmax)
plt.ylim(-0.25,0.6)
plt.tight_layout()
plt.grid('on')

#%%

'''
Vectorized sums
Let's say we want to compute:
    fun_sum = sum_i x_np[i] fun_np[i]
'''

# method 1 - non vectorized way
fun_sum1 = 0.
for i in range(npoints):
    fun_sum1 += x_np[i] * fun_np[i]

print('fun_sum1 is:\n', fun_sum1)

# other ways?

fun_sum2 = np.sum(x_np * fun_np)

print('fun_sum2 is:\n', fun_sum2)

# other ways?

fun_sum3 = x_np @ fun_np

print('fun_sum3 is:\n', fun_sum3)

#%%

# let's time these computations and make the arrays bigger

import timeit

npoints = 10000000 # this is a lot of points!
x_np = xmin + (xmax-xmin)*np.arange(npoints)/(npoints-1)
fun_np = f2(x_np)

start = timeit.default_timer()
fun_sum1 = 0.
for i in range(npoints):
    fun_sum1 += x_np[i] * fun_np[i]
stop = timeit.default_timer()
time1 = stop-start
print('time1:',time1)

start = timeit.default_timer()
fun_sum2 = np.sum(x_np * fun_np)
stop = timeit.default_timer()
time2 = stop-start
print('time2:',time2)

start = timeit.default_timer()
fun_sum3 = x_np @ fun_np
stop = timeit.default_timer()
time3 = stop-start
print('time3:',time3)

print('method 2 is', int(time1/time2), 'times after than method 1')

print('method 3 is', int(time1/time3), 'times after than method 1')

methods = np.array([time1,time2,time3])
imax = np.argmin(methods)
print('And the winner is, Method',imax)

'''
So the Matrix Multiplication wins - exploit @ when you can as it 
is highly optimizes and uses the BLAS librar:
BLAS: Basic Linear Algebra Subprograms
https://www.netlib.org/blas/    
'''


# Some other useful stuff to know:
# Feb 13, 2024
# week 6
    
#%%

''' calling a double function - 
I ask you to return N sets of functions in Q3 of lab 4.
  Here is a simple example of calling a subroutine that returns two function evalutions 
'''

def fs1(xs):
    # extract the two values
    x0 = xs[0]
    x1 = xs[1]
    # or in a more compact way
    x0, x1 = xs
    print('x0 is:', x0)
    print('x1 is:', x1)
    f0 = x0 +  2*x1**2
    f1 = x0**2 + x1 
    return np.array([f0,f1])

xbold = np.array([1.,2.])
print('The function f(xbold) is:', fs1(xbold)) 



#%%
'''
Setting up big ONE and a matrix of zeros (say ZERO)
'''
n = 4
ONE = np.identity(n) # identity
print('ONE (identity)\n', ONE)

# or use eye
ONE = np.eye(n)
print('ONE (eye)\n', ONE)

# eye has a bit more control, e.g. (can shift the ones up 1)
ONE = np.eye(n, k=1)
print('ONE MODIFIED (eye)\n', ONE)

ZERO = np.zeros((n,n))
print('ONE\n', ONE)
print('ZERO\n',ZERO)
print('-----------------')



#%%
# Numpy matrix solvers

# from the matrix lab
A = np.array([2., 1., 1., 2., 1., -4., 1., 2., 1.]).reshape(3,3)
bs = np.array([8., -2., 2.])

print('A\n',A)
print('bs\n',bs)

# previously you coded something like this
# xs = gauelim_pivot(A,bs); print('my xs=', xs)

# You can also use numpy's solver for lab 4:
    
import numpy.linalg as lg
print('-----------------')
xs = lg.solve(A,bs); print('numpy solution, xs=', xs)
print('-----------------')



#%% calling a function within a function, e.g., to check some errors

'''this was mentioned by the TA to cause some confusion, but it is certainly
ok to call a common function within another function of subroutine'''

# consider a common error check, could be nice compact function 
def error_check(x_old,x_new):
    errs = np.abs((x_new - x_old)/x_new)
    return np.sum(errs)

def fun(xs_old, kmax=10, tol=1.e-6):
    delta = 1.e-9*xs_old # just a forced example, not really doing much!
    for k in range(1,kmax):
        xs_new = xs_old + delta # so delta could be something like roots
        err = error_check(xs_old,xs_new)
 
        if err < tol:
            print('nice - we found a solution')
            break # exit the loop

        xs_old = np.copy(xs_new)
    else:
        print('not nice - we did not find a solution!')
        xs_new = None
    return xs_new,err

xs = np.ones(50)
xs_new,err = fun(xs,tol=1.e-7)
print('This one immediately finds a solution, e.g.:\n', xs_new[0],err)
print('-----------------')

xs_new,err = fun(xs,tol=1.e-8)
print('This one does not find a solution:\n', xs_new, err)
print('-----------------')


#%%
'''Of course, we can also pass numpy functions to other numpy functions, 
such as:
'''

data_x = -np.cos(np.linspace(0,np.pi,20))
data_y = np.ones(len(data_x))

# which is useful for the inperpolation functions - with Chebyshev nodes

# let's plot the data to see the spacings
plt.rcParams.update({'font.size': 20})
plt.rcParams['figure.dpi'] = 80
fig = plt.figure(figsize=(12,6))
ax = fig.add_axes([.16, .16, .36, .66])
ax.set_title('Chebyshev nodes')
ax.plot(data_x,data_y,'or',ms=8)
ax.set_xlabel(r'$x$ data')     
ax.set_ylabel(r'$y$ data'); 


#%% raising an error (exception) within a function

def fun1(a):
    if a == 0:
        raise ValueError('Oops, we have a problem here!')
# Note cannot use break here as no loop
# here we use ValueError to handle exceptions for using our function        

    ans = 1/a # so we want to avoid dividing by zero
    return ans

c = fun1(2.)
print('Solution is:', c)
print('-----------------')
#%%

c = fun1(0.)
print('Solution is:', c) # these lines will not run
print('-----------------')

#%%

#Python uses these as well, for example:
#import math as m
print('this has a problem:')
b = m.sqrt(-10)
print('-----------------')


#%%
'''
With the above example, let's look at evaluationg sqrt(-10)'
'''

import cmath as cm
b = cm.sqrt(-10)
print('no problem with cmath module:')
print(b)
print('-----------------')


#%%
print('what about?')
b = np.sqrt(-10)
print(b)
print('-----------------')



#%%

b = np.sqrt(-10., dtype=np.complex64)
print('this numpy is ok though:', b)
print('-----------------')

b = pow(-10.,0.5)
print('and so is this:', b)
print('-----------------')

b = pow(-10.,0.5)
print('and so is this:', b)
print('-----------------')


#%%

b = -10.**0.5
print('what about this?', b)
print('-----------------')


#%%

b = (-10.)**0.5
print('this is clearer:', b)
print('-----------------')


'''
Why are some values that work different?
''';

#%%
'''
The reason for the small differences with working examples
is due to machine precision
''';

eps = np.finfo(complex).eps
print('The methods evalue to within machine precision:', eps)
print(' and the sqrt one uses a differnet method')
print('-----------------')


#%% The continue function
'''
Common application might be in a double form loop to continue at an exception
'''

# Example
sum = 0.; n = 3

for k in range(n): 
    for j in range(n):
        if k == j: continue # includes all j apart from j=k
        print(k,j)
        sum = sum + k*j

print('...and the sum is:', sum)
print('-----------------')


#%% Setting up a sphere and simple 3d graphics

npoints = 30
# set up theta and phi arrays, can also use numpy
theta = [i/(npoints-1)*m.pi for i in range(npoints)]
phi = [i/(npoints-1)*2*m.pi for i in range(npoints)]

# meshgrid is much faster here, as exploits vectorization
PHI, THETA = np.meshgrid(phi, theta)

# spoherical coordinates
# e.g., https://en.wikipedia.org/wiki/Spherical_coordinate_system
'''
x = r sin (theta) cos (phi)
y = r sin (theta) sin (phi)
z = r cos(theta)
'''

# and now we call the x,y,z values
x = np.sin(THETA)*np.cos(PHI)
y = np.sin(THETA)*np.sin(PHI)
z = np.cos(THETA) 

'''
note each one of these is now of shape (npoints,npoints)
since we are using meshgrid 
numpy.meshgrid function is used to create a rectangular 
grid out of two given one-dimensional arrays representing 
the Cartesian indexing or Matrix indexing
meshgrid is very useful to evaluate functions on a grid. 
If the function depends on all coordinates, both dense 
and sparse outputs can be used.
'''

#https://matplotlib.org/stable/gallery/mplot3d/surface3d.html

# plot the sphere (simple graphics - you can improve this!)
from matplotlib import cm # want to use map colors
fig = plt.figure(figsize=(4, 6))
ax = fig.add_subplot(1, 1, 1, projection='3d')

# Label axes.
ax.set_xlabel('x')
ax.set_ylabel('y')
ax.set_zlabel('z')

# plot the sphere with some transparency (1 is none)
surf2 = ax.plot_surface(x, y, z, cmap=cm.prism_r,alpha=0.4 )
# or could try cm.winter, etc

# list of colormaps here
#https://matplotlib.org/stable/users/explain/colors/colormaps.html

print('----------------------')
print('finished - have a great reading week!')



