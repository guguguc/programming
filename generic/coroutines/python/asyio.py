import random

class Queue:
    def __init__(self, max_size=100):
        self._queue = [None] * max_size
        self._front = 0
        self.size = 0
        self.max_size = max_size
    
    def put(self, data):
        if self.full():
            raise Exception('Queue is full.')
        pos = (self._front + self.size) % self.max_size
        self._queue[pos] = data
        self.size += 1
        print(f'put data {data} to queue {self._queue}, after size {self.size}')
    
    def get(self):
        if self.empty():
            raise Exception('Queue is empty.')
        data = self._queue[self._front]
        self._front = (self._front + 1) % self.max_size
        self.size -= 1
        print(f'get data {data} in queue {self._queue}, after size {self.size}')
        return data

    def empty(self):
        return self.size == 0
    
    def full(self):
        return self.size == self.max_size


MAX_SIZE = 5
q = Queue(max_size=MAX_SIZE)
