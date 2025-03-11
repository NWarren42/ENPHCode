# %%

import numpy as np
import matplotlib.pyplot as plt

# %%

# ----------------------
# Question 1a
# ----------------------

def configurableSinusoidal(t, aVals=[3, 1, 0.5], wVals=[1, 4, 7]):
    return aVals[0]*np.sin(wVals[0]*t) + aVals[1]*np.sin(wVals[1]*t) + aVals[2]*np.sin(wVals[2]*t)

def myDFT(fct, xVals):

    yVals = fct(xVals)

    numVals = len(xVals)

    if numVals % 2 != 0:
        raise ValueError("Size of array passed to the dft function must be even")

    jVals = np.arange(numVals)
    kVals = jVals.reshape((numVals, 1))
    return yVals, np.dot(np.exp(-2j*np.pi*kVals*jVals/numVals), yVals)

xVals30n = np.linspace(0, 2*np.pi, 30)
xVals60n_lin = np.linspace(0, 2*np.pi, 60)

yVals30n, n30DFTresults = myDFT(configurableSinusoidal, xVals30n)
yVals60n, n60DFTresults = myDFT(configurableSinusoidal, xVals60n_lin)

# The plots shown below use the linspace function so some smaller frequencies come out of the dft
# this means it doesn't look exactly like the example graph, however this is fixed in Q1B where 
# linspace and arange are compared.

fig, (fctPlot, dftPlot) = plt.subplots(1, 2)

fctPlot.plot(xVals30n, yVals30n, label='n = 30')
fctPlot.plot(xVals60n_lin, yVals60n, linestyle='dashed', label='n = 60')
fctPlot.set(title='Sinusoidal Output', xlabel='t', ylabel='f(t)')
fctPlot.legend()

dftPlot.stem(np.arange(0, 60), np.abs(n60DFTresults), 'b', label='n = 60', markerfmt=' ', basefmt='-b')
dftPlot.stem(np.arange(0, 30), np.abs(n30DFTresults), 'r', label='n = 30', markerfmt=' ', basefmt='-b')
dftPlot.set(title='DFT Output', xlabel='w', ylabel='|y~|')
dftPlot.legend()

plt.tight_layout()

# %%

# ----------------------
# Question 1b
# ----------------------

xVals60n_arange = np.arange(0, 2*np.pi, (2*np.pi)/60)

yVals60n_arange, n60DFTresults_arange = myDFT(configurableSinusoidal, xVals60n_arange)

plt.stem(np.arange(0, 60), np.abs(n60DFTresults), 'b', label='linspace', markerfmt=' ', basefmt='-b')
plt.stem(np.arange(0, 60), np.abs(n60DFTresults_arange), 'r', label='arange', markerfmt=' ', basefmt='-r')
plt.title('DFT Comparison between using linspace and arange for n=60 points')
plt.legend()
plt.plot()

'''
Interestingly, we see that by using arange, we get much better isolation of the actual frequencies
present in the sinusoidal. I have to think a bit more about why this would make a difference
'''

# %%

# ----------------------
# Question 1c
# ----------------------

def myIDFT(freqs):
    numVals = len(freqs)

    if numVals % 2 != 0:
        raise ValueError("Size of array passed to the IDFT function must be even")

    jVals = np.arange(0, numVals)
    kVals = jVals.reshape(((numVals, 1)))
    return np.dot(np.exp(2j*np.pi*kVals*jVals/numVals), freqs)/numVals

n60IDFTresults = myIDFT(n60DFTresults_arange)

plt.plot(xVals60n_arange, yVals60n_arange, label='Actual Function')
plt.plot(xVals60n_arange, n60IDFTresults.real, linestyle='dashed', label='IDFT Function')
plt.legend()
plt.title('Pure data / IDFT comparison')
plt.show()

# %%

# ----------------------
# Question 2
# ----------------------

def gaussianPulse(t, sigma=0.5, w=0):
    return np.exp(-(t**2)/sigma**2)*np.cos(w*t)

Q2xVals = np.arange(-np.pi, np.pi, (2*np.pi)/60)

Q2yVals, Q2DFTresults = myDFT(gaussianPulse, Q2xVals)

unshiftedVals = np.abs(Q2DFTresults)

print(len(unshiftedVals))

# Mirroring the unshifted data over its own half point. This implementation only works when 60 points are
# used, however the same method can be used for any size of dataset so long as it has an even number of points
shiftedVals = np.concatenate((unshiftedVals[30:], unshiftedVals[:30]))

fig, (xySpace, freqSpace) = plt.subplots(1, 2)

xySpace.plot(Q2xVals, Q2yVals, label='y(t)')
xySpace.set(xlabel='t', ylabel='y(t)', title='XY-Space Gaussian Pulse')
xySpace.legend()

freqSpace.plot(np.arange(0, 60), unshiftedVals, label='no shift')
freqSpace.plot(np.arange(-30, 30), shiftedVals, linestyle='dashed', label='with shift')
freqSpace.set(xlabel='w', ylabel='|y~|', title='Frequency Space Gaussian Pulse')
freqSpace.legend()


plt.tight_layout()

# %%

# ----------------------
# Question 3
# ----------------------


# This is the only way I could think of doing this without restructuring how I wrote the code above.
# It might be a bit overkill but it allows me to have a properly configurable sinusoidal function, which 
# I think was the aim of the definition given to us. This also keeps my DFT function able to take input from
# any arbitrary function which is a nice touch, and also I think desired by the project outline. 
Q3aVals = [3, 1, 0]
Q3wVals = [1, 10, 0]

Q3fct = lambda t: configurableSinusoidal(t, Q3aVals, Q3wVals)

Q3xVals = np.arange(0, 8*np.pi, (8*np.pi)/200)

Q3yVals_unfiltered, Q3DFTresults_unfiltered = myDFT(Q3fct, Q3xVals)

Q3DFTresults_filtered = np.zeros_like(Q3DFTresults_unfiltered)
Q3DFTresults_filtered[:30] = Q3DFTresults_unfiltered[:30]

Q3yVals_filtered = myIDFT(Q3DFTresults_filtered)


fig, (xyPlot, freqPlot) = plt.subplots(1, 2)

xyPlot.plot(Q3xVals, Q3yVals_unfiltered, color='r', linestyle='dashed', label='Unfiltered')
# We need to multiply the filtered results by two because we're losing the magnitude of the 
# second, mirrored, frequency spike. This frequency is still relevant to the the IDFT, and only
# appears to not be relevant because the displayed data hasn't been shifted yet
xyPlot.plot(Q3xVals, 2*Q3yVals_filtered, color='b', label='Filtered')
xyPlot.legend()
xyPlot.set(xlabel='t', ylabel='y(t)', title='XY-space the specified function')


freqPlot.plot(np.abs(Q3DFTresults_unfiltered), color='r', linestyle='dashed', label='Unfiltered')
freqPlot.plot(np.abs(Q3DFTresults_filtered), color='b', label='Filtered')
freqPlot.set(xlabel='w', ylabel='|y~|', title='Frequency space for the specified function')
freqPlot.legend()

plt.tight_layout()