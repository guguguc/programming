#include <assert.h>

#define YES 1
#define NOPE 0

int table = YES;
int locked = 0;

int xchg(volatile int *addr, int newval) {
  int result;
  asm volatile("lock xchg %0, %1" : "+m"(*addr), "=a"(result) : "1"(newval));
  return result;
}

void lock() {
  int got;
retry:
  got = xchg(&table, NOPE);
  if (got == NOPE) {
    goto retry;
  }
  assert(got == YES);
}

void unlock() { xchg(&table, YES); }

void spinlock() {
  while (xchg(&locked, 1))
    ;
}

void spinunlock() { xchg(&locked, 0); }
