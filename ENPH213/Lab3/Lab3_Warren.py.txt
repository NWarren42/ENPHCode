# %%
import numpy as np
import math as m


# %%
# ----------------------
# Question 1a
# ----------------------

def getnxnMatrix(n):
    startVal = 21

    mat = np.arange(startVal, startVal + n*n)
    mat = mat.reshape((n,n))

    return mat

# %% part (i) -- Upper/Lower Matrices

def getLowerMatrix(mat):
    clonedMat = np.copy(mat)
    for i in range(len(mat)):
        clonedMat[i, i+1:] = 0
    
    return clonedMat

def getUpperMatrix(mat):
    clonedMat = np.copy(mat)
    for i in range(len(mat)):
        clonedMat[i, :i] = 0
    
    return clonedMat

matSize = int(4)

nxnMatrix = getnxnMatrix(matSize)
lowerMatrix = getLowerMatrix(nxnMatrix)
upperMatrix = getUpperMatrix(nxnMatrix)

# %% part (ii) -- Euclidean/Frobenius Norm

def getEuclideanNorm(mat):
    return np.sqrt(np.sum(mat**2))

euclideanNorm = getEuclideanNorm(nxnMatrix)
print(f"The Euclidean Norm of the matrix is: {euclideanNorm:.4f}")

# %% part (iii) -- Infinity Norm
def getInfinityNorm(mat):
    return np.max(np.sum(mat, axis=1))

infinityNorm = getInfinityNorm(nxnMatrix)
print(f"The Infinity Norm of the matrix is: {infinityNorm}")

# %%
# ----------------------
# Question 1b
# ----------------------

# %% part (i)
Q1B_matSize = 4

def makeQ1B_AMat(n):
    mat = np.triu(np.ones((n,n))*-1)
    np.fill_diagonal(mat, 1)
    return mat

# %% part (ii)

def makeQ1B_BMat(n):
    mat = np.ones(n)
    mat[1::2] = -1
    return mat

def Q2solveMatrices(n):
    AMat = makeQ1B_AMat(n)
    BMat = makeQ1B_BMat(n)

    perturbedA = np.copy(AMat)
    perturbedA[n-1, 0] -= 0.001

    ASoltns = np.linalg.solve(AMat, BMat)
    perturbedASoltns = np.linalg.solve(perturbedA, BMat)

    return ASoltns, perturbedASoltns

soltns, perturbedSoltns = Q2solveMatrices(Q1B_matSize)

print(f"Normal A solutions are x1: {soltns[0]}, x2: {soltns[1]}, x3: {soltns[2]}")
print(f"Normal A solutions are x1: {perturbedSoltns[0]}, x2: {perturbedSoltns[1]}, x3: {perturbedSoltns[2]}")


# %% part (iii)

Q1C_matSize = 16

soltns, perturbedSoltns = Q2solveMatrices(Q1C_matSize)

print(f"Normal A solutions are x1: {soltns[0]}, x2: {soltns[1]}, x3: {soltns[2]}")
print(f"Normal A solutions are x1: {perturbedSoltns[0]}, x2: {perturbedSoltns[1]}, x3: {perturbedSoltns[2]}")

# %%

# %%
# ----------------------
# Question 2a
# ----------------------

from timeit import default_timer

def backsubBad (U, bVals): # Given bad, silly, slow (but very readable) backsub function
    n = bVals.size
    xVals = np.zeros(n)

    xVals[n-1] = bVals[n-1]/U[n-1, n-1] # Setting first x value from bottom row of upper matrix
    for i in range(n-2, -1, -1):
        leftSideSum = 0
        for j in range(i+1, n):
            leftSideSum += U[i, j] * xVals[j]
        xVals[i] = (bVals[i] - leftSideSum) / U[i, i]
    return xVals

def backsubGood (U, bVals): # Assumes U is already an upper matrix
    n = bVals.size
    xVals = np.zeros(n)

    # Back substitution logic -- dot product is used to assemble the terms to be subtracted from the b values
    for i in range(n-1, -1, -1):
        xVals[i] = (bVals[i] - np.dot(xVals[i+1:], U[i, i+1:])) / U[i, i]

    return xVals

# Getting upper matrix of the nxn matrix created
Q2A_aMat = np.triu(getnxnMatrix(5000))
Q2A_bMat = Q2A_aMat[0]

timeStart = default_timer()
bsbResults = backsubBad(Q2A_aMat, Q2A_bMat)
timeEnd = default_timer()
print(f"Bad Backsub Results: x1 = {bsbResults[0]}, x2 = {bsbResults[1]}, x3 = {bsbResults[2]}")
print(f"Bad Backsub Time: {timeEnd-timeStart:.2f}")

timeStart = default_timer()
bsgResults = backsubGood(Q2A_aMat, Q2A_bMat)
timeEnd = default_timer()
print(f"\nGood Backsub Results: x1 = {bsgResults[0]}, x2 = {bsgResults[1]}, x3 = {bsgResults[2]}")
print(f"Good Backsub Time: {timeEnd-timeStart:.2f}")


# %%

# ----------------------
# Question 2b
# ----------------------

def gaussianElimination (aMat, bMat):

    newA = np.copy(aMat)
    newB = np.copy(bMat)

    for i in range(0, len(bMat)-1):
        # Gaussian elimination logic to zero out all elements below the current index in the current column 
        for j in range(i+1, len(bMat)):
            coeff = newA[j, i]/newA[i, i]
            newA[j, i:] -= coeff * newA[i, i:]
            newB[j] -= coeff * newB[i]

    return newA, newB


Q2B_aMat = np.array(
            [[2., 1.,  1.],
             [1., 1., -2.],
             [1., 2.,  1.]])

Q2B_bMat = np.array(
            [ 8.,
             -2.,
              2.])

gaussElimResults = gaussianElimination(Q2B_aMat, Q2B_bMat)

backsubResults = backsubGood(*gaussElimResults)

print(f"X values for the given matrix are {backsubResults}")
# %%

def gaussianEliminationPartial (aMat, bMat):

    newA = np.copy(aMat)
    newB = np.copy(bMat)
    swap = None

    for i in range(0, len(bMat)-1):
        maxIndex = np.argmax(np.abs(newA[i:, i])) + i

        # Swapping array rows if the max at the current column is in a different row
        if(maxIndex != i):
            newA[[i, maxIndex], :] = newA[[maxIndex, i], :]
            newB[i], newB[maxIndex] = newB[maxIndex], newB[i]
        
        # Gaussian elimination logic to zero out all elements below the current index in the current column 
        for j in range(i+1, len(bMat)):
            if(newA[j, i]): pass
            coeff = newA[j, i]/newA[i, i]
            newA[j, i:] -= coeff * newA[i, i:]
            newB[j] -= coeff * newB[i]

    return newA, newB

Q2C_aMat = np.array(
            [[2., 1.,  1.],
             [2., 1., -4.],
             [1., 2.,  1.]])

Q2C_bMat = np.array(
            [ 8.,
             -2.,
              2.])

gaussElimResults = gaussianEliminationPartial(Q2C_aMat, Q2C_bMat)
backsubResults = backsubGood(*gaussElimResults)

print(f"X values for the given matrix are {backsubResults}")

# %%
