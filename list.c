#include "list.h"
#include <assert.h>
#include <stdio.h>

// ==============
// List functions
// ==============

struct List *newList()
{
	struct List *ls = (struct List *)malloc(sizeof(struct List));
	ls->head = NULL;
	ls->foot = NULL;
	ls->n = 0;
	return ls;
}

void appendToList(struct List *ls, void *data)
{
	struct ListNode *ln = (struct ListNode *)malloc(sizeof(struct ListNode));
	assert(ln);
	ln->data = data;
	ln->next = NULL;

	if (ls->foot)
	{
		ls->foot->next = ln;
		ls->foot = ln;
	}
	else
	{
		ls->head = ln;
		ls->foot = ln;
	}

	(ls->n)++;
}

void traverseList(struct List *ls, void (*fn)(void *data))
{
	for (struct ListNode *ln = ls->head; ln != NULL; ln = ln->next)
		fn(ln->data);
}

void freeListNodeRec(struct ListNode *ln)
{
	if (ln->next)
		freeListNodeRec(ln->next);

	free(ln);
}

void freeList(struct List *ls, void (*freeData)(void *data))
{
	traverseList(ls, freeData);
	if (ls->head)
		freeListNodeRec(ls->head);
	free(ls);
}

//