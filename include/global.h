#ifndef __GLOBAL_H__
#define __GLOBAL_H__


char *base_file_name(char *full_filename);
#define FL(abc) "%d:%s,%d,"abc,0/*OSTimeGet()*/,base_file_name(__FILE__),__LINE__ 


void assert_mine(char *filename,int lineno,int value);
#define ASSERT_MINE(value) do{assert_mine(__FILE__,__LINE__,value);}while(0)


#define CONF_FILENAME "MortageApp.ini"


typedef unsigned char  uint8;                   /* defined for unsigned 8-bits integer variable 	?T¡¤?o?8????D¨ª¡À?¨¢?  */
typedef signed   char  int8;                    /* defined for signed 8-bits integer variable		¨®D¡¤?o?8????D¨ª¡À?¨¢?  */
typedef unsigned short uint16;                  /* defined for unsigned 16-bits integer variable 	?T¡¤?o?16????D¨ª¡À?¨¢? */
typedef signed   short int16;                   /* defined for signed 16-bits integer variable 		¨®D¡¤?o?16????D¨ª¡À?¨¢? */
typedef unsigned long   uint32;                  /* defined for unsigned 32-bits integer variable 	?T¡¤?o?32????D¨ª¡À?¨¢? */
typedef signed   long   int32;                   /* defined for signed 32-bits integer variable 		¨®D¡¤?o?32????D¨ª¡À?¨¢? */
typedef float          fp32;                    /* single precision floating point variable (32bits) ¦Ì£¤???¨¨??¦Ì?¨ºy¡ê¡§32??3¡è?¨¨¡ê? */
typedef double         fp64;                    /* double precision floating point variable (64bits) ?????¨¨??¦Ì?¨ºy¡ê¡§64??3¡è?¨¨¡ê? */


typedef uint8 BYTE;
typedef uint32 DWORD;
typedef unsigned int UINT;
typedef void * HANDLE;
typedef int BOOL;

#ifndef INVALID_HANDLE_VALUE
#define INVALID_HANDLE_VALUE (-1)
#endif
#if 0
#define FALSE (0)
#define TRUE (1)
#endif
typedef struct{
    uint8 *p;
    int len;
} UP_AND_LEN;
#define MIN(a,b) (a>b?b:a)
#define MAX(a,b) (a>b?a:b)
#define FT_VAR (0x3)
#define FT_REMAIN (0x4)
#define FT_FIX_N(n) ((0x7788<<16)|n)
UP_AND_LEN fieldPick(uint8 *data,int data_len,uint32 fld_type_lst[],int fld_idx);
int fieldTypeListChk(uint8 *data,int data_len,uint32 fld_type_lst[]);
int getNum(char *num_buf,int len);

#endif
