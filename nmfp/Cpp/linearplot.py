from pylab import *
from scipy.optimize import curve_fit
import numpy as np
import matplotlib.pyplot as plt
import math

# fake data
x = arange(0, 50)
y = x + 5*np.random.normal(size=len(x))

# fit
f = lambda x, *p: polyval(p, x)
p, cov = curve_fit(f, x, y, [1, 1])

# simulated draws from the probability density function of the regression
xi = linspace(np.min(x), np.max(x), 100)
ps = np.random.multivariate_normal(p, cov, 10000)
ysample = np.asarray([f(xi, *pi) for pi in ps])
lower = percentile(ysample, 16.0, axis=0)
upper = percentile(ysample, 84.0, axis=0)

# regression estimate line
y_fit = poly1d(p)(xi)

# plot
fig = plt.figure()
ax1 = fig.add_subplot(111)

ax1.scatter(x, y, c='b')
ax1.plot(xi, y_fit, 'r-')
ax1.plot(xi, lower, 'b--')
ax1.plot(xi, upper, 'b--')

plt.show()

