#include <stdlib.h>
#include <assert.h>

typedef int elem;

typedef struct list list;
typedef struct list *ptr_node;
typedef struct list *head;

typedef struct dlist dlist;
typedef struct dlist *ptr_dnode;
typedef struct list  *dhead;

// single linked list
head create_list(void);
head create_list_by_array(elem *array, int length);
head create_list(void);

int insert(head list, elem data, int position);
int append(head list, elem data);
int remove_data(head list, elem data);
int remove_all(head list, elem data);
int find(head list, elem data);
int find_range(head list, int left, int right, elem data);
int free_list(head list);

ptr_node next(ptr_node node);
elem get_data(ptr_node node);
ptr_node find_pre(head list, elem data);

// double linked list
ptr_dnode create_dnode(elem);
ptr_dnode insert_node(ptr_dnode, elem);
ptr_dnode remove_node(ptr_dnode);
ptr_dnode find_node(ptr_dnode, elem);

ptr_dnode dnext(ptr_dnode);
ptr_dnode dpre(ptr_dnode);
elem get_elem(ptr_dnode);