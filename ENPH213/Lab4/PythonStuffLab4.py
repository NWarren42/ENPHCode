# Author: S Hughes, Queen's U
# Last modidied, Feb 1, 2024
# Some Python Stuff  - Week 4

# usual imports to use here
import matplotlib.pyplot as plt 
import math as m 
import numpy as np

# set up function in lecture
def f1(x):
    return m.exp(x - m.sqrt(x)) - x
# same but with numpy arrays
def f2(x):
    return np.exp(x - np.sqrt(x)) - x

def bisection(f,x0,x1,nmax=200,eps=1.e-8):
#    print(nmax,eps) # uncomment if you want to see these values
    for i in range(nmax):
        x2 = (x0+x1)/2
        
        if f(x0)*f(x2) < 0:
            x1 = x2
        else:
            x0 = x2
            
        xnew = (x0+x1)/2
        xdiff = abs(xnew-x2)

        if abs(xdiff/xnew) < eps:
            break

    else: # does this is xnew was not found within nmax iterations
        xnew = None

    return xnew


#%% Let first look at the function - call it and plot it

# set up sensible x array
npoints = 100
xmin = 0.1; xmax = 3.
xlist = [xmin+(i)/(npoints-1)*xmax for i in range(npoints)]
fun = [f1(xlist[i]) for i in range(npoints)]

# or if using numpy
x_np = xmin + (xmax-xmin)*np.arange(npoints)/(npoints-1)
fun_np = f2(xlist)

# plot both to check it
fig = plt.figure(figsize=(7, 6))
ax = fig.add_axes([.2, .2, .7, .7])
# these next two lines are very useful - controls font sizes and resolution 
plt.rcParams.update({'font.size': 20}) # fonts (min, unless given)
plt.rcParams['figure.dpi'] = 120 # resolution on screen
plt.plot(xlist,fun,color='b',linewidth=2)
plt.plot(xlist,fun_np,'-.', color='orange', linewidth=2)
plt.xlabel('$x$')
plt.ylabel('$f(x)$')
ax.set_xlim(0.4,3)
ax.set_ylim(-0.4,1)
ax.grid()


#%% Check solution near right and left root

# this changes the default nmax and eps values in function
#root = bisection(f1,1.5,3,eps=1.e-4)
# this changes the default eps only (similarly for nmax) 
#root = bisection(f1,1.5,3,eps=1.e-4)
# you test this by printing these out in function (uncomment)

# this uses the default nmax and eps values in function
root = bisection(f1,1.5,3)

eps=1.e-6
print(root)
print(f1(root+eps))
print(f1(root-eps))
print('should be near 2.5!')
print('-----------------------')

root = bisection(f1,0.5,1.2)
eps=1.e-6
print(root)
print(f1(root+eps))
print(f1(root-eps))
print('should be near 1!')
print('-----------------------')

