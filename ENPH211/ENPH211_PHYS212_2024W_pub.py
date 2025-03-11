#!/usr/bin/env python
# coding: utf-8

# ENPH 211 / PHYS 212 2024W
# ====
# Student names:
# ------
# Submit your code, a pdf of the code, and pdfs of any figures you make.  Ensure your figures are labelled and titled.
# ------

# The following code solves the second order linear differential equation  $\ddot{\theta} + \ \omega_0^2 \ \sin \theta = 0$.


#%% Load libraries
import numpy as np
from scipy.integrate import odeint
import matplotlib.pyplot as plt



#%% Parameters
omega_0_rads = 1.0 # Natural angular frequency

theta0_rad, thetaDot0_rads = 0.7 * np.pi, 0.0 # Initial position and velocity

outpath = "./figure_" # Where figure goes



#%% Do the numerical integration
def dU_dt(U, t):
    # Here U is a vector such that y=U[0] and z=U[1]. This function should return [y', z']
    return [U[1], - omega_0_rads**2 * np.sin(U[0])]

U0 = [theta0_rad, thetaDot0_rads]
ts, tIncrement_s = np.linspace(0, 9 * np.pi / omega_0_rads, 300, retstep=True)
Us = odeint(dU_dt, U0, ts)
thetas = Us[:,0]



#%% Plot
plt.xlabel("t (s)")
plt.ylabel(r"$\theta $ (rad)")
plt.title("Oscillator")
plt.plot(ts, thetas, label='pos')

plt.show(); plt.clf()


#%%

# Q1) (3 pts) Numerically determine the period of the previous oscillator, 
# for instance by identifying consecutive samples of opposite sign.
# ----


# Here's the cheater method of using an already nicely created scipy function
from scipy.signal import find_peaks

def scipyPeriod (thetas):
    peaksInd, _ = find_peaks(thetas)
    return ts[peaksInd[1]] - ts[peaksInd[0]]

print(f"Period of the given oscillator using Scipy is {scipyPeriod(thetas):.2f} seconds")

# Here's the suggested method

def getApproxPeriod(thetas):
    currentState = None
    switchState = None

    switchIndices = []
    for i in range(len(thetas)):
        if thetas[i] < 0: currentState = False
        else: currentState = True # Checking +/- state of theta value
            
        if currentState != switchState: # we only care about +/- transition points so check current state of function. True is pos, False is neg 
            switchIndices.append(i)
            switchState = currentState

    return (switchIndices[2] - switchIndices[1])*2*tIncrement_s # Taking index 3 and 1 because first switch index will always be zero the way that this has been coded (because going from none to True or False is a state switch)

print(f"Period of the given oscillator using sign switching is {getApproxPeriod(thetas):.2f} seconds")


#%%
# Q2 (3 pts) Reproduce the previous plot over roughly 2 periods with the harmonic approximation overlayed.
# ---


def smallAngleApproxdU_dt(U, t):
    # Here U is a vector such that y=U[0] and z=U[1]. This function should return [y', z']
    return [U[1], - omega_0_rads**2 * U[0]]

Us = odeint(dU_dt, U0, ts[:int((4/5)*300)])
Uthetas = Us[:, 0]

sAAUs = odeint(smallAngleApproxdU_dt, U0, ts[:int((4/5)*300)])
sAAThetas = sAAUs[:, 0]

plt.xlabel("t (s)")
plt.ylabel(r"$\theta $ (rad)")
plt.title("Oscillator")

plt.plot(ts[:int((4/5)*300)], Uthetas)
plt.plot(ts[:int((4/5)*300)], sAAThetas)


plt.show(); plt.clf()


#%%
# Q3 (3 pts) Determine the relative difference between the period and the harmonic approximation ((true - harmonic) / true)
# ---

def getRelativeDiff(tru, approx):
    return 100*(tru-approx)/tru

truePeriod = getApproxPeriod(Uthetas) 
approxPeriod = getApproxPeriod(sAAThetas)


print(f"The true period of the oscillator is {truePeriod:.2f}s")
print(f"The approximate harmonic period of the oscillator is {approxPeriod:.2f}s")
print(f"\nThe relative difference in period is {getRelativeDiff(truePeriod, approxPeriod):.2f}%")


#%%
# Q4 (4 pts) Scanning starting angles over angles from close to 0 to close to $\pi$ radians, plot the period vs the starting angle, and the relative difference with the harmonic approximation vs the starting angle.
# ---

startingAngles = np.delete(np.linspace(0, np.pi, 502), [0, -1]) # Creating a linear space between 0 and pi, then dropping the 0, and pi elements

periods = []
for i in range(len(startingAngles)):
    periods.append(getApproxPeriod(odeint(dU_dt, [startingAngles[i], thetaDot0_rads], ts[:int((4/5*300))])[:, 0]))

periods = np.array(periods)

plt.xlabel("Starting Angle (rad)")
plt.ylabel("Period (s)")
plt.title("Period vs Starting angle")

plt.plot(startingAngles, periods)
plt.show()

plt.xlabel("Starting Angle (rad)")
plt.ylabel("Relative Difference")
plt.title("Accuracy of harmonic approximation")

plt.plot(startingAngles, getRelativeDiff(truePeriod, periods))
plt.show()

# %%
