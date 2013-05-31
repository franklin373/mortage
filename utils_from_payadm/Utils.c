#include <windows.h>
#include "utils.h"

#include <errno.h>
#include <stdio.h>
#include <ctype.h>  /* isdigit */

#ifndef LINELEN 
#define LINELEN 4096
#endif

#ifndef StdErr
#define StdErr stderr
#endif 


char achStrUpChar [] = {		
    '\0',  '\1',  '\2',  '\3',  '\4',  '\5',  '\6',  '\7',
   '\10', '\11', '\12', '\13', '\14', '\15', '\16', '\17',
   '\20', '\21', '\22', '\23', '\24', '\25', '\26', '\27',
   '\30', '\31', '\32', '\33', '\34', '\35', '\36', '\37',
     ' ',   '!',   '"',   '#',   '$',   '%',   '&',  '\'',
     '(',   ')',   '*',   '+',   ',',   '-',   '.',   '/',
     '0',   '1',   '2',   '3',   '4',   '5',   '6',   '7',
     '8',   '9',   ':',   ';',   '<',   '=',   '>',   '?',
     '@',   'A',   'B',   'C',   'D',   'E',   'F',   'G',
     'H',   'I',   'J',   'K',   'L',   'M',   'N',   'O',
     'P',   'Q',   'R',   'S',   'T',   'U',   'V',   'W',
     'X',   'Y',   'Z',   '[',  '\\',   ']',   '^',   '_',
     '`',   'A',   'B',   'C',   'D',   'E',   'F',   'G',
     'H',   'I',   'J',   'K',   'L',   'M',   'N',   'O',
     'P',   'Q',   'R',   'S',   'T',   'U',   'V',   'W',
     'X',   'Y',   'Z',   '{',   '|',   '}',   '~','\177',
     '€',   ' ',   ' ',   ' ',   ' ',   ' ',   ' ',   '€',
     ' ',   ' ',   ' ',   ' ',   ' ',   ' ',   ' ',   ' ',
     ' ',   ' ',   ' ',   ' ',   ' ',   ' ',   ' ',   ' ',
  '\230',   ' ',   ' ',   ' ','\234',   ' ','\236','\237',
     ' ',   ' ',   ' ',   ' ',   ' ',   ' ','\246','\247',
  '\250','\251','\252','\253','\254','\255','\256','\257',
  '\260','\261','\262','\263','\264',   ' ',   ' ',   ' ',
  '\270','\271','\272','\273','\274','\275','\276','\277',
  '\300','\301','\302','\303','\304','\305',   ' ',   ' ',
  '\310','\311','\312','\313','\314','\315','\316','\317',
  '\320','\321',   ' ',   ' ',   ' ','\325',   ' ',   ' ',
     ' ','\331','\332','\333','\334','\335',   ' ','\337',
     ' ','\341',   ' ',   ' ',   ' ',   ' ','\346','\347',
  '\350',   ' ',   ' ',   ' ',   ' ',   ' ','\356','\357',
  '\360','\361','\362','\363','\364','\365','\366','\367',
  '\370','\371','\372','\373','\374','\375','\376','\377'
};


