# %%
import numpy as np
import matplotlib.pyplot as plt
from scipy.linalg import solve

# %%

# ----------------------
# Question 1
# ----------------------

def rungeFct(x): return 1/(1+25*x**2) 

def generateRungePoints(numPoints, spacingType, fct=rungeFct, xRange=(-1, 1)):
    if spacingType == 'equal':
        xVals = np.linspace(*xRange, numPoints)
    elif spacingType == 'cheb':
        xVals = []
        for i in range(numPoints):
            xVals.append(-np.cos((i*np.pi)/(numPoints-1)))
        xVals = np.array(xVals)
    
    return xVals, fct(xVals)

def monomialInterpolation(xVals, yVals, xRange=(-1, 1), numEvalPoints=100):
    # First step is to create the coefficient matrix
    numVals = len(xVals)
    coeffMat = np.ones([numVals, numVals])

    for i in range(numVals):
        for j in range(numVals):
            coeffMat[i, j] = xVals[i]**j

    # Now we solve the coefficient matrix to use when applying the interpolation formula    
    solvedCoeffs = solve(coeffMat, yVals)

    # Setting up values to interpolate at
    interpXs = np.linspace(*xRange, numEvalPoints)    
    interpYs = []
    
    for i in range(numEvalPoints): # Getting a corresponding y value for each x interpolation value
        tempSum = 0
        for j in range(numVals): # Summing the point multiplied by each of the solved coefficients raised to the desired power
            tempSum += solvedCoeffs[j]*(interpXs[i]**j)
        interpYs.append(tempSum)

    return interpXs, np.array(interpYs)

def lagrangianInterpolation(xVals, yVals, xRange=(-1,1), numEvalPoints=100):
    numVals = len(xVals)

    # Setting up output values
    interpXs = np.linspace(*xRange, numEvalPoints)
    interpYs = []

    for x in interpXs: # Running the lagrangian interpolation for each point
        tempY = 0
        for i in range(numVals):
            tempVal = yVals[i]
            for j in range(numVals):
                if i != j:
                    tempVal *= (x - xVals[j])/(xVals[i] - xVals[j]) # General lagrangian interpolation formula
            tempY += tempVal
        interpYs.append(tempY) # Saving the corresponding y value for the x value just calculated
    
    return interpXs, np.array(interpYs)


chebXs, chebYs = generateRungePoints(15, 'cheb')
equalXs, equalYs = generateRungePoints(15, 'equal')

monoSolvedChebXs, monoSolvedChebYs = monomialInterpolation(chebXs, chebYs)
monoSolvedEqualXs, monoSolvedEqualYs = monomialInterpolation(equalXs, equalYs)

lagSolvedChebXs, lagSolvedChebYs = lagrangianInterpolation(chebXs, chebYs)
lagSolvedEqualXs, lagSolvedEqualYs = lagrangianInterpolation(equalXs, equalYs)

fig, (chebPlot, equalPlot) = plt.subplots(1, 2)

chebPlot.plot(chebXs, chebYs, '.', label='Points', color='black')
chebPlot.plot(monoSolvedChebXs, monoSolvedChebYs, label='Mono', color='red')
chebPlot.plot(lagSolvedChebXs, lagSolvedChebYs, label='Lag', linestyle='dotted', color='blue')
chebPlot.set(title='Chebyshev Points', xlabel='x', ylabel='f(x)')

equalPlot.plot(equalXs, equalYs, '.', label='Points', color='black')
equalPlot.plot(monoSolvedEqualXs, monoSolvedEqualYs, label='Mono', color='red')
equalPlot.plot(lagSolvedEqualXs, lagSolvedEqualYs, label='Lag', linestyle='dotted', color='blue')
equalPlot.set(title='Equal Points', xlabel='x')

chebPlot.legend()
equalPlot.legend()

plt.tight_layout()

# %%

# ----------------------
# Question 2
# ----------------------

def cSplineInterpolation(xVals, yVals, numEvalPoints=500):
    
    numVals = len(xVals)

    # To solve the cubic spline equation, two matrices must be set up then solved to be able
    # to determine the relevant coefficients to the system. Both matrices have specific mathematical
    # that are implemented below.

    # A matrix setup
    aMatrix = np.zeros((numVals-2, numVals-2))

    # Filling the symmetric tri-diagonal matrix
    np.fill_diagonal(aMatrix, 2*(xVals[2:] - xVals[:-2]))
    np.fill_diagonal(aMatrix[1:,:], xVals[2:-1] - xVals[1:-2])
    np.fill_diagonal(aMatrix[:,1:], xVals[2:-1] - xVals[1:-2])

    # Setting up B matrix
    bMatrix = 6*(((yVals[2:]-yVals[1:-1])/(xVals[2:]-xVals[1:-1])) 
                          - ((yVals[1:-1]-yVals[:-2])/(xVals[1:-1]-xVals[:-2])))
    
    # Now solve for the coefficient matrix from A and B
    solvedCoeffs = np.zeros(numVals)
    solvedCoeffs[1:-1] = solve(aMatrix, bMatrix)

    # With the coefficients, solve for the y values between each pair of x values
    interpXs = np.linspace(xVals[0], xVals[-1], numEvalPoints)
    interpYs = []
    
    # Setting up left and right indices for used on determining which interval a supplied x value sits in
    lI = 0
    rI = 1

    for i in range(numEvalPoints):
        # Need to know which interval the x value thats being evaluated sits within. The code below assumed
        # we are using a sorted array and searching left to right (which we know we are since we are setting
        # the search values with np.linspace)
        if interpXs[i] > xVals[rI]: 
            lI += 1
            rI += 1
        
        interpYs.append(  (yVals[lI]*(xVals[rI]-interpXs[i])/(xVals[rI]-xVals[lI]))
                        + (yVals[rI]*(interpXs[i]-xVals[lI])/(xVals[rI]-xVals[lI]))
                        - (solvedCoeffs[lI]/6)*((xVals[rI]-interpXs[i])*(xVals[rI]-xVals[lI])-(((xVals[rI]-interpXs[i])**3)/(xVals[rI]-xVals[lI])))
                        - (solvedCoeffs[rI]/6)*((interpXs[i]-xVals[lI])*(xVals[rI]-xVals[lI])-(((interpXs[i]-xVals[lI])**3)/(xVals[rI]-xVals[lI]))))

    return interpXs, np.array(interpYs)


