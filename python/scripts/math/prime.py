import math
import matplotlib.pyplot as plt

from concurrent.futures.thread import ThreadPoolExecutor
from multiprocessing import cpu_count

N = 1024
xs = [x for x in range(2, N + 1)]
ys = [0] * len(xs)
blk_sz = N // cpu_count()
blk_num = N // blk_sz
max_threads = cpu_count()


def is_prime(x):
    for i in range(2, math.ceil(math.sqrt(x)) + 1):
        if x % i == 0:
            return False
    print(x)
    return True


def prime_cnt(n):
    return len([i for i in range(1, n) if is_prime(i)])


def calc_func(st, blk_sz):
    ans = [prime_cnt(i) for i in range(st, st + blk_sz)]
    return (st // blk_sz, ans)


def main():
    with ThreadPoolExecutor(max_workers=blk_sz) as executor:
        func = lambda x: calc_func(x, blk_sz)
        sts = range(0, N, blk_sz)
        ans = executor.map(func, sts)
        dct = {item[0]: item[1] for item in ans}
        for blk_idx in range(blk_num):
            st = blk_idx * blk_sz
            ys[st:st + blk_sz] = dct[blk_idx]
    plt.plot(xs, ys, marker='o', color='red')
    plt.plot(xs, list(map(lambda x: x / math.log(x), xs)))
    plt.show()


main()