/*char achStrUpChar [] = {		
    '\0',  '\1',  '\2',  '\3',  '\4',  '\5',  '\6',  '\7',
   '\10', '\11', '\12', '\13', '\14', '\15', '\16', '\17',
   '\20', '\21', '\22', '\23', '\24', '\25', '\26', '\27',
   '\30', '\31', '\32', '\33', '\34', '\35', '\36', '\37',
     ' ',   '!',   '"',   '#',   '$',   '%',   '&',  '\'',
     '(',   ')',   '*',   '+',   ',',   '-',   '.',   '/',
     '0',   '1',   '2',   '3',   '4',   '5',   '6',   '7',
     '8',   '9',   ':',   ';',   '<',   '=',   '>',   '?',
     '@',   'A',   'B',   'C',   'D',   'E',   'F',   'G',
     'H',   'I',   'J',   'K',   'L',   'M',   'N',   'O',
     'P',   'Q',   'R',   'S',   'T',   'U',   'V',   'W',
     'X',   'Y',   'Z',   '[',  '\\',   ']',   '^',   '_',
     '`',   'A',   'B',   'C',   'D',   'E',   'F',   'G',
     'H',   'I',   'J',   'K',   'L',   'M',   'N',   'O',
     'P',   'Q',   'R',   'S',   'T',   'U',   'V',   'W',
     'X',   'Y',   'Z',   '{',   '|',   '}',   '~','\177',
     '€',   'š',   '',   '¶',   'Ž',   '·',   '',   '€',
     'Ò',   'Ó',   'Ô',   'Ø',   '×',   'Þ',   'Ž',   '',
     '',   '’',   '’',   'â',   '™',   'ã',   'ê',   'ë',
  '\230',   '™',   'š',   '','\234',   '','\236','\237',
     'µ',   'Ö',   'à',   'é',   '¥',   '¥','\246','\247',
  '\250','\251','\252','\253','\254','\255','\256','\257',
  '\260','\261','\262','\263','\264',   'µ',   '¶',   '·',
  '\270','\271','\272','\273','\274','\275','\276','\277',
  '\300','\301','\302','\303','\304','\305',   'Ç',   'Ç',
  '\310','\311','\312','\313','\314','\315','\316','\317',
  '\320','\321',   'Ò',   'Ó',   'Ô','\325',   'Ö',   '×',
     'Ø','\331','\332','\333','\334','\335',   'Þ','\337',
     'à','\341',   'â',   'ã',   'å',   'å','\346','\347',
  '\350',   'é',   'ê',   'ë',   'í',   'í','\356','\357',
  '\360','\361','\362','\363','\364','\365','\366','\367',
  '\370','\371','\372','\373','\374','\375','\376','\377'
};*/


/* {{{ void CorrectPathName(char *pc) */
/* ersetzt Backslashes durch slashes bzw. umgekehrt. */
void CorrectPathName(char *pc)
{
#if !defined(WINDOWS) && !defined(WIN32) && !defined(MSDOS)
	for (; *pc; pc++ )
		if ( *pc == '\\' )
			*pc = '/';
#else
	for (; *pc; pc++ )
		if ( *pc == '/' )
			*pc = '\\';
#endif
}

/* }}} */
/* {{{ static BOOL ReadLine(FILE *pf, char *pc, int MaxLen ) */

static BOOL ReadLine(FILE *pf, char *pc, int MaxLen )
{
	int i;

	if ( !fgets( pc, MaxLen, pf ) )
	{ 
		*pc = 0x0;
		return(FALSE);
	}

/*	for ( ; *pc; pc++ )	                       
		if ( !isprint((int) *pc) )
			*pc = ' ';		delete by llf */
	i=strlen(pc)-1;
	if(i>=0&&pc[i]=='\n')
		pc[i]='\0';

	return( TRUE );
}

/* }}} */
/* {{{ char *NormalizeStringUpCase(char *pszString) */
/** Entfernt Leerzeichen am Anfang und am Ende sowie mehrfache
 *  Leerzeichen, wandelt Klein- in Groábuchstaben.
 *  @return Zeiger auf normalisierte Zeichenkette.
 */
char *NormalizeStringUpCase(char *pszString)
{
	char *s = pszString;
	char *t = pszString;

	while ((s[0]==' ')||(s[0]=='\t')) ++s;

	while ((*t++ = StrUpChar(*s++)) != 0)
		if ((s[0]==' ')||(s[0]=='\t')) {
			while ((s[1]==' ')||(s[1]=='\t')) ++s;
			if (s[1]==0) ++s;
		}

	return (pszString);
} /* NormalizeStringUpCase */
/* }}} */
/* {{{ void NormalizeString(char *s ) */
void NormalizeString(char *s )
/* remove leading and trailing spaces */
{
	int l, l2;

	l = strlen(s);
	while ( l &&( s[l-1] == ' ' ) )                /* remove trailing spaces */
		s[--l] = 0x0;
	for ( l=0; s[l] == ' '; l++ )                  /* number of leading spaces */
		;
	for ( l2=l; s[l2]; l2++ )
		s[l2-l] = s[l2];
	s[l2-l] = 0x0;
}

/* }}} */
/* {{{ static int StringIsEmpty(char *pc) */
static int StringIsEmpty(char *pc)
{ 
	if ( !pc[0] )
		return 1;
	for ( ; (*pc==' ')||(*pc=='\t')||(*pc=='\r')||(*pc=='\n'); pc++ )
		;
	return( *pc == 0x0 );
}

