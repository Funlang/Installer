/*========================================================================*/

/*		Huffman Statistic Coding ---- Arrays			  */

/*========================================================================*/

/*========================================================================*/
#include	<alloc.h>


/*========================================================================*/
#define		_ARRAYS_	0

#ifndef		_TREE_
#include	"tree.h"
#endif

#ifndef		false
#define		false		0
#define		true		1
typedef		int		bool;
#endif


/*========================================================================*/
typedef		struct
{
	Tree		*tree;			/* Tree.h */
}
Arrays;


/*========================================================================*/
bool	InitArrays	();
bool	InsertArrays	(unsigned char v);
bool	DeleteArrays	();


/*========================================================================*/
Arrays		*arrays;


/*========================================================================*/
bool	InitArrays	()
{
	int		i;

	arrays=malloc(sizeof(Arrays)*256);	/* alloc.h */

	if (arrays)
	{
		for (i=0;i<256;i++)
			arrays[i].tree=NULL;	/* alloc.h */

		return true;
	}
	else
		return false;
}

/*========================================================================*/
bool	InsertArrays	(unsigned char v)
{
	if (arrays[v].tree)
	{
		arrays[v].tree->count++;

		return true;
	}
	else
	{
		arrays[v].tree=MakeTree();	/* Tree.h */

		if (arrays[v].tree)
		{
			arrays[v].tree->value=v;
			arrays[v].tree->count=1;

			return true;
		}
		else
			return false;
	}
}

/*========================================================================*/
bool	DeleteArrays	()
{
	free (arrays);				/* alloc.h */

	return true;
}


/*========================================================================*/

