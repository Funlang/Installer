/*========================================================================*/

/*		Huffman Statistic Coding ---- Tree			  */

/*========================================================================*/

/*========================================================================*/
#include	<alloc.h>


/*========================================================================*/
#define		_TREE_		0

#ifndef		false
#define		false		0
#define		true		1
typedef		int		bool;
#endif


/*========================================================================*/
typedef		struct	T
{
	unsigned char	value;
	unsigned long	count;

	struct T	*left,*right;
}
Tree;


/*========================================================================*/
bool	InitTree	();
Tree	*MakeTree	();
Tree	*CombineTree	(Tree *t1,Tree *t2);
bool	DelTree		(Tree *t);
bool	DeleteTree	();


/*========================================================================*/
Tree		*root;


/*========================================================================*/
bool	InitTree	()
{
	root=NULL;				/* alloc.h */

	return true;
}

/*========================================================================*/
Tree	*MakeTree	()
{
	Tree		*t;

	t=malloc(sizeof(Tree));			/* alloc.h */

	if (t)
	{
		t->value=0;
		t->count=0L;

		t->left=t->right=NULL;		/* alloc.h */
	}

	return t;
}

/*========================================================================*/
Tree	*CombineTree	(Tree *t1,Tree *t2)
{
	Tree		*t;

	t=MakeTree();

	if (t)
	{
		t->count=t1->count+t2->count;

		t->left=t1;
		t->right=t2;
	}

	return t;
}

/*========================================================================*/
bool	DelTree		(Tree *t)
{
	if (t->left)
	{
		DelTree(t->left);
		t->left=NULL;			/* alloc.h */
	}

	if (t->right)
	{
		DelTree(t->right);
		t->right=NULL;			/* alloc.h */
	}

	if (!t->left && !t->right)
		free (t);			/* alloc.h */

	return true;
}

/*========================================================================*/
bool	DeleteTree	()
{
	return DelTree(root);
}


/*========================================================================*/

