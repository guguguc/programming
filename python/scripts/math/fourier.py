import numpy as np
import matplotlib.pyplot as plt
from scipy.integrate import quad

N = 20
PI = 3.14159274
F = lambda x: np.exp(x)

def timer(func):
    from time import time
    from functools import wraps
    @wraps(func)
    def wrap(*args):
        t1 = time()
        ans = func(*args)
        t2 = time()
        print(f'{func.__name__} cost {(t2-t1)*1000:2} ms')
        return ans
    return wrap

@timer
def fourier_series(x):
    def calc(n, x):
        an, ea = quad(lambda x: F(x)*np.cos(n*x), -PI, PI)
        bn, eb = quad(lambda x: F(x)*np.sin(n*x), -PI, PI)
        ans = an*np.cos(n*x) + bn*np.sin(n*x)
        return ans

    ans = np.sum([calc(n, x) for n in range(1, N)])
    ans += (quad(F, -PI, PI)[0])/2
    ans /= PI
    return ans

x = np.linspace(-PI, PI, N)
f = np.vectorize(fourier_series)
y = f(x)


plt.plot(x, y, marker='o')
plt.plot(x, np.vectorize(F)(x))

plt.show()