/* }}} */
/* {{{ int TCU_GetProfileString(const char *, const char *, const char *, char *, int, BOOL) */
/* return codes:
    1 oder 2: ConfgiFilename nicht gefunden
    3: Section nicht gefunden
    4: FieldName nicht gefunden 
*/
int TCU_GetProfileString( const char *ConfigFilename, const char *Section, 
const char *FieldName,
char *Value, int MaxValueLen, BOOL NormalizeNames )
{
	FILE *cf;
	static char fn[512];
	char line[LINELEN+1], keyword[LINELEN+1], value[LINELEN+1], *pc;
	int LineNo=0, ret=3,iNullOffset=0;
	BOOL SectionFound=FALSE;

#ifdef UTIL_Debug
	fprintf( StdErr, "trying config file '%s'\n", ConfigFilename );
#endif
	*value = 0x0;
	if ( (cf = fopen( ConfigFilename, "rt" ))==NULL )  /* evtl. vorgegebenen Namen */
	{ 
		if ( getenv("HOME") )                     /* sonst cox im eigenen home */
		{ 
			strcpy( fn, getenv("HOME") );
			CorrectPathName( fn );
			if ( fn[strlen(fn)-1] != '/' )
				strcat( fn, "/" );
			strcat( fn, ConfigFilename );
#ifdef UTIL_Debug
			fprintf( StdErr, "trying config file '%s'\n", fn );
#endif
			if ( (cf = fopen( fn, "rt" ))==NULL )
			{ 
				fprintf( StdErr, "cannot read config-file (%s:[%s] %s)\n", fn, Section, FieldName );
				ret = 1;
				goto ende;
			}
		}
		if ( !cf )                                /* sonst in /usr/local suchen */
		{
#ifdef UNIX
			strcpy( fn, "/usr/local/etc/" );
#else
			strcpy( fn, "c:/etc/" );
#endif
			strcat( fn, ConfigFilename );
			CorrectPathName( fn );
#ifdef UTIL_Debug
			fprintf( StdErr, "trying config file '%s'\n", fn );
#endif
			if ( (cf = fopen( fn, "rt" ))==NULL )
			{ 
				fprintf( StdErr, "cannot read config-file (%s:[%s] %s)\n", fn, Section, FieldName );
				ret = 2;
				goto ende;
			}
		}
	}
	while ( ReadLine( cf, line, LINELEN ) )
	{ 
		LineNo++;
		if ( line[0] == '[' )	  /* Start of Section ? */
		{ 
                        if(SectionFound==TRUE&&FieldName==NULL){
                                Value[iNullOffset]='\0';
                                ret=0;
                                goto ende;
                        }
			pc = strchr(line,']');
			if ( pc )
				*pc = 0x0;	/* ab ']' loeschen */
			else fprintf( StdErr, "%s:%d sectionnames must be enclosed in '[' ']' \n", 
			    ConfigFilename, LineNo );
			if ( NormalizeNames )
				NormalizeStringUpCase( &line[1] );
			else NormalizeString( &line[1] );
			if ( strcmp( &line[1], Section ) ){
                                SectionFound=FALSE;    /*I don't know why such simple code should add by llf*/
				continue;
                        }       
			else 
			{ 
				SectionFound = TRUE;
				ret = 4;
			}
		}
		else if ( line[0] == ';' )
			;                           /* Kommentarzeile */
		else if ( SectionFound )
		{ 
			pc = strchr( line, '=' );
			if ( pc )
			{ 
				strncpy( keyword, line, pc-line );
				keyword[pc-line] = 0x0;
				if ( NormalizeNames )
					NormalizeStringUpCase( keyword );
				else NormalizeString( keyword );
				sscanf( ++pc, "%s", value );

                                if(FieldName==NULL){
                                        if(iNullOffset+strlen(keyword)+1>=MaxValueLen){
                                                ret=10;
                                                goto ende;
                                        }
                                        strcpy(&Value[iNullOffset],keyword);
                                        iNullOffset=iNullOffset+strlen(keyword)+1;
                                        ret=0;
                                        continue;
                                }

                                
				if ( !strcmp( keyword, FieldName ) )
				{ 
					strncpy( Value, pc, MaxValueLen );
					NormalizeString(Value);
					ret = 0;
					goto ende;
				}
			}
			else if ( !StringIsEmpty(line) )
				fprintf( StdErr, "%s:%d keyword and value must be separated with '=' (%s)\n", 
				    ConfigFilename, LineNo, line);
			/* sonst ist es eine Leerzeile */
		}
	}

ende:
	if ( cf )
		fclose( cf );
        if(FieldName==NULL){
                Value[iNullOffset]='\0';
                Value[iNullOffset+1]='\0';
        }
	return ret;
}

