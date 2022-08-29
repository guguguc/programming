'https://stackoverflow.com/questions/18679264/how-to-use-malloc-and-free-with-python-ctypes'
'https://stackoverflow.com/questions/874245/python-ctypes-and-function-pointers'

import ctypes

def load_libc_win():
    libc = ctypes.cdll.msvcrt
    libc.printf(b"hello, world")

def f(x):
    return x

def load_external_dll(dll_name):
    dll = ctypes.cdll.LoadLibrary(dll_name)
    callback = ctypes.CFUNCTYPE(ctypes.c_double, ctypes.c_double)
    dll.diff.argtypes = [callback, ctypes.c_double, ctypes.c_double]
    dll.diff.restype = ctypes.c_double
    arg1 = callback(f)
    ans = dll.diff(arg1, 1, 0.0001)
    print(ans)

if __name__ == '__main__':
    load_external_dll("calc.dll")