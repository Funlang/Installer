/*========================================================================*/

/*		Compress v1.0 ---- Line Coding				  */

/*========================================================================*/

/*========================================================================*/
#ifndef		_FILE_
#include	"file.h"
#endif

/*========================================================================*/
#define		_LINE_		0

#ifndef		false
#define		false		0
#define		true		1
typedef		int		bool;
#endif


/*========================================================================*/
bool	C_Line		();
bool	E_Line		();


/*========================================================================*/
bool	C_Line		()
{
	long		l;

	char		c,ch,t;
	int		count=0;

	c=ReadByte();

	for (l=0;l<Rfile.len;l++)
	{
		ch=ReadByte();

		if (c==ch && count<255)
		{
			count++;
			continue;
		}

		t=c;
		c=ch;
		ch=t;

		WriteByte(ch);

		if (count)
		{
			WriteByte(ch);
			WriteByte((unsigned char)count);
			count=0;
		}
	}

	FlushFile();

	return true;
}

/*========================================================================*/
bool	E_Line		()
{
	long		l;

	char		c,ch;
	int		count;

	c=ReadByte();
	WriteByte(c);

	for (l=1;l<Rfile.len;l++)
	{
		ch=ReadByte();
		WriteByte(ch);

		if (c==ch && l<Rfile.len-1)
		{
			count=(unsigned char)ReadByte();
			l++;

			count--;
			while (count)
			{
				WriteByte(ch);
				count--;
			}

			if (l<Rfile.len-1)
			{
				c=ReadByte();
				WriteByte(c);
				l++;
			}
		}
		else
			c=ch;
	}

	FlushFile();

	return true;
}


/*========================================================================*/

