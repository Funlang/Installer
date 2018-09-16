/*========================================================================*/

/*		Compress v1.0 for Make Compress Coding			  */

/*========================================================================*/

/*========================================================================*/
#include	"huffman2.h"
#include	"huffman3.h"
#include	"line.h"

#ifndef		_FILE_
#include	"file.h"
#endif

#include	<stdio.h>

#include	<stdlib.h>

#include	<ctype.h>
#include	<string.h>

#include	<io.h>
#include	<conio.h>


/*========================================================================*/
#ifndef		false
#define		false		0
#define		true		1
typedef		int		bool;
#endif

#define		E_Format	1
#define		E_FileNone	2
#define		E_FileExist	3
#define		E_NoCompress	4
#define		E_Compressed	5


/*========================================================================*/
char		*_Version="Zwd\x10";
char		*rfile,*wfile;
char		*temp="Compress.Tmp";


/*========================================================================*/
bool	Error		(int p)
{
	switch (p)
	{
		case E_Format:
			printf("\nUsage:\t\tCOMPRESS <command> <input file> <out file>\n");
						/* stdio.h */
			break;
		case E_FileNone:
			printf("\nError:\t\t[%s] isn't exist, COMPRESS can't work\n",rfile);

			break;
		case E_FileExist:
			printf("\nError:\t\t[%s] is already exist, please input a new file\n",wfile);

			break;
		case E_NoCompress:
			printf("\nError:\t\t[%s] isn't compressed by COMPRESS v1.0\n",rfile);

			break;
		case E_Compressed:
			printf("\nError:\t\t[%s] is already compressed by COMPRESS v1.0\n",rfile);

			break;
		default:
			break;
	}

	exit(false);				/* stdlib.h */
}

/*========================================================================*/
bool	Head		(bool b)
{
	long		l;

	if (!b)
	{
		l=ReadLong();			/* File.h */

		if (l == *(long*)_Version)
		{
			l=ReadLong();		/* File.h */

			if (l>0)
			{
				Rfile.len=l;	/* File.h */
				b=true;
			}
		}
	}
	else
	{
		WriteLong(*(long*)_Version);	/* File.h */
		WriteLong(Rfile.len);		/* File.h */
	}

	return b;
}

/*========================================================================*/
bool	Compress	()			/* Bits */
{
	InitFile(rfile,NULL);			/* alloc.h,File.h */

	if (Head(false))
	{
		DeleteFile();			/* File.h */

		Error(E_Compressed);
	}

	Rseek(0);

	ResetWfile(temp);
	C_Line();
	ResetWfile(NULL);
	ResetRfile(temp);

	ResetWfile(wfile);

	Head(true);

	C_Huffman();				/* Huffman2.h */

	DeleteFile();				/* File.h */

	return true;
}

/*========================================================================*/
bool	Extract		()			/* Tree */
{
	InitFile(rfile,NULL);			/* alloc.h,File.h */

	if (!Head(false))
	{
		DeleteFile();			/* File.h */

		Error(E_NoCompress);
	}

	ResetWfile(wfile);

	E_Huffman();				/* Huffman3.h */

	ResetWfile(NULL);
	ResetWfile(temp);
	ResetRfile(wfile);
	E_Line();

	DeleteFile();				/* File.h */

	return true;
}

/*========================================================================*/
bool	main		(int argc,char *argv[])
{
	char		ch;

	printf("\nCOMPRESS v1.0\tCopyright(c) Zhang Weidong, 1999-2000, All Rights Reserved.\n");

	if ( argc!=4)
		Error(E_Format);

	ch=toupper(argv[1][0]);			/* ctype.h */
	if (ch!='A' && ch!='E')
		Error(E_Format);

	rfile=strupr(argv[2]);			/* string.h */
	if (!SearchFile(rfile))			/* File.h */
		Error(E_FileNone);

	wfile=strupr(argv[3]);			/* string.h */
	if (SearchFile(wfile))			/* File.h */
		Error(E_FileExist);

	while (SearchFile(temp))		/* File.h */
		temp[0]++;

	if (ch=='A')
		printf("\nCOMPRESS:");
	else
		printf("\nEXTRACT:");

	printf("\t[%s]  ==>  [%s]  [  ]",rfile,wfile);
	gotoxy(wherex()-3,wherey());		/* conio.h */

	if (ch=='A')
		Compress();
	else
		Extract();

	printf("ok\n");

	if (ch=='A')
		unlink(temp);
	else
	{
		unlink(wfile);
		rename(temp,wfile);
	}

	return true;
}


/*========================================================================*/

