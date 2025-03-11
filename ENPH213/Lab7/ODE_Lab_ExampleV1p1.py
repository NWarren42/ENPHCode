# %% -*- coding: utf-8 -*-
"""
last Edited: March 4, 2024

ODE Stepper Example - I am showing how to use with Euler, but you can add other
ODE solvers in exactly the same way. I am also using the Matlab-like "feval", so
you can can a function and the variables for that function (of any size) 

@author: shugh
"""

import numpy as np
import matplotlib.pyplot as plt
plt.rcParams.update({'font.size': 18}) # keep those graph fonts readable!
plt.rcParams['figure.dpi'] = 120 # plot resolution

# similar to Matlab's feval function - allows one to pass a function and arguments
def feval(funcName, *args):
    return eval(funcName)(*args)

# vectorized forward Euler with 1d numpy arrays
def euler(f, y0, t, h): # Vectorized forward Euler (so no need to loop, even for coupled ODEs) 
    k1 = h*f(y0, t)                     
    y1 = y0+k1
    return y1 

# stepper function for integrating ODE solver over some time array
def odestepper(odesolver, deriv, y0, t):
# simple np array  
    y0 = np.asarray(y0) # convert to numpy just in case a numpy was not sent
    y = np.zeros((t.size, y0.size))
    y[0,:] = y0; h=t[1]-t[0]
    y_next = y0 # initial conditions 

    for i in range(1, len(t)):
        y_next = feval(odesolver, deriv, y_next, t[i-1], h)
        y[i,:] = y_next
    return y

#%%

'''Some function examples'''

# example function 
def fun(y,t):
    return -a1*y # derivative function (right hand side)

def funexact(t):
    return np.exp(-a1*t)

# example function 2
def fun2(y,t):
    return -4*t*y # derivative function (right hand side)

def fun2exact(t):
    return np.exp(-2*t**2) 

# example function 3
def fun3(y,t):
    return -np.sin(t) # derivative function (right hand side)

def fun3exact(t):
    return np.cos(t) 

#%%
'''Simple plotting subroutine'''

def plotme():
    fig = plt.figure(figsize=(8,6))
    ax = fig.add_axes([.12, .15, .4, .4])
    ax.plot(ts, y1, 'gs', label='Euler $n={}$'.format(n), markersize=4)
    ax.plot(ts, y2, '-r', label='Exact', linewidth=3)
    ax.set_xlabel(r'$t$')     
    ax.set_ylabel(r'$y$')
    ax.set_xlim(0, b)
    ax.set_ylim(ymin, ymax)
    ax.legend(loc='best')
    
#%%

'''Test the examples'''

# f' = -a1*y
a,b,y0 = 0.,2.,1.
ymin = 0; ymax = 1.04
a1 = 2; n = 20
ts = a+np.arange(n)/(n-1)*b
y1 = odestepper('euler',fun, y0, ts)
y2 = funexact(ts)
plotme()

#%% increase n to 40 points
a1 = 2; n = 40
ts = a+np.arange(n)/(n-1)*b
y1 = odestepper('euler',fun, y0, ts)
y2 = funexact(ts)
plotme()
    
#%% increase n to 100 points
a1 = 2; n = 100
ts = a+np.arange(n)/(n-1)*b
y1 = odestepper('euler',fun, y0, ts)
y2 = funexact(ts)
plotme()
  
#%% second function example with n= 100
# f' = -4*t*y
n = 100; b= 3
ts = a+np.arange(n)/(n-1)*b
y1 = odestepper('euler',fun2, y0, ts)
y2 = fun2exact(ts)
plotme()    
    
#%% third example
# f' = -np.sin(t)
n = 100; b=np.pi*2
ymin=-1.04; ymax =1.04
ts = a+np.arange(n)/(n-1)*b
y1 = odestepper('euler',fun3, y0, ts)
y2 = fun3exact(ts)
plotme()  

print('--------------------------------')
print('Cool -- This stuff really works!')
print('--------------------------------')