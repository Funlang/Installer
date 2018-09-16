/*========================================================================*/

/*		Huffman Statistic Coding ---- Huffman3			  */

/*========================================================================*/

/*========================================================================*/
#define		_HUFFMAN3_	0

#ifndef		_TREE_
#include	"tree.h"
#endif

#ifndef		_BIT_
#include	"bit.h"
#endif

#ifndef		_FILE_
#include	"file.h"
#endif

#ifndef		false
#define		false		0
#define		true		1
typedef		int		bool;
#endif


/*========================================================================*/
Tree	*LoadEmpty	();
bool	LoadValue	(Tree *t);
bool	LoadTree	();

char	treetobyte	();
bool	TreeToByte	();

bool	E_Huffman	();


/*========================================================================*/
Tree	*LoadEmpty	()			/* Tree.h */
{
	Tree		*t;

	do	t=MakeTree();			/* Tree.h */
	while (!t);

	if (ReadBit())				/* Bit.h */
	{
		t->left=LoadEmpty();
		t->right=LoadEmpty();
	}

	return t;
}

/*========================================================================*/
bool	LoadValue	(Tree *t)		/* Tree.h */
{
	if (!t->left)
		t->value=ReadByte();		/* File.h */
	else
	{
		LoadValue(t->left);
		LoadValue(t->right);
	}

	return true;
}

/*========================================================================*/
bool	LoadTree	()
{
	InitBit();				/* Bit.h */

	root=LoadEmpty();

	LoadValue(root);

	InitBit();

	return true;
}

/*========================================================================*/
char	treetobyte	()
{
	Tree		*t;			/* Tree.h */

	t=root;

	do
	{
		if (!ReadBit())			/* Bit.h */
			t=t->left;
		else
			t=t->right;
	}
	while (t->left);

	return t->value;
}

/*========================================================================*/
bool	TreeToByte	()
{
	long		l;

	for (l=0;l<Rfile.len;l++)
	{
		WriteByte(treetobyte());
	}

	DeleteTree();				/* Tree.h */
}

/*========================================================================*/
bool	E_Huffman	()
{
/*	Rseek(?);				*/
	LoadTree();

/*	Rseek(0);				*/
/*	Wseek(0);				*/
	TreeToByte();

	FlushFile();				/* File.h */

	return true;
}


/*========================================================================*/

