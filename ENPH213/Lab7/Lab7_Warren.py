# %%
import numpy as np
import matplotlib.pyplot as plt
from scipy.optimize import fsolve
from matplotlib.animation import FuncAnimation
plt.rcParams.update({'font.size': 12}) # keep those graph fonts readable!
plt.rcParams['figure.dpi'] = 120 # plot resolution

# similar to Matlab's feval function - allows one to pass a function and arguments
def feval(funcName, *args):
    return eval(funcName)(*args)

# vectorized forward Euler with 1d numpy arrays
def fwdeuler(f, y0, t, h): # Vectorized forward Euler (so no need to loop, even for coupled ODEs) 
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

# %%
# ----------------------
# Question 1a
# ----------------------

def Q1Afct(y, t):
    return -10*y

def Q1AsolExact(t):
    return np.exp(-10*t)

'''Backwards euler solving takes an extra step. Since it is implicitly defined its kind of a pain to work with
we get around this by treating the situation instead as a root problem, where we can rearrange to find an equation
of the form 0 = y0 - y1 + hf(y1, t1), which is convenient because this allows us to solve for the roots of the expression
in terms of y1. I did this with scipy's fsolve function to find the value of y1 that satisifies that equation, then
moved forward with that value as my y(j+1) when implementing the standard backwards euler equation.
''' 
def bwdEulerEqn(yNext, yCurrent, h, f, tNext): # this is the equation that you rearrange to solve with fsolve
    return yCurrent - yNext + h*f(yNext, tNext)

def bwdeuler(f, yCurrent, tNext, h): # and this is the proper output function to give us y(j+1)
    return fsolve(bwdEulerEqn, yCurrent, args=(yCurrent, h, f, tNext))

y0, ts10, ts20 = 1., np.linspace(0, 0.6, 10), np.linspace(0, 0.6, 20)

fwdeulern10Results = odestepper('fwdeuler', Q1Afct, y0, ts10)
fwdeulern20Results = odestepper('fwdeuler', Q1Afct, y0, ts20)

bwdeulern10Results = odestepper('bwdeuler', Q1Afct, y0, ts10)
bwdeulern20Results = odestepper('bwdeuler', Q1Afct, y0, ts20)

fig, (n10plot, n20plot) = plt.subplots(1, 2)

exactts = np.linspace(0, 0.6, 100)
n10plot.plot(exactts, Q1AsolExact(exactts), color='red', label='Exact')
n10plot.plot(ts10, fwdeulern10Results, 'gs', label="F-euler n = 10", markersize=3)
n10plot.plot(ts10, bwdeulern10Results, 'bo', label="B-euler n = 10", markersize=3)
n10plot.set(title="n = 10", xlabel='t', ylabel='y')
n10plot.legend()


n20plot.plot(exactts, Q1AsolExact(exactts), color='red', label='Exact')
n20plot.plot(ts20, fwdeulern20Results, 'gs', label="F-euler n = 20", markersize=3)
n20plot.plot(ts20, bwdeulern20Results, 'bo', label="B-euler n = 20", markersize=3)
n20plot.set(title="n = 20", xlabel='t')
n20plot.legend()

plt.tight_layout()

# %%
# ----------------------
# Question 1b
# ----------------------


def RK4(f, y0, t, h):
    # Standard definitions of RK4 coefficients
    k0 = h*f(y0, t)
    k1 = h*f(y0 + k0/2 ,t + h/2)
    k2 = h*f(y0 + k1/2, t + h/2)
    k3 = h*f(y0 + k2, t + h)
    return y0 + (1/6)*(k0 + 2*k1 + 2*k2 + k3) # Final calculation

def SHO (y, t):
    return np.array([y[1], -y[0]]) # We can model the second order ODE as a system of first order ODEs of this form due to our initial conditions
    # This is a dumbed down version of the function. I maybe should include the angular frequency in this because it is relevant
    # to the solver, however for the case here where omega_0 = 1, this function represents the simplified equation.

