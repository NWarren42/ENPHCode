# %% 
import numpy as np
import matplotlib.pyplot as plt
from numpy.linalg import norm

from numpy.fft import fft2, ifft2
import time

plt.rcParams.update({'font.size': 12}) # keep those graph fonts readable!
plt.rcParams['figure.dpi'] = 120 # plot resolution

# %%
# ----------------------
# Question 1
# ----------------------

def Q1initialTemp(x):
    return 20 + 30 * np.exp(-100*(x-0.5)**2)

def HeatEquation1D(initialTemps, tElapsed, alpha, endTemp, dt=0.1, dx=0.01):
    
    k = alpha*(dt/(dx**2))
    if k > 0.5: raise Exception("Chosen alpha and step sizes invalidate Caurant stability criteria") 

    numIterations = tElapsed/dt


    u = np.copy(initialTemps)
    for i in range(0, int(numIterations)):
        oldU = np.copy(u)

        # Setting all values for u except end conditions
        u[1:-1] = oldU[1:-1] + k * (oldU[2:] - 2*oldU[1:-1] + oldU[:-2])
        
        # Setting end conditions. Since we never actually change them up above, 
        # technically this is redundant as they're set by default but this helps
        # clarify that ends are always the same temp
        u[0] = endTemp
        u[-1] = endTemp
    
    return u



alpha = 2.3e-4
uEnds = 20

xVals = np.linspace(0, 1, 100)
initialTemps = Q1initialTemp(xVals)

tVals = [0, 5, 10, 20, 30, 60]

# Plot Setup

fig, ax1 = plt.subplots(1, 1, figsize= (8, 5))

ax1.set(title="Temperature in a rod with T=20 at the ends, and some starting temperature",
        xlabel="Rod Length [m]", ylabel="Temperature [C]")

for t in tVals:
    data = HeatEquation1D(initialTemps, t, alpha, uEnds)
    ax1.plot(xVals, data, label=f"Time = {t:.0f}")

ax1.legend()
plt.show()


# %%
# ----------------------
# Question 2a
# ----------------------

def Q2ChargeFct(x, y):
    return np.cos(10*x) - np.sin(5*y - np.pi/4)

def jacobiIterationPoissons(xGrid, yGrid, phi, fct, walls=(0,0,0,0), tol=1e-5):
    
    dx = xGrid[0, 1] - xGrid[0, 0]
    dy = yGrid[1, 0] - yGrid[0, 0]

    relChange = tol + 1 # Forcing some value greater than tolerance so the loop can run one minimum one time. Missing the do-while loop from C right now :')
    
    while relChange > tol:
        newPhi = np.zeros_like(phi)

        # Setting phi+1 grid using the general term for a jacobi iteration
        newPhi[1:-1, 1:-1] = (1/(2*(dx**2 + dy**2))) * (dy**2*(phi[:-2, 1:-1] + phi[2:, 1:-1]) +
                                      dx**2*(phi[1:-1, :-2] + phi[1:-1, 2:]) - 
                                      (dx**2)*(dy**2)*fct(xGrid[1:-1, 1:-1], yGrid[1:-1, 1:-1]))

        # Set wall conditions
        newPhi[0, :] = walls[0] # bottom wall
        newPhi[-1, :] = walls[1] # top wall
        newPhi[:, 0] = walls[2] # left wall
        newPhi[:, -1] = walls[3] # right wall
        
        relChange = norm(newPhi - phi)/norm(newPhi)
        phi = newPhi
    
    return phi


xVals = np.linspace(0, 2, 200)
yVals = np.linspace(0, 1, 100)

# Setting up corresponding x-y grids
xGrid, yGrid = np.meshgrid(xVals, yVals)

# Setting up proper size of array for charge densities
initialPhi = np.zeros_like(xGrid)

# Calling function to solve the grid
solvedVals = jacobiIterationPoissons(xGrid, yGrid, initialPhi, Q2ChargeFct)

