#! /usr/bin/python3

import numpy as np
import matplotlib.pyplot as plt

# given two random number in (0, 1)
# generate the third random number in (0, 2)

a = np.random.rand(10000)
b = np.random.rand(10000)
# wrong method
c1 = a + b
# right method
c2 = np.where(a > 0.5, b, b + 1.0)

data_list = [a, b, c1, c2]
fig, axes = plt.subplots(2, 2)
for idx, ax in enumerate(axes.flatten()):
    ax.hist(data_list[idx], bins=100)
plt.show()
