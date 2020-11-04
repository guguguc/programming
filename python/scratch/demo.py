import os
import functools

def func():
    msg = 'hello, world'
    return msg

class Foo:
    def __init__(self, arg1, arg2, *args, **kw):
        self.arg1 = arg1
        self.arg2 = arg2
        self.args = args
        self.kw = kw

    def print(self):
        msg = 'dsajl'
        return msg

if __name__ == '__main__':
    func()
