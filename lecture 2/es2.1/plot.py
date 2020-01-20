import matplotlib
import matplotlib.pyplot as plt
import numpy as np

i, r2, cr2= np.loadtxt("output1", usecols=(0,1,3), delimiter=' ',  unpack='true')

plt.errorbar(i,r2)
plt.errorbar(i,cr2)

plt.show()
