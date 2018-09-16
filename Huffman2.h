/*========================================================================*/

/*		Huffman Statistic Coding ---- Huffman2			  */

/*========================================================================*/

/*========================================================================*/
#define		_HUFFMAN2_	0

#ifndef		_FILE_
#include	"file.h"
#endif

#ifndef		_ARRAYS_
#include	"arrays.h"
#endif

#ifndef		_HUFFMAN1_
#include	"huffman1.h"
#endif

#ifndef		_TREE_
#include	"tree.h"
#endif

#ifndef		_BIT_
#include	"bit.h"
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
bool	BuildTree	();

bool	SaveEmpty	(Tree *t);
bool	SaveValue	(Tree *t);
bool	SaveTree	();

bool	ByteToBits	();

bool	C_Huffman	();


/*========================================================================*/
bool	BuildTree	()
{
	long		l;

	InitArrays();				/* Arrays.h */

	for (l=0;l<Rfile.len;l++)		/* File.h */
	{
		InsertArrays(ReadByte());	/* File.h,Arrays.h */
	}

	ArraysToList();				/* Huffman1.h */
	ListToTree();				/* Huffman1.h */

	return true;
}

/*========================================================================*/
bool	SaveEmpty	(Tree *t)		/* Tree.h */
{
	if (!t->left)
	{
		WriteBit(false);		/* Bit.h */
	}
	else
	{
		WriteBit(true);			/* Bit.h */

		SaveEmpty(t->left);
		SaveEmpty(t->right);
	}

	return true;
}

/*========================================================================*/
bool	SaveValue	(Tree *t)		/* Tree.h */
{
	if (!t->left)
	{
		WriteByte(t->value);		/* File.h */
	}
	else
	{
		SaveValue(t->left);
		SaveValue(t->right);
	}

	return true;
}

/*========================================================================*/
bool	SaveTree	()
{
	InitBit();				/* Bit.h */

	SaveEmpty(root);

	FlushBit();				/* Bit.h */

	SaveValue(root);

	return true;
}

/*========================================================================*/
bool	ByteToBits	()
{
	long		l;

	InitBit();				/* Bit.h */

	for (l=0;l<Rfile.len;l++)           	/* File.h */
		WriteBits(bits[(unsigned char)ReadByte()]);
						/* File.h,Bits.h,Bit.h */

	FlushBit();				/* Bit.h */

	DeleteBits();				/* Bits.h */

	return true;
}

/*========================================================================*/
bool	C_Huffman	()
{
	Rseek(0);				/* File.h */
	BuildTree();

/*	Wseek(?);				*/
	SaveTree();
	TreeToBits();				/* Huffman1.h */

	Rseek(0);                               /* File.h */
/*	Wseek(?);				*/
	ByteToBits();

	FlushFile();				/* File.h */

	return true;
}


/*========================================================================*/

