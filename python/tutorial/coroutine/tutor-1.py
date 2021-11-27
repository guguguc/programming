import os
"""
Consumer1 consume producer1, and send some information.
We can leverage this feature to implement notification based on event driven.
"""
"""demo0
"""


def producer1():
    for i in range(10):
        ret = (yield i)
        print("[resume]", ret)


def consumer1():
    obj = producer1()
    i = next(obj)
    print("[consume]", i)
    i = obj.send(200)
    print("[consume]", i)


"""demo1
"""


def gen_files(dirname: str):
    files = os.listdir(dirname)
    for file in files:
        ret = (yield file)
        print("[ret]", ret)


def read_files(dirname: str):
    gen = gen_files(dirname)
    ret = None
    files = []
    try:
        while True:
            file = gen.send(ret)
            files.append(file)
            data = yield do_read(file)
            ret = "ok"
            print(data)
    except StopIteration:
        print("end")


def do_read(filename: str):
    print('[process]', filename)
    return filename


def run():
    pipline = read_files('/home/gugugu/Pictures/screenshot')
    ret = None
    while True:
        try:
            it = pipline.send(ret)
        except StopIteration:
            print('exit')
            break
        else:
            print(it)
            ret = 'ook'


def main():
    # consumer1()
    run()


main()
