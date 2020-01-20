import matplotlib
import matplotlib.pyplot as plt
import numpy as np

n, f, er= np.loadtxt("output1", usecols=(0, 1, 2), delimiter=' ', unpack='true')
plt.errorbar(n,f, yerr= er)
plt.xlabel('#throws')
plt.ylabel('means-1/12')
plt.grid( True )
plt.show()

