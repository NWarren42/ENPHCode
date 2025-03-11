import numpy as np
import plotly.graph_objects as go

def getCns(b, A, n):
    
    if (n % 2 == 1):
        val = 1 + np.exp(-b*A)
    else: 
        val = 1 - np.exp(-b*A)
    
    return (b*A*val)/(b**2 * A**2 + np.pi**2 * n**2)

def fterm(b, A, n, x):
    if (n == 0):
        return getCns(b, A, 0)
    return 2*getCns(b, A, n)*np.cos(n*np.pi*x/A)

def getFourierSeries(b, A, x, N):
    sum = 0
    for n in range(N+1):
        sum += fterm(b, A, n, x)
    return sum

def baseFunction(b, x):
    return np.exp(-b*np.abs(x))

xVals = np.linspace(-4, 4, 1001)
b = 0.5
A = 3

fVals = baseFunction(b, xVals)
fFourierVals_n0 = getFourierSeries(b, A, xVals, 1)
fFourierVals_n5 = getFourierSeries(b, A, xVals, 5)
fFourierVals_n20 = getFourierSeries(b, A, xVals, 20)

fig = go.Figure()
fig.add_trace(go.Scatter(x=xVals, y=fFourierVals_n0, mode='lines', name='N=1'))
fig.add_trace(go.Scatter(x=xVals, y=fFourierVals_n5, mode='lines', name='N=5'))
fig.add_trace(go.Scatter(x=xVals, y=fFourierVals_n20, mode='lines', name='N=20'))
fig.add_trace(go.Scatter(x=xVals, y=fVals, mode='lines', name='f(x)', line=dict(color='black', width=2)))

fig.update_layout(
    title="$Fourier\ Series\ Approximation\ of\ f(x)=e^{-b|x|}$",
    xaxis_title="$x$",
    yaxis_title="$f(x)$",
    xaxis = dict(
        range=[-4, 4]
    ),
    yaxis = dict(
        range=[0, 1.2]
    )
)

# save this image as a png file
fig.write_image("FourierSeriesApprox.png")