#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// N * 8 / 1024 = 78.125KB
#define N 10000

typedef unsigned char bool;
typedef unsigned long ul;
typedef struct list list;

struct list
{
    ul num;
    struct list *next;
};

int is_prime(int num)
{
    bool flag = 0;
    for (int i = 2; i * i < num; ++i) {
        if (i != num && num % i == 0) {
            flag = 1; break;
        }
    }
    return flag;
} 

list *make_node(ul n)
{
    list* node = (list*) malloc(sizeof(list));
    node->num = n;
    node->next = NULL;
    return node;
}

list *make_list(bool *aux, size_t size)
{
    list *head, *p;
    head = p = make_node(0);
    size_t cnt = 0;
    for (size_t i = 0; i < size; ++i) {
        if (aux[i] == 1) {
            p->next = make_node(i);
            p = p->next;
            ++cnt;
            printf("create node %ld\n", i);
        }
    }
    head->num = cnt;
    return head;
}

list *erat_sieve(ul n)
{
    if (n > N) return NULL;
    bool *aux = (bool*) malloc(n * sizeof(bool));
    memset(aux, 0, n);
    for(ul i = 0; i < n; ++i) aux[i] = 1;
    aux[0] = aux[1] = 0;
    for(ul i = 2; i < n; ++i) {
        for (ul j = i * i; j < n; j += i)
            aux[j] = 0;
    }
    list *head = make_list(aux, n);
    free(aux);
    return head;
}

int main()
{
    size_t n = 10000;
    list *arr = erat_sieve(n);
    for (list* p = arr->next; p != NULL; p = p->next) {
        printf("%ld ", p->num);
    }
    printf("count is %ld\n", arr->num);
    printf("%ld\n", sizeof(long));
    free(arr);
    return 0;
}
