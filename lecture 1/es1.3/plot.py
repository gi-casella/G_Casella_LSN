import matplotlib
import matplotlib.pyplot as plt
import numpy as np

ex1, ex2 ,ex10, ex100 , lor1, lor2 ,lor10, lor100, n1, n2 ,n10, n100  = np.loadtxt("output1", usecols=(0,1,2,3,4,5,6,7,8,9,10,11), delimiter=' ',  unpack='true')

fig, e= plt.subplots(1,  4, sharey=True, tight_layout=True)

e[0].hist(ex1, bins = 100, density = True)
e[1].hist(ex2, bins = 100, density = True)
e[2].hist(ex10, bins = 100, density = True)
e[3].hist(ex100, bins = 100, density = True)

fig, l= plt.subplots(1,  4, sharey=True, tight_layout=True)

l[0].hist(lor1, bins = 1000, range = (-100, +100), density = True)
l[1].hist(lor2, bins = 1000, range = (-100, +100), density = True)
l[2].hist(lor10, bins = 1000, range = (-100, +100), density = True)
l[3].hist(lor100, bins = 1000, range = (-100, +100), density = True)

fig, n= plt.subplots(1,  4, sharey=True, tight_layout=True)

n[0].hist(n1, bins = 100, density = True)
n[1].hist(n2, bins = 100, density = True)
n[2].hist(n10, bins = 100, density = True)
n[3].hist(n100, bins = 100, density = True)


plt.show()

