/*========================================================================*/

/*		Huffman Statistic Coding ---- File			  */

/*========================================================================*/

/*========================================================================*/
#ifndef	__COMPACT__
#error	File Buffers must run in COMPACT mode.
#endif


/*========================================================================*/
#include	<dir.h>
#include	<dos.h>

#include	<alloc.h>

#include	<io.h>
#include	<fcntl.h>
#include	<sys\stat.h>


/*========================================================================*/
#define		_FILE_		0

#ifndef		false
#define		false		0
#define		true		1
typedef		int		bool;
#endif

#define		Block		0x8000		/* 32KB */


/*========================================================================*/
typedef		struct
{
	int		fp;

	long		len;

	char		*buff;

	long		from;
	int		seek;
}
File;


/*========================================================================*/
bool	SearchFile	(char *file);
bool	InitFile	(char *rf,char *wf);
bool	ResetFile	(char *rf,char *wf);

bool	ResetRfile	(char *rf);
bool	Rseek		(long s);
char	ReadByte	();
long	ReadLong	();

bool	ResetWfile	(char *wf);
bool	Wseek		(long s);
bool	WriteByte	(char ch);
bool	WriteLong	(long l);

bool	FlushFile	();
bool	CloseFile	(int fp);
bool	DeleteFile	();


/*========================================================================*/
File		Rfile;
File		Wfile;


/*========================================================================*/
bool	SearchFile	(char *file)
{
	struct ffblk	fb;			/* dir.h */

	if ( findfirst(file,&fb,FA_ARCH) == -1)	/* dir.h,dos.h */
		return false;

	return true;
}

/*========================================================================*/
bool	InitFile	(char *rf,char *wf)
{
	do	Rfile.buff=malloc(Block);	/* alloc.h */
	while (!Rfile.buff);

	do	Wfile.buff=malloc(Block);	/* alloc.h */
	while (!Wfile.buff);

	Rfile.fp=Wfile.fp=0;

	ResetFile(rf,wf);

	return true;
}

/*========================================================================*/
bool	ResetFile	(char *rf,char *wf)
{
	ResetRfile(rf);
	ResetWfile(wf);

	return true;
}

/*========================================================================*/
bool	ResetRfile	(char *rf)
{
	CloseFile(Rfile.fp);

	Rfile.fp=open(rf,O_RDONLY|O_BINARY);	/* io.h,fcntl.h */

	if (Rfile.fp==-1)
	{
		Rfile.fp=0;

		return false;
	}

	Rfile.len=filelength(Rfile.fp);		/* io.h */
	Rseek(0L);

	return true;
}

/*========================================================================*/
bool	Rseek		(long s)
{
	Rfile.from=s;
	Rfile.seek=-1;

	return true;
}

/*========================================================================*/
char	ReadByte	()
{
	char		ch;

	if (Rfile.seek<0)
	{
		lseek(Rfile.fp,Rfile.from,0);	/* io.h */
		read(Rfile.fp,Rfile.buff,Block);/* io.h */

		Rfile.from+=Block;
		Rfile.seek=0;
	}

	ch=Rfile.buff[Rfile.seek];
	Rfile.seek++;

	return ch;
}

/*========================================================================*/
long	ReadLong	()
{
	long		l;
	int		i;

	for (i=0;i<4;i++)
		((char*)(&l))[i]=ReadByte();

	return l;
}

/*========================================================================*/
bool	ResetWfile	(char *wf)
{
	if (Wfile.fp)
		FlushFile();

	CloseFile(Wfile.fp);

	if (SearchFile(wf))
		Wfile.fp=open(wf,O_RDWR|O_BINARY);
						/* io.h,fcntl.h */
	else
		Wfile.fp=open(wf,O_CREAT|O_BINARY,S_IWRITE);
						/* io.h,fcntl.h,sys\stat.h */
	if (Wfile.fp==-1)
	{
		Wfile.fp=0;
		return false;
	}

	Wfile.len=0L;
	Wseek(0L);

	return true;
}

/*========================================================================*/
bool	Wseek		(long s)
{
	Wfile.from=s;
	Wfile.seek=0;

	return true;
}

/*========================================================================*/
bool	WriteByte	(char ch)
{
	if (Wfile.seek<0)
	{
		lseek(Wfile.fp,Wfile.from,0);	/* io.h */
		write(Wfile.fp,Wfile.buff,Block);
						/* io.h */

		Wfile.from+=Block;
		Wfile.seek=0;
	}

	Wfile.buff[Wfile.seek]=ch;
	Wfile.seek++;

	return true;
}

/*========================================================================*/
bool	WriteLong	(long l)
{
	int		i;

	for (i=0;i<4;i++)
		WriteByte(((char*)(&l))[i]);

	return true;
}

/*========================================================================*/
bool	FlushFile	()
{
	if (Wfile.fp && Wfile.seek)
	{
		lseek(Wfile.fp,Wfile.from,0);	/* io.h */
		write(Wfile.fp,Wfile.buff,Wfile.seek);
						/* io.h */
	}

	return true;
}

/*========================================================================*/
bool	CloseFile	(int fp)
{
	if (fp)
		close(fp);			/* io.h */

	return true;
}

/*========================================================================*/
bool	DeleteFile	()
{
	FlushFile();

	CloseFile(Rfile.fp);
	CloseFile(Wfile.fp);

	free (Rfile.buff);			/* alloc.h */
	free (Wfile.buff);			/* alloc.h */

	return true;
}


/*========================================================================*/