# Force 2:1 aspect ratio
fig = plt.figure(figsize=(10, 5))
ax = fig.add_subplot()
heatMap = plt.imshow(solvedVals, extent=[0, 2, 0, 1], cmap="magma", origin="lower")

ax.set_xlabel('x')
ax.set_ylabel('y')

ax.set_xlim(0, 2)  # Set x limits
ax.set_ylim(0, 1)  # Set y limits

ax.set_title("Solution to the given charge function found through Jacobi iteration")

# Colour bar setup
colorBar = fig.colorbar(heatMap)
colorBar.set_label("Charge density (x, y)")
colorBar.ax.yaxis.set_label_position("left")

plt.show()


# %%
# ----------------------
# Question 2b
# ----------------------

xVals = np.linspace(0, 2, 200)
yVals = np.linspace(0, 1, 100)

xGrid, yGrid = np.meshgrid(xVals, yVals)

# Setting up proper size of array for charge densities
initialPhi = np.zeros_like(xGrid)

# Exact same code as above, only difference is that the wall conditions have changed
solvedVals = jacobiIterationPoissons(xGrid, yGrid, initialPhi, Q2ChargeFct, walls=(0.2, 0.1, 0.3, 0.4))

fig = plt.figure(figsize=(10, 5))
ax = fig.add_subplot()
heatMap = plt.imshow(solvedVals, extent=[0, 2, 0, 1], cmap="magma", origin="lower")
ax.set_xlabel('x')
ax.set_ylabel('y')

ax.set_xlim(0, 2)  # Set x limits
ax.set_ylim(0, 1)  # Set y limits

ax.set_title("Solution to the given charge function found through Jacobi iteration")
colorBar = fig.colorbar(heatMap)
colorBar.set_label("Charge density (x, y)")
colorBar.ax.yaxis.set_label_position("left")

plt.show()

# %%
# ----------------------
# Bonus Q
# ----------------------

def bonusQfct (x, y):
    return np.cos(3*x + 4*y) - np.cos(5*x - 2*y)

# Taking start time
startTime = time.time()

numPoints = 800

# set up x/y bounds and pick out the step size
xVals, dx = np.linspace(0, 2*np.pi, numPoints, retstep=True)
yVals, dy = np.linspace(0, 2*np.pi, numPoints, retstep=True)

xGrid, yGrid = np.meshgrid(xVals, yVals)

# evaluate the given function over the whole grid
fctVals = bonusQfct(xGrid, yGrid)

# take fft of the function values
fftVals = fft2(fctVals)

# Computing k and l values to use in the solved
kVals = np.fft.fftfreq(numPoints, d=dx)[:, np.newaxis]
lVals = np.fft.fftfreq(numPoints, d=dx)[np.newaxis, :]

# Preliminary denominator calculation for clarity
denominator = np.cos(2*np.pi*kVals/numPoints) + np.cos(2*np.pi*lVals/numPoints) - 2

# Avoiding a div by 0 error since k and L both have an element at 0
denominator[0,0] = 1

# Charge density calculation in fourier space
phiFourier = (dx**2 * fftVals)/(2*denominator)

# Taking ifft of fourier space data and putting it in fractions of pi
phi = np.real(ifft2(phiFourier))/np.pi

# Taking end time
endTime = time.time()
print(f"Solution found in {endTime-startTime:.2f} seconds")

fig = plt.figure(figsize=(10, 5))
ax = fig.add_subplot()
heatMap = plt.imshow(phi, extent=[0, 2, 0, 2], cmap="magma", origin="lower")
ax.set_xlabel('x [pi]')
ax.set_ylabel('y [pi]')

ax.set_xlim(0, 2)  # Set x limits
ax.set_ylim(0, 2)  # Set y limits

ax.set_title("Solution to periodic Poisson's function\nas found by solving in fourier space")
colorBar = fig.colorbar(heatMap)
colorBar.set_label("Real charge density (x, y)")
colorBar.ax.yaxis.set_label_position("left")


# %%