/* }}} */

/* {{{ char *TC_strtok_r(char *s1, const char *s2, char**lasts) */

#include <string.h>

char *TC_strtok_r(char *s1, const char *s2, char**lasts)
{

#if defined(_WINDOWS) || defined(WIN32) || !defined(HAVE_STRTOK_R)

	char *token;

	if(lasts == NULL)
	{
		errno = EINVAL;
		return NULL;
	}

	if (s1 == NULL)
	{
		if (*lasts == NULL)
		{
			errno = EINVAL;
			return NULL;
		}
		else
			s1 = *lasts;
	}

	/* Scan leading delimiters.  */
	s1 += strspn(s1, s2);
	if (*s1 == '\0')
	{
		*lasts = NULL;
		return NULL;
	}

	/* Find the end of the token.  */
	token = s1;
	s1 = strpbrk(token, s2);
	if (s1 == NULL)
		/* This token finishes the string.  */
		*lasts = NULL;
	else
	{
		/* Terminate the token and make *LASTS point past it.  */
		*s1 = '\0';
		*lasts = s1 + 1;
	}
	return token;

#else

	return strtok_r(s1,s2,lasts);

#endif /* !WINDOWS && !WIN32 */
}






int FindField( const char *ConfigFilename, const char *Section, 
const char *FieldName,
int *pOffset,int *pLen )
{
	FILE *cf;
	static char fn[512];
	char line[LINELEN+1], keyword[LINELEN+1], value[LINELEN+1], *pc;
	int LineNo=0, ret=3;
	BOOL SectionFound=FALSE;
	int LineBeginOff;

#ifdef UTIL_Debug
	fprintf( StdErr, "trying config file '%s'\n", ConfigFilename );
#endif
	*value = 0x0;
	if ( (cf = fopen( ConfigFilename, "rt" ))==NULL )  /* evtl. vorgegebenen Namen */
	{ 
		if ( getenv("HOME") )                     /* sonst cox im eigenen home */
		{ 
			strcpy( fn, getenv("HOME") );
			CorrectPathName( fn );
			if ( fn[strlen(fn)-1] != '/' )
				strcat( fn, "/" );
			strcat( fn, ConfigFilename );
#ifdef UTIL_Debug
			fprintf( StdErr, "trying config file '%s'\n", fn );
#endif
			if ( (cf = fopen( fn, "rt" ))==NULL )
			{ 
				fprintf( StdErr, "cannot read config-file (%s:[%s] %s)\n", fn, Section, FieldName );
				ret = 1;
				goto ende;
			}
		}
		if ( !cf )                                /* sonst in /usr/local suchen */
		{
#ifdef UNIX
			strcpy( fn, "/usr/local/etc/" );
#else
			strcpy( fn, "c:/etc/" );
#endif
			strcat( fn, ConfigFilename );
			CorrectPathName( fn );
#ifdef UTIL_Debug
			fprintf( StdErr, "trying config file '%s'\n", fn );
#endif
			if ( (cf = fopen( fn, "rt" ))==NULL )
			{ 
				fprintf( StdErr, "cannot read config-file (%s:[%s] %s)\n", fn, Section, FieldName );
				ret = 2;
				goto ende;
			}
		}
	}
	while ( LineBeginOff=ftell(cf),ReadLine( cf, line, LINELEN ) )
	{ 
		LineNo++;
		if ( line[0] == '[' )	  /* Start of Section ? */
		{ 
			if(SectionFound==TRUE){
				*pOffset=LineBeginOff;
				*pLen=0;	
				ret = 0;
				goto ende;

			}
			pc = strchr(line,']');
			if ( pc )
				*pc = 0x0;	/* ab ']' loeschen */
			else fprintf( StdErr, "%s:%d sectionnames must be enclosed in '[' ']' \n", 
			    ConfigFilename, LineNo );
			NormalizeString( &line[1] );
			if ( strcmp( &line[1], Section ) ){
                                SectionFound=FALSE;
				continue;
                        }
			else 
			{ 
				SectionFound = TRUE;
				ret = 4;
			}
		}
		else if ( line[0] == ';' )
			;                           /* Kommentarzeile */
		else if ( SectionFound )
		{ 
			pc = strchr( line, '=' );
			if ( pc )
			{ 
				strncpy( keyword, line, pc-line );
				keyword[pc-line] = 0x0;
				NormalizeString( keyword );
				sscanf( ++pc, "%s", value );
				if ( !strcmp( keyword, FieldName ) )
				{ 
					*pOffset=LineBeginOff;
					*pLen=ftell(cf)-LineBeginOff;	
					ret = 0;
					goto ende;
				}
			}
			else if ( !StringIsEmpty(line) )
				fprintf( StdErr, "%s:%d keyword and value must be separated with '=' (%s)\n", 
				    ConfigFilename, LineNo, line);
			/* sonst ist es eine Leerzeile */
		}
	}
	if(SectionFound==TRUE){
		*pOffset=LineBeginOff;
		*pLen=0;	
		ret = 0;
		goto ende;
	}

ende:
	if ( cf )
		fclose( cf );
	return ret;
}