def Q1BxsolExact(t):
    return np.cos(t)

# Setting initial conditions for coupled ODEs
y0 = np.array([1, 0])

# Setting t values for different step sizes (0.01, and 0.005)
ts01 = np.arange(0, 2*np.pi*10, 0.01)
ts005 = np.arange(0, 2*np.pi*10, 0.005)

# Solving using RK4
RK401sols = odestepper('RK4', SHO, y0, ts01)
RK4005sols = odestepper('RK4', SHO, y0, ts005)

# Solving using F-euler
fe01sols = odestepper('fwdeuler', SHO, y0, ts01)
fe005sols = odestepper('fwdeuler', SHO, y0, ts005)
realxVals = Q1BxsolExact(ts005)

# Making subplots and cleaning up formatting
fig, ((phaseSpace01, position01), (phaseSpace005, position005)) = plt.subplots(2, 2, figsize=(10, 10))
plt.rcParams.update({'font.size': 18})

# Plotting phase space with position as a function of velocity
phaseSpace01.plot(fe01sols[:,1], fe01sols[:,0], 'r', linestyle='dashed', label='F-E')
phaseSpace01.plot(RK401sols[:,1], RK401sols[:,0], 'b', label='RK4')
phaseSpace01.set(title='Phase Space - dt=0.01', xlabel='v', ylabel='x')
phaseSpace01.legend(loc='center')

phaseSpace005.plot(fe005sols[:,1], fe005sols[:,0], 'r', linestyle='dashed', label='F-E')
phaseSpace005.plot(RK4005sols[:,1], RK4005sols[:,0], 'b', label='RK4')
phaseSpace005.set(title='Phase Space - dt=0.005', xlabel='v', ylabel='x')
phaseSpace005.legend(loc='center')

# Setting new T bound to be in units of period
pos01Ts = np.linspace(0, 10, len(ts01))
pos005Ts = np.linspace(0, 10, len(ts005))

# Plotting x-plots as function of periods elapsed
position01.plot(pos01Ts, RK401sols[:, 0], 'b', label='RK4')
position01.plot(pos01Ts, fe01sols[:, 0], 'r', linestyle='dashed', label='F-E')
position01.plot(pos005Ts, realxVals, 'g', linestyle='dashed', label='Exact')
position01.set(title='Position - dt=0.01', xlabel='t(T)', ylabel='x')
position01.legend(loc='center right')


position005.plot(pos005Ts, RK4005sols[:, 0], 'b', label='RK4')
position005.plot(pos005Ts, fe005sols[:, 0], 'r', linestyle='dashed', label='F-E')
position005.plot(pos005Ts, realxVals, 'g', linestyle='dashed', label='Exact')
position005.set(title='Position - dt=0.005', xlabel='t(T)', ylabel='x')
position005.legend(loc='center right')

plt.tight_layout()
# %%
# ----------------------
# Question 2a
# ----------------------

# Some original parameter definitions
sigma = 10
b = 8/3
r = 28

def R4K3D(fx, fy, fz, x0, y0, z0, ts, h):
    n = len(ts)
    x, y, z = [np.zeros(n) for _ in range(3)]
    x[0], y[0], z[0] = x0, y0, z0

    for i in range(1, n): 
        # Lorenz equations have no time dependency so that term of the RK4 solver is not included
        # This is how we calculated the k values for each x, y, z term then
        # im using some inline for logic to make it a bit more condensed, but its just evaluating each
        # derivative function at each point
        k0x, k0y, k0z = (h*f(x[i-1], y[i-1], z[i-1]) for f in (fx, fy, fz))
        k1x, k1y, k1z = (h*f(x[i-1]+k0x/2, y[i-1]+k0y/2, z[i-1]+k0z/2) for f in (fx, fy, fz))
        k2x, k2y, k2z = (h*f(x[i-1]+k1x/2, y[i-1]+k1y/2, z[i-1]+k1z/2) for f in (fx, fy, fz))
        k3x, k3y, k3z = (h*f(x[i-1]+k2x, y[i-1]+k2y, z[i-1]+k2z) for f in (fx, fy, fz))

        # this is where we actually solve for each value
        x[i] = x[i-1] + (1/6) * (k0x + 2*k1x + 2*k2x + k3x)
        y[i] = y[i-1] + (1/6) * (k0y + 2*k1y + 2*k2y + k3y)
        z[i] = z[i-1] + (1/6) * (k0z + 2*k1z + 2*k2z + k3z)
    
    return x, y, z

