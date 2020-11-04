import matplotlib.pyplot as plt
import numpy as np

fig, ax = plt.subplots(2, 1, figsize=(10, 6), tight_layout=True,
                       facecolor=(.18, .31, .31))
x = np.arange(10)
classes = ['plane', 'car', 'bird', 'cat', 'deer', 'dog', 'frog', 'horse', 'ship', 'truck']
cmap = plt.get_cmap('tab10')
for idx, c in enumerate(classes):
    ax[0].plot(x, idx * x)
    ax[1].plot(x, idx * x, color=cmap(idx), linestyle='dotted', label=c)
ax[1].set_title('color map', color='0.7')
ax[1].legend(loc='best', fancybox=True, ncol=5)
for axes in ax:
    axes.tick_params(labelcolor='tab:orange')
plt.tight_layout(pad=0.5)
plt.show()



