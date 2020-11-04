import asyncio
import threading
import concurrent.futures
import random
import time


async def print_after(delay, msg):
    await asyncio.sleep(delay)
    # time.sleep(delay)
    print('thread id', threading.get_native_id(), 'message', msg)
    if msg == 0:
        raise TypeError('error')
    return msg

def blocking_io():
    print(f"started blocking at {time.strftime('%X')}")
    with open('/dev/urandom', 'rb') as f:
        return f.read(100)
    time.sleep(10)
    print(f"blocking_io complete at {time.strftime('%X')}")

    
async def main_1():
    # blocking
    print(f"started at {time.strftime('%X')}")
    # It won't run at all
    print_after(1, 'xx')
    await print_after(2, 'hello')
    await print_after(3, 'world')
    print(f"finised at {time.strftime('%X')}")


async def main_2():
    # non-blocking
    t1 = asyncio.create_task(print_after(2, 'hello'))
    t2 = asyncio.create_task(print_after(3, 'world'))
    print(f"started at {time.strftime('%X')}")
    await t1
    await t2
    print(f"finised at {time.strftime('%X')}")


async def main_3():
    # schedule concurrently
    res = await asyncio.gather(
        *[print_after(random.randint(0, 10), i) for i in range(10)],
        return_exceptions=True)
    print(res)

async def main_4():
    # run coroutines in multiple threads
    # new in python 3.9
    # await asyncio.gather(
    #     *[asyncio.to_thread(blocking_io) for _ in range(10)]
    # )
    loop = asyncio.get_running_loop()
    with concurrent.futures.ThreadPoolExecutor() as pool:
        for _ in range(10):
            res = await loop.run_in_executor(pool, blocking_io)
            print(res)


asyncio.run(main_4())