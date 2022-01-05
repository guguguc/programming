#!/bin/python3
import asyncio
import time


async def read():
    return 10


async def main():
    print(f"start: {time.strftime('%X')}")
    await read()
    print(f"end: {time.strftime('%X')}")

if __name__ == '__main__':
    asyncio.run(main(), debug=True)
