/*========================================================================*/

/*		Build v1.0 for Build Software <Install v1.0>		  */

/*========================================================================*/

/*========================================================================*/
#include	"huffman2.h"

#ifndef		_FILE_
#include	"file.h"
#endif

#include	<stdio.h>

#include	<stdlib.h>

#include	<dos.h>
#include	<dir.h>

#include	<string.h>

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


/*========================================================================*/
long	GetSerial	();


/*========================================================================*/
char		*_Version="Zwd\x20";
char		*rfile,*wfile;


/*========================================================================*/
bool	Error		(int p)
{
	switch (p)
	{
		case E_Format:
			printf("\nUsage:\t\tBUILD <Archive> <File1> <File2> ......\n");
						/* stdio.h */
			break;
		case E_FileNone:
			printf("\nError:\t\t[%s] isn't exist, Build can't work\n",rfile);

			break;
		case E_FileExist:
			printf("\nError:\t\t[%s] is already exist, but is'nt a Build Archive\n",wfile);

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

			if (l==GetSerial())
				b=true;
		}
	}
	else
	{
		WriteLong(*(long*)_Version);	/* File.h */
		WriteLong(GetSerial());		/* File.h */
	}

	return b;
}

/*========================================================================*/
long	GetSerial	()
{
	struct REGPACK	r;			/* dos.h */
	int		disk;
	char		*ser;
	long		s;

	disk=getdisk();				/* dir.h */
	setdisk(0);				/* dir.h */

	ser=malloc(24);				/* alloc.h */

	r.r_ax=0x6900;
	r.r_bx=0x0000;
	r.r_cx=0x0000;
	r.r_dx=FP_OFF(ser);			/* dos.h */
	r.r_ds=FP_SEG(ser);			/* dos.h */

	intr(0x21,&r);				/* dos.h */

	s=*(long*)(ser+2);

	free (ser);				/* alloc.h */

	setdisk(disk);				/* dir.h */

	return s;
}

/*========================================================================*/
bool	Index		()
{
	long		l;
	int		i=0;

	ResetWfile(wfile);
	l=filelength(Wfile.fp);			/* File.h,io.h */
	Wseek(l);				/* File.h */

	while (rfile[i])
	{
		WriteByte(rfile[i]);		/* File.h */
		i++;
	}
	WriteByte(0);				/* File.h */

	WriteLong(Rfile.len);			/* File.h */

	return true;
}

/*========================================================================*/
bool	main		(int argc,char *argv[])
{
	int		i;

	printf("\nBUILD v1.0\tCopyright(c) Zhang Weidong, 1999-2000, All Rights Reserved.\n");

	if ( argc<3)
		Error(E_Format);

	for (i=2;i<argc;i++)
	{
		rfile=strupr(argv[i]);		/* string.h */
		if (!SearchFile(rfile))		/* File.h */
			Error(E_FileNone);
	}

	wfile=strupr(argv[1]);			/* string.h */
	if (SearchFile(wfile))			/* File.h */
	{
		InitFile(wfile,NULL);		/* alloc.h,File.h */

		if (Head(false))
			ResetFile(NULL,wfile);	/* alloc.h,File.h */
		else
		{
			DeleteFile();		/* File.h */
			Error(E_FileExist);
		}
	}
	else
		InitFile(NULL,wfile);		/* alloc.h,File.h */

	Head(true);

	for (i=2;i<argc;i++)
	{
		rfile=argv[i];
		printf("\n%d\t[%s]\tAdding\t[  ]",i-1,rfile);

		ResetRfile(rfile);

		Index();
		C_Huffman();			/* Huffman2.h */

		gotoxy(wherex()-3,wherey());
		printf("ok");
	}

	DeleteFile();

	printf("\n\nSuccess:\t[%s] is build, use INSTALL v1.0 to install\n",wfile);
						/* stdio.h */

	return true;
}


/*========================================================================*/

