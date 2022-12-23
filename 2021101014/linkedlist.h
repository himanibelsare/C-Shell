#ifndef __LINKEDLIST_H__
#define __LINKEDLIST_H__

typedef int DataType;

typedef struct LL_Node {
	DataType val;
	struct LL_Node *next;
} LL_Node;

typedef struct LL {
	int size;
	LL_Node *head;
} LL;

LL *LL_init();
int LL_empty(LL *l);
int LL_Size(LL *l);
void LL_add(LL *l, int p, DataType val);
int LL_search(LL *l, DataType val);
void LL_delete(LL *l, DataType val);

LL* bgp;

#endif