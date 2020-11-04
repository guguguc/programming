#!/usr/bin/python3
import numpy as np
import time

N = 10000000
K = N - 200000
A = list(np.random.randint(low=0,
                           high=0x7fffffff,
                           size=(N)))
def timer(f):
    def wraper(*args):
        t1 = time.perf_counter()
        ans = f(*args)
        t2 = time.perf_counter()
        print(f'func {f.__name__} cost {(t2-t1)*1000} ms')
        return ans
    return wraper

@timer
def topk_vanilla(sequence, k):
    x = sorted(sequence)
    return x[k-1]

def partition(sequence, left, right):
    if right == left:
        return left
    s = left
    privot = sequence[s]
    i, j = left, right
    while i < j:
        while(j > i and sequence[j] > privot):
            j -= 1
        if i >= j:
            break
        sequence[i] = sequence[j]
        while(j > i and sequence[i] < privot):
            i += 1
        sequence[j] = sequence[i]
    sequence[j] = privot
    return j

# @timer
def topk_quick(sequence, k, n):
    # print(f'before partition {sequence}')
    i = partition(sequence, 0, n - 1)
    # print(f'after partition {sequence}')
    if i+1 > k:
        print(f'length is {i}')
        return topk_quick(sequence[:i], k, i)
    elif i+1 < k:
        print(f'length is {n-i-1}')
        return topk_quick(sequence[i+1:], k-i-1, n-i-1)
    else:
        print(f'find the answer is {sequence[i]}')
        exit()
        return sequence[i]
# ans1 = topk_vanilla(A, K)
# print(ans1)
ans2 = topk_quick(A, K, N)
print(ans2)
