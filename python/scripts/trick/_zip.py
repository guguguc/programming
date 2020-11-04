'''
@Author: grehex
@Date: 2020-03-28 16:26:06
@LastEditTime: 2020-03-28 16:26:06
@Description: 
'''

def myzip(*iterables):
    sentinel = object()
    itertors = [iter(it) for it in iterables]
    print(itertors)
    while itertors:
        result = []
        for it in itertors:
            elem = next(it, sentinel)
            if elem is sentinel:
                return
            result.append(elem)
        yield tuple(result)