datax = np.array([2.5,2.8,3.0,3.3,3.7,4.1,4.3,4.7,
                  5.,5.2,5.6,6.1,6.5,6.7,7.1,7.2,7.5])

datay = np.array([1.084e-17 , 6.7041e-11 , 1.125e-07 , 2.359e-04 ,
                  5.749e-02, 5.188e-01 , 7.865e-01 , 9.919e-01 ,
                  1.000e+00, 9.984e-01 , 8.784e-01 , 2.312e-01 ,
                  6.329e-03, 2.359e-04 , 3.579e-09 , 6.704e-11 , 1.084e-17])

Q2lagXs, Q2lagYs = lagrangianInterpolation(datax, datay, xRange=(2.5, 7.5), numEvalPoints=500)

Q2cSplineXs, Q2cSplineYs = cSplineInterpolation(datax, datay)

fig, (lagPlot, cSplinePlot) = plt.subplots(1, 2)

lagPlot.plot(datax, datay, '.', color='blue')
lagPlot.plot(Q2lagXs, Q2lagYs, color='red')
lagPlot.set(title='Lagrangian Interpolation', xlabel='x', ylabel='f(x)')

cSplinePlot.plot(datax, datay, '.', color='blue')
cSplinePlot.plot(Q2cSplineXs, Q2cSplineYs, color='red')
cSplinePlot.set(title='Cubic Spline Interpolation', xlabel='x')


plt.show()

# %%

# ----------------------
# Question 3
# ----------------------

def Q3fct(x):
    return np.exp(np.sin(2*x))

def trigInterpolation(xVals, yVals, numOutputPoints=500):
    
    numVals = len(xVals)
    mVal = numVals//2

    aCoeffs = np.zeros(mVal + 1)
    bCoeffs = np.zeros(mVal - 1)
    
    for k in range(0, mVal+1):
        aCoeffs[k] = (1/mVal)*np.dot(yVals, np.cos(k*xVals))

    for k in range(1, mVal):
        bCoeffs[k - 1] = (1/mVal)*np.dot(yVals, np.sin(k*xVals))

    interpXs = np.linspace(0, 2*np.pi, numOutputPoints)
    interpYs = (1/2)*(aCoeffs[0] +  aCoeffs[-1]*np.cos(mVal*interpXs))
    
    for i in range(numOutputPoints):
        for k in range(1, mVal):
            interpYs[i] += aCoeffs[k]*np.cos(k*interpXs[i]) + bCoeffs[k - 1]*np.sin(k*interpXs[i])

    return interpXs, interpYs

# Actual Function Points
Q3XVals = np.linspace(0, 2*np.pi, 100)
Q3YVals = Q3fct(Q3XVals)

# Known Points
Q311xVals = np.linspace(0, 2*np.pi, 11)
Q311yVals = Q3fct(Q311xVals)
Q351xVals = np.linspace(0, 2*np.pi, 51)
Q351yVals = Q3fct(Q351xVals)

# Interpolated Values
Q3interp11XVals, Q3interp11YVals = trigInterpolation(Q311xVals, Q311yVals)
Q3interp51XVals, Q3interp51YVals = trigInterpolation(Q351xVals, Q351yVals)

# Plots
fig, (plot11n, plot51n) = plt.subplots(1, 2)

plot11n.plot(Q3XVals, Q3YVals, linestyle='dashed', label='f(x)')
plot11n.plot(Q311xVals, Q311yVals, '.', label='Points')
plot11n.plot(Q3interp11XVals, Q3interp11YVals, label = 'Interpolation')
plot11n.set(title='Trig Approx -- n=11', xlabel='x', ylabel='y')
plot11n.legend(loc='lower left')

plot51n.plot(Q3XVals, Q3YVals, linestyle='dashed', label='f(x)')
plot51n.plot(Q351xVals, Q351yVals, '.', label='Points')
plot51n.plot(Q3interp51XVals, Q3interp51YVals, label = 'Interpolation')
plot51n.set(title='Trig Approx -- n=51', xlabel='x', ylabel='y')
plot51n.legend(loc='lower left')

plt.tight_layout()


# %% 

# ----------------------
# Bonus Q
# ----------------------

print("The exact function is e^(-((x-5)^2)^2)")
# %%
