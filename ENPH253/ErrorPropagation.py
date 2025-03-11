# %%
import numpy as np
import sympy as sm

# %%
def solveExpressionWithError(stringExpression, varValError):
    '''
    This function evaluates an expression and gives the error, and fractional contribution to the 
    total error by each variable. The function takes an input expression in the form of a string, 
    and a list of as many 3 element tuples as there are variables in the expression of the form
    ('differentiationVariable', evaluationValue, errorOnValue) 
    
    As of right now, only the first specified variable can be passed through as an list/numpy array

    '''

    
    # Converting the given expression in the form of a string to a sympy expression
    symbolicExpression = sm.sympify(stringExpression)

    # First step is to evaluate the function at the given values
    singleInputAnswers = []
    multiInputAnswers = []

    listArrayCheck = False   
    if(isinstance(varValError[0][1], (int, float))):
        singleInputAnswers.append(symbolicExpression.subs([(sm.symbols(var), val) for var, val, _ in varValError]))
    elif(isinstance(varValError[0][1], (list, np.ndarray))):
        listArrayCheck = True
        tempAnswers = []
        for listVal in varValError[0][1]:
            for j, (var, val, _) in enumerate(varValError[0][1]):
                if j == 0:
                    tempAnswers.append(symbolicExpression.subs((sm.symbols(var), listVal)))
                else:
                    tempAnswers.append(symbolicExpression.subs((sm.symbols(var), val)))
        multiInputAnswers.append(tempAnswers)
    else: raise TypeError(f"Unsupported type for {varValError[0][1]}: {type(varValError[0][1])}. Expected int or float.")
    
    if len(multiInputAnswers) > 0:
        ans = np.array(multiInputAnswers)+ sum(singleInputAnswers) 
    else:     
        ans = sum(singleInputAnswers)

    totalError = 0
    individualErrors = {}
    
    for var, _, error in varValError:
        symPartialDerivative = sm.diff(symbolicExpression, sm.symbols(var))

        if(listArrayCheck):
            evaluatedPartial = symPartialDerivative.subs([(sm.symbols(var), val[0] if isinstance(val, (list, np.ndarray)) else val) for var, val, _ in varValError])           
        else:    
            evaluatedPartial = symPartialDerivative.subs([(sm.symbols(var), val) for var, val, _ in varValError])
        
        individualErrors[var] = (evaluatedPartial * error)**2
        totalError += individualErrors[var]

    # Both the individual and total error have already been squared so this is the easiest spot
    # to calculate the fractional contribution of each variable to the error
    fractionalContribution = {var: indError/totalError for var, indError in individualErrors.items()}

    # The last step to solving the equation for the actual error is to take the root of the error from this point
    totalError **= (1/2)

    return ans, totalError, fractionalContribution