def fx(x, y, z, sigma=sigma):
    return sigma*(y-x)

def fy(x, y, z, r=r):
    return r*x - y - x*z

def fz(x, y, z, b=b):
    return x*y - b*z

# Feeding two very slighlty different start values in to demonstrate butterfly
startPos1 = [1, 1, 1.001]
startPos2 = [1, 1, 1]

h = 0.01
tVals = np.arange(0, 2*np.pi*4, h)

x1, y1, z1, = R4K3D(fx, fy, fz, *startPos1, tVals, h)
x2, y2, z2, = R4K3D(fx, fy, fz, *startPos2, tVals, h)

fig = plt.figure(figsize=(9,9))
ax = fig.add_subplot(projection='3d')
ax.view_init(azim=10, elev=15)

plt.rcParams.update({'font.size': 12}) # keep those graph fonts readable!
plt.rcParams['figure.dpi'] = 120 # plot resolution

ax.plot(x1, y1, z1, color='b', linestyle='dashed', linewidth=1, label=f"P0 = {startPos1}")
ax.plot(x2, y2, z2, color='r', linewidth=1, label=f"P0 = {startPos2}")
ax.legend()
ax.set(title='Lorentz Attractor', xlabel='x', ylabel='y', zlabel='z')
fig.show()

# %%
# ----------------------
# Question 2b
# ----------------------

%matplotlib auto

# Initial figure setup, I prefer this angle to the one specified by prof, hughes but its the same thing
fig = plt.figure(figsize=(9,9))
ax = fig.add_subplot(projection='3d')
ax.view_init(azim=10, elev=15)

# Just cleaning the graph up a little bit
plt.rcParams.update({'font.size': 12})
plt.rcParams['figure.dpi'] = 120

# Setting up the intial blank paths that I want to show. Initially they have no data in them
# but that gets upated throughout the animation
path1, = ax.plot([], [], [], color='b', linestyle='dashed', linewidth=1, label=f"P0 = {startPos1}")
path2, = ax.plot([], [], [], color='r', linewidth=1, label=f"P0 = {startPos2}")
ax.set(title='Lorentz Attractor', xlabel='x', ylabel='y', zlabel='z', 
                                  xlim=[-20, 20], ylim=[-20, 20], zlim=[0, 50])
plt.legend()

# Actual animation function here that is constantly updating the data available to the paths being plotted
def tracePath(frameNum):
    path1.set_data(x1[:frameNum], y1[:frameNum])
    path1.set_3d_properties(z1[:frameNum])

    path2.set_data(x2[:frameNum], y2[:frameNum])
    path2.set_3d_properties(z2[:frameNum])

    return path1, path2

ani = FuncAnimation(fig, tracePath, frames=len(x1), interval=10)

# I saved it and submitted the file alongside my code because I write my code in vscode, and although
# I copy pasted my code into spyder to double check I was still having some inconsistencies with the 
# animation so this was just a precaution. It should work fine... I think.... Needed to install ffmpeg
# to get it to save properly so that was fun. Atleast now I know how to do it :D

#ani.save('LorenzSim.mp4') 

# -- I also saves a .gif file as a test but the animation was really slow, maybe gifs cap their update speed?
# dunno

plt.show()