import numpy as np
from matplotlib import pyplot as plt

N = 10000

def draw_border():
    theta = np.linspace(0, np.pi/2, N)
    r = np.array([np.cos(p) if p < np.pi/4 else np.sin(p) for p in theta])
    r = 1 / r
    r_border = np.linspace(0, 1, N)
    theta_border_left = np.zeros_like(r_border)
    theta_border_right = np.ones_like(r_border) * np.pi / 2

    theta = np.concatenate([theta_border_left, theta, theta_border_right])
    r = np.concatenate([r_border, r, r_border])
    plt.plot(theta, r)

    p0 = (np.pi/4, 2**(0.5)/2)
    p1 = (0, 1)
    p2 = (np.pi/4, 2**(0.5))
    p3 = (np.pi/2, 1)
    points = [p0, p1, p2, p3]
    noise = np.random.normal(scale=1e-2, size=(100, 2))
    for i in points:
        p = noise + [i]
        plt.plot(p[:, 0], p[:, 1])

def simulate():
    p1 = np.random.uniform(0, 1, size=(N, 2))
    p2 = np.zeros_like(p1)
    r = np.sqrt(np.square(p1[:, 0]) + np.square(p1[:, 1]))
    theta = np.arcsin(p1[:, 1] / r)
    plt.scatter(theta, r)

if __name__ == '__main__':
    simulate()
    plt.show()
