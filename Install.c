/*========================================================================*/

/*		Install v1.0 for Install Software <Build v1.0>		  */

/*========================================================================*/

/*========================================================================*/
#include	"huffman3.h"

#ifndef		_FILE_
#include	"file.h"
#endif

#include	<stdio.h>

#include	<stdlib.h>

#include	<dos.h>
#include	<dir.h>
#include	<alloc.h>

#include	<string.h>

#include	<conio.h>


/*========================================================================*/
#ifndef		false
#define		false		0
#define		true		1
typedef		int		bool;
#endif

#define		E_Copyright	1
#define		E_FileNone	2
#define		E_DirNone	3
#define		E_DirExist	4


/*========================================================================*/
long	GetSerial	();


/*========================================================================*/
char		*_Version="Zwd\x20";
char		*rfile="Install.ovl";
char		*wfile;
char		path[256];

int		drive=2;
int		dir=0;


/*========================================================================*/
bool	Error		(int p)
{
	switch (p)
	{
		case E_Copyright:
			printf("\nWARNING:\tInvalid Copy Software.\n");
						/* stdio.h */
			break;
		case E_FileNone:
			printf("\nError:\t\t[%s] isn't exist, Install can't work\n",rfile);

			break;
		case E_DirNone:

			return false;
		case E_DirExist:

			return false;
		default:
			break;
	}

	exit(false);				/* stdlib.h */
}

/*========================================================================*/
bool	Head		()
{
	bool		b=false;
	long		l;

	l=ReadLong();				/* File.h */

	if (l == *(long*)_Version)
	{
		l=ReadLong();			/* File.h */

		if (l==GetSerial())
			b=true;
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
void 	Screen		()
{
	int		i;

	window(1,1,80,25);			/* conio.h */
	textattr(GREEN+(BLUE<<4));
	clrscr();

	gotoxy(4,3);
	printf("INSTALL v1.0");
	gotoxy(26,3);
	printf("Copyright(c) Zhang Weidong, 1999-2000");

	gotoxy(4,4);
	for (i=0;i<74;i++)
		printf("?);

	gotoxy(26,6);
	printf("You Are Welcome");

	gotoxy(14,8);
	printf("INSTALL v1.0 is used to install program");
	gotoxy(14,9);
	printf("But it must be build by BUILD v1.0");
	gotoxy(14,11);
	printf("Now input the install path ...");
	gotoxy(14,13);
	printf("For example:");
	gotoxy(26,14);
	printf("C:\\DBMS");
	gotoxy(26,15);
	printf("C:\\USER\\DBMS");

	gotoxy(8,18);
	printf("PATH:");

	gotoxy(4,21);
	for (i=0;i<74;i++)
		printf("?);

	gotoxy(8,22);
	printf("  0%:");

	gotoxy(14,22);
	for (i=0;i<64;i++)
		printf("?);
}

/*========================================================================*/
bool	ReadKey		()
{
	int		i=0,f=i;
	char		ch,*st;

	window(14,18,77,18);
	textattr(BLUE+(GREEN<<4));
	clrscr();

	printf("%c%s",drive+'A',":\\");

	setdisk(drive);
	chdir("\\");

	st=malloc(9);

	while (true)
	{
		while ((ch=getch())==0);

		if (ch==0x1b)
			break;

		if (ch>0x20)
		{
			if (i==60)
				continue;
			if (i-f==8)
				ch='\\';

			putch(ch);

			if (ch=='\\')
			{
				st[i-f]=0;
				if (chdir(st)==-1)
				{
					ch=8;
					Error(E_DirNone);
				}
				else
					f=i+1;
			}
			else
				st[i-f]=ch;

			i++;
		}
		else if (ch==0xd)
		{
			st[i-f]=0;
			if (mkdir(st)==-1)
				Error(E_DirExist);
			else
			{
				chdir(st);
				break;
			}
		}

		if (ch==8 && i>f)
		{
			gotoxy(wherex()-1,wherey());
			putch(0x20);
			gotoxy(wherex()-1,wherey());

			i--;
		}
	}

	free (st);

	if (ch==0x1b)
		return false;

	return true;
}

/*========================================================================*/
bool	Index		()
{
	int		i=0;
	char		*p,*p1,*p2;

	do	path[i]=ReadByte();
	while (path[i] && i++<256);

	p=strrchr(path,'\\');
	if (p)
	{
		p++;

		p1=path;

		while (true)
		{
			p2=strchr(p1,'\\');

			if (p1!=p)
			{
				p2[0]=0;
				mkdir(p1);
				chdir(p1);

				dir++;
				p1=p2+1;
			}
			else
				break;
		}

		wfile=p;
	}
	else
		wfile=path;

	ResetWfile(wfile);

	Rfile.len=ReadLong();			/* File.h */

	return true;
}

/*========================================================================*/
bool	main		(int argc,char *argv[])
{
	long		len;
	int		i;

	printf("\nINSTALL v1.0\tCopyright(c) Zhang Weidong, 1999-2000, All Rights Reserved.\n");

	if (argc==2 || argc==3)
	{
		strupr(argv[argc-1]);
		if (strcmp(argv[argc-1],"/DEMO")==0)
		{
			argc--;
			drive=0;
		}
	}
	if (argc==2)
		rfile=strupr(argv[1]);

	if (!SearchFile(strupr(rfile)))		/* File.h */
		Error(E_FileNone);

	InitFile(rfile,NULL);

	if (!Head())
	{
		DeleteFile();

		Error(E_Copyright);
	}

	Screen();

	if (ReadKey())
	{
		len=filelength(Rfile.fp);

		window(1,1,80,25);

		while ((Rfile.from+Rfile.seek-Block)<len)
		{
			Index();
			E_Huffman();

			while (dir)
			{
				chdir("..");
				dir--;
			}

			i=(Rfile.from+Rfile.seek-Block)*100/len;

			gotoxy(8,22);
			printf("%3d",i);

			i*=16;
			i/=25;

			gotoxy(14,22);
			while (i)
			{
				printf("?);
				i--;
			}
		}
	}

	DeleteFile();

	window(1,1,80,25);
	textattr(7);
	clrscr();

	return true;
}


/*========================================================================*/

