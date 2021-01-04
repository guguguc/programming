# 协程
>Coroutines are computer program components that generalize subroutines for non-preemptive multitasking, by allowing execution to be suspended and resumed.
 Coroutines are well-suited for implementing familiar program components such as cooperative tasks, exceptions, event loops, iterators, infinite lists and pipes.

简言之，协程延长了函数的生命期（通过保存寄存器与堆栈状态来恢复之前的执行位置与变量状态）。
协程能够在语言层级（不需要操作系统支持）来实现同步。(不需要锁啊，信号量等)

## 实现
### 0x00 Python
通过async/await语法实现。
在python中有三类object是awaitable的。
* coroutines
    - coroutine function: 使用async def定义的函数
    - coroutine object:   协程函数返回的object
* Tasks
* Futures
```python
    import asyncio
    # coroutine function
    async def func()：
        await asyncio.sleep(1)
        # coroutine object
        return 1
    async def main():
        ret = await func()
        # task
        task = asyncio.create_task(func())
        await task
    asyncio.run(main())
```
## 0x01 C++
## 0x02 Go

## 代码片段