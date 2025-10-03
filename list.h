#ifndef __LIST_H__
#define __LIST_H__

#include <stdlib.h>

typedef struct ListNode ListNode_t;

struct ListNode
{
	void *data;
	ListNode_t *next;
};

struct List
{
	struct ListNode *head;
	struct ListNode *foot;
	size_t n;
};

// List functions

struct List *newList();
void appendToList(struct List *ls, void *data);
void traverseList(struct List *ls, void (*fn)(void *data));

/* defined in list.c but doesn't need to be declared here */
// void freeListNodeRec(struct ListNode *ln);

void freeList(struct List *ls, void (*freeData)(void *data));

#endif