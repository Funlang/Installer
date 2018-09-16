/*========================================================================*/

/*		Huffman Statistic Coding ---- List			  */

/*========================================================================*/

/*========================================================================*/
#include	<alloc.h>


/*========================================================================*/
#define		_LIST_		0

#ifndef		_TREE_
#include	"tree.h"
#endif

#ifndef		false
#define		false		0
#define		true		1
typedef		int		bool;
#endif


/*========================================================================*/
typedef		struct	L
{
	Tree		*tree;			/* Tree.h */

	struct L	*next;
}
List;


/*========================================================================*/
bool	InitList	();
bool	InsertList	(Tree *t);
List	*SearchMini	();
Tree	*DeleteList	(List * l);


/*========================================================================*/
List		*head;


/*========================================================================*/
bool	InitList	()
{
	head=NULL;				/* alloc.h */

	return true;
}

/*========================================================================*/
bool	InsertList	(Tree *t)
{
	List		*l;

	l=malloc(sizeof(List));			/* alloc.h */

	if (l)
	{
		l->tree=t;
		l->next=head;

		head=l;

		return true;
	}
	else
		return false;
}

/*========================================================================*/
List	*SearchMini	()
{
	List		*l,*l1;
	unsigned long	c;

	l1=NULL;				/* alloc.h */

	if (!head)
		return l1;

	c=head->tree->count;

	for (l=head;l->next;l=l->next)
	{
		if (l->next->tree->count < c)
		{
			l1=l;
			c=l->next->tree->count;
		}
	}

	return l1;
}

/*========================================================================*/
Tree	*DeleteList	(List *l)
{
	List		*l1;
	Tree		*t;

	if (!l)
	{
		if (!head)
			return NULL;		/* alloc.h */

		l1=head;
		t=l1->tree;

		head=head->next;
	}
	else
	{
		l1=l->next;
		t=l1->tree;

		l->next=l1->next;
	}

	free (l1);				/* alloc.h */

	return t;
}


/*========================================================================*/

