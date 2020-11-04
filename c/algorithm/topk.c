#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


void printArray(const int *array, size_t start, size_t end) {
  for (int i = start; i < end; ++i)
    printf("%d ", array[i]);
  printf("\n");
}

int *genRandom(int n, size_t low, size_t high) {
  srand(time(0));
  int *ret = (int *)malloc(n * sizeof(int));
  for (int i = 0; i < n; ++i) {
    ret[i] = rand() % (high - low) + low;
  }
  return ret;
}

int partition(int *array, size_t left, size_t right) {
  if (right == left)
    return left;
  int privot = array[left];
  int i = left, j = right;
//   printf("before partition\n");
//   printArray(array, left, right - left + 1);
  while (i < j) {
    while (i < j && array[j] > privot) {
      j--;
    }
    array[i] = array[j];
    if (i >= j)
      break;
    while (i < j && array[i] < privot) {
      i++;
    }
    array[j] = array[i];
  }
  array[j] = privot;
//   printf("j is %d, privot is %d\n", j, privot);
//   printf("after partition\n");
//   printArray(array, left, right - left + 1);
  return j;
}

int compareFunc(const void *left, const void *right) {
  return *(int *)left > *(int *)right;
}

int selectTopk(int *array, int n, int k)
{
    int index = partition(array, 0, n-1);
    if ((index+1) == k) {
        printf("find answer %d\n", array[k-1]);
        return array[index];
    } else if ((index+1) < k) {
        printf("search length is %d\n", n-index-1);
        return selectTopk(array+index+1, n-index-1, k-index-1);
    } else {
        printf("search length is %d\n", index);
        return selectTopk(array, index, k);
    }
}

#define N 100000000
#define K 500000
int main() {
  int low = 7986, high = 0x7fffffff;
  printf("start to gen random number\n");
  int *x = genRandom(N, low, high);
  printArray(x, 0, 10);
  printf("start to malloc y\n");
  int *y = (int *)malloc(N * sizeof(int));
  memcpy(y, (void *)x, N * sizeof(int));
  printf("start sort\n");
  qsort(y, N, sizeof(int), compareFunc);
  printArray(y, 0, 10);
  int ans1 = y[K-1];
  printf("sort ans is %d\n", ans1);
  int ans2 = selectTopk(x, N, K);
  printf("ans is %d\n", ans2);
  return 0;
}
