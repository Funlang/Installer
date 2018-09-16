/*========================================================================*/

/*		Huffman Statistic Coding ---- Huffman1			  */

/*========================================================================*/

/*========================================================================*/
#define		_HUFFMAN1_	0

#ifndef		_ARRAYS_
#include	"arrays.h"
#endif

#ifndef		_LIST_
#include	"list.h"
#endif

#ifndef		_TREE_
#include	"tree.h"
#endif

#ifndef		_BITS_
#include	"bits.h"
#endif

#ifndef		false
#define		false		0
#define		true		1
typedef		int		bool;
#endif


/*========================================================================*/
bool	ArraysToList	();
bool	ListToTree	();

bool	Coding		(Tree *t,unsigned long b32,int len);
bool	TreeToBits	();


/*========================================================================*/
bool	ArraysToList	()
{
	int		i;

	InitList();				/* List.h */

	for (i=0;i<256;i++)
	{
		if (arrays[i].tree)		/* Arrays.h */
			InsertList(arrays[i].tree);
						/* List.h */
	}

	DeleteArrays();				/* Arrays.h */

	return true;
}

/*========================================================================*/
bool	ListToTree	()
{
	Tree		*t;			/* Tree.h */

	InitTree();      			/* Tree.h */

	while (true)
	{
		root=DeleteList(SearchMini());	/* Tree.h,List.h */

		t=DeleteList(SearchMini());

		if (!t)
			break;

		InsertList(CombineTree(root,t));/* Tree.h,List.h */
	}

	return true;
}

/*========================================================================*/
bool	Coding		(Tree *t,unsigned long b32,int len)
						/* Tree.h */
{
	if (!t->left)
	{
		bits[t->value].b32=b32;		/* Bits.h */
		bits[t->value].len=len;		/* Bits.h */
	}
	else
	{
		Coding(t->left,(b32<<1)+0,len+1);
		Coding(t->right,(b32<<1)+1,len+1);
	}

	return true;
}

/*========================================================================*/
bool	TreeToBits	()
{
	InitBits();				/* Bits.h */

	Coding(root,0L,0);			/* Tree.h */

	DeleteTree();				/* Tree.h */

	return true;
}


/*========================================================================*/

