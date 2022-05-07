#include <pthread.h>
#include <stdio.h>

#define N 100000000

long sum = 0;

void Tsum(void) {
  for (int i = 0; i < N; ++i) {
    asm volatile("lock addq $1, %0": "+m"(sum));
  }
}

int main() {
  pthread_t t1, t2;
  pthread_create(&t1, NULL, &Tsum, NULL);
  pthread_create(&t2, NULL, &Tsum, NULL);
  pthread_join(t1, NULL);
  pthread_join(t2, NULL);
  printf("sum : %ld", sum);
}
