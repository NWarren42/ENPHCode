#%%
import numpy as np
import matplotlib.pyplot as plt

# %%
# ----------------------
# Question 1a
# ----------------------

circleRadius = 0.5
numPoints = 1000

# Creating random points
randPoints = np.random.uniform(-0.5, 0.5, size=(numPoints, 2))

# Check if points fall in circle radius using distance
distances = np.linalg.norm(randPoints, axis=1)
countInside = np.sum(distances < circleRadius)

piApprox = (4*countInside/numPoints)

fig, ax = plt.subplots(1, 1)

# Shapes
displaySquare = plt.Rectangle((-0.5, -0.5), 1, 1, ec = 'black', fc = 'none')
displayCircle = plt.Circle((0, 0), circleRadius, ec = 'black', fc = 'blue')

ax.add_artist(displaySquare)
ax.add_artist(displayCircle)
# plotting points with random rgb values
ax.scatter(randPoints[:, 0], randPoints[:, 1], c=np.random.rand(numPoints, 3), s=10)

ax.set(title=f"Pi = {piApprox}, for n={numPoints}", 
       xlim=(-0.5, 0.5), ylim=(-0.5, 0.5))
ax.set_aspect("equal")

# %%
# ----------------------
# Question 1b
# ----------------------

def integrand(x):
    return np.exp(x)

def monteCarloIntegration(fct, lowerBound, upperBound, numPoints):
    xVals = np.random.uniform(lowerBound, upperBound, numPoints)
    yVals = fct(xVals)
    return (upperBound - lowerBound) * np.sum(yVals)/numPoints

numPoints = 500

# Creating sample points from 10^2 to 10^6. Forcing integer because non-integer sampling points makes no sense
numSamplePoints = np.logspace(2, 6, numPoints, dtype=int)

# Computing the monte carlo integration for each sampling point count
mcVals = [monteCarloIntegration(integrand, 0, 1, i) for i in numSamplePoints]

fig, ax = plt.subplots(1, 1)

ax.scatter(numSamplePoints, mcVals, color='blue', label="MC", s=10)
ax.hlines(np.e-1, 1e2, 1e6, color='orange', linewidth=3, label="Exact")
ax.set_xscale('log')
ax.set(xlabel="Num Iterations", ylabel="Integral Value")
ax.legend()

# %%
# ----------------------
# Question 2
# ----------------------
epsilon = 1

def setupSpins(numSpins, orderParam, epsilon=epsilon):
    spins = np.ones(numSpins) # Setting up proper array size
    spins = np.where(np.random.rand(numSpins) < orderParam, -1, spins) # Setting some values to -1 instead of 1
    totEnergy = -epsilon * np.sum(spins * np.roll(spins, -1)) # Calculating energies
    totMagnet = np.sum(spins) # Calculating magnetism
    
    return spins, totEnergy, totMagnet

def update(spins, kT, totEnergy, totMagnetism, epsilon=epsilon):
    numSpins = len(spins)
    
    # Picking a random spin to try to flip and calculating the resulting energy change
    randSpinIndex = np.random.randint(0, numSpins)
    energyChange = 2 * epsilon * spins[randSpinIndex] * (spins[randSpinIndex - 1] + spins[(randSpinIndex + 1)% numSpins])
    
    # Seeing if the flip is valid
    if energyChange < 0 or np.random.rand() < np.exp(-energyChange/kT):
        spins[randSpinIndex] *= -1
        totEnergy += energyChange
        totMagnetism -= 2 * spins[randSpinIndex]

    return totEnergy, totMagnetism

def metropolis(numSpins, orderParam, kTVal, numIterations):
    spins, totEnergy, totMagnetism = setupSpins(numSpins, orderParam)

    # Setting up storage arrays for spin, energy, and magnetism values
    spinStates = np.zeros((numIterations, numSpins))
    spinStates[0] = spins

    energyVals = [totEnergy]
    magnetismVals = [totMagnetism]

    for i in range(1, numIterations):
        # Running calculations to update sim data
        totEnergy, totMagnetism = update(spins, kTVal, totEnergy, totMagnetism)
        
        # Storing new state of system
        spinStates[i] = spins[:]
        energyVals.append(totEnergy)
        magnetismVals.append(totMagnetism)

    return np.array(spinStates), np.array(energyVals), np.array(magnetismVals)

numSpins = 50
numIterations = 40*numSpins

kTVals = (0.1, 0.5, 1.)

# Setting up a couple different parameters to look at 0.9 being colder start, 0.1 being hotter
orderParams = (0.1, 0.3, 0.6, 0.9)


for param in orderParams:
    fig, ax = plt.subplots(2, len(kTVals), figsize=(12, 8))
    
    for i, kT in enumerate(kTVals):
        spins, energyVals, magVals = metropolis(numSpins, param, kT, numIterations)
        
        # Normalizing Energy
        energyVals_norm = energyVals/(numSpins * epsilon)
        analyticalEnergy = -epsilon * np.tanh(epsilon/kT) # Finding analytical average for when system hits equilibrium
        
        ax[0, i].imshow(spins.T, cmap='PuOr', extent = [0, numIterations/numSpins, 0, numSpins])
        ax[0, i].set(title=f"Spins states with kT = {kT}",
                     xlabel="Iterations/numSpins",
                     ylabel="Spins")
        
        ax[1, i].plot(np.arange(numIterations)/numSpins, energyVals_norm, color='blue', label='State Energy')
        ax[1, i].hlines(analyticalEnergy, 0, numIterations/numSpins, color='red', label='Analytical Energy')
        ax[1, i].set(title=f"Total Energy for kT = {kT}",
                     xlabel="Iterations/numSpins",
                     ylabel="Spins")
        ax[1, i].legend()

    fig.suptitle(f"Starting Param = {param}")
    plt.tight_layout()