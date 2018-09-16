/*========================================================================*/

/*		Huffman Statistic Coding ---- Bit			  */

/*========================================================================*/

/*========================================================================*/
#define		_BIT_		0

#ifndef		_FILE_
#include	"file.h"
#endif

#ifndef		false
#define		false		0
#define		true		1
typedef		int		bool;
#endif


/*========================================================================*/
typedef		struct
{
	unsigned long	b32;
	int		len;
}
Bit;


/*========================================================================*/
bool	InitBit		();
bool	WriteBit	(bool b);
bool	WriteBits	(Bit bs);
bool	FlushBit	();


/*========================================================================*/
Bit		bit;


/*========================================================================*/
bool	InitBit		()
{
	bit.b32=0L;
	bit.len=0;

	return true;
}

/*========================================================================*/
bool	ReadBit		()
{
	bool		b;

	if (bit.len==0)
	{
		bit.b32=ReadLong();		/* File.h */
		bit.len=32;
	}

	if (bit.b32 & 0x80000000)
		b=true;
	else
		b=false;

	bit.b32<<=1;
	bit.len--;

	return b;
}

/*========================================================================*/
bool	WriteBit	(bool b)
{
	if (b==false || b==true)
	{
		bit.b32<<=1;
		bit.b32+=b;
		bit.len++;

		if (bit.len==32)
		{
			WriteLong(bit.b32);	/* File.h */
			InitBit();
		}

		return true;
	}
	else
		return false;
}

/*========================================================================*/
bool	WriteBits	(Bit bs)
{
	Bit		b;

	if (bit.len+bs.len<=32)
	{
		bit.b32<<=bs.len;
		bit.b32+=bs.b32;
		bit.len+=bs.len;

		if (bit.len==32)
		{
			WriteLong(bit.b32);	/* File.h */
			InitBit();
		}
	}
	else
	{
		b.b32=bs.b32;

		b.len=bs.len-(32-bit.len);

		b.b32>>=(b.len);

		bit.b32<<=(32-bit.len);
		bit.b32+=b.b32;

		WriteLong(bit.b32);		/* File.h */

		bit.b32=bs.b32;
		bit.b32<<=(32-b.len);
		bit.b32>>=(32-b.len);
		bit.len=b.len;
	}

	return true;
}

/*========================================================================*/
bool	FlushBit	()
{
	if (bit.len)
	{
		bit.b32<<=(32-bit.len);
		WriteLong(bit.b32);		/* File.h */
	}

	return true;
}


/*========================================================================*/