int FilePartUpdate(char szFileName[],int DestOffset,int DestLen,char caSrc[],int SrcLen)
{
	FILE *fpConf,*fpTmp;
	int i,iValue;

//LogWithPlace("DestOffset=%d,DestLen=%d,caSrc=%s,SrcLen=%d\n",DestOffset,DestLen,caSrc,SrcLen);
	fpConf=fopen(szFileName,"rb");
	if(fpConf==NULL)
		return -1;
	fpTmp=tmpfile();
	for(i=0;i<DestOffset;i++){
		iValue=fgetc(fpConf);
		if(iValue==EOF)
			goto error;
		fputc(iValue,fpTmp);
	}
	for(i=0;i<DestLen;i++){
		iValue=fgetc(fpConf);
		if(iValue==EOF)
			goto error;
	}
	for(i=0;i<SrcLen;i++){
		fputc(iValue=caSrc[i],fpTmp);
	}
	for(;;){
		iValue=fgetc(fpConf);
		if(iValue==EOF)
			break;
		fputc(iValue,fpTmp);
	}
	fclose(fpConf);
	fpConf=fopen(szFileName,"wb");
	if(fpConf==NULL){
		fclose(fpTmp);
		return -1;
	}
	fseek(fpTmp,0,SEEK_SET);
	for(;;){
		iValue=fgetc(fpTmp);
		if(iValue==EOF)
			break;
		fputc(iValue,fpConf);
	}
	fclose(fpTmp);
	fclose(fpConf);
	return 0;
error:
	fclose(fpTmp);
	fclose(fpConf);
	return -1;
}

int FileAppend(char szFileName[],char szBuf[])
{
        FILE *fp;
        
        fp=fopen(szFileName,"at");
        if(fp==NULL)
                return -1;
        fprintf(fp,"%s",szBuf);
        fclose(fp);
        return 0;
}

int TCU_SetProfileString(char szFileName[],char section[],char field[],char value[])
{
	int iRtn,offset,len;
	char buf[400];

	iRtn=FindField(szFileName,section,field,&offset,&len);
	if(iRtn!=0){
                sprintf(buf,"\n[%s]\n",section);
                iRtn=FileAppend(szFileName,buf);
                if(iRtn!=0)
                        return -1;
                iRtn=FindField(szFileName,section,field,&offset,&len);
                if(iRtn!=0)
        		return -1;
	}
	if(value==NULL){
		buf[0]='\0';
	}else{
#if !defined(WINDOWS) && !defined(WIN32) && !defined(MSDOS)
		sprintf(buf,"%s=%s\n",field,value);
#else
		sprintf(buf,"%s=%s\r\n",field,value);
#endif
	}
	iRtn=FilePartUpdate(szFileName,offset,len,buf,strlen(buf));
	if(iRtn!=0){
		return -1;
	}
	return 0;
}
