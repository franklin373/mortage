#include "includes.h"

char *base_file_name(char *full_filename)
{
	char *result=full_filename;
	int i;
	
	for(i=0;full_filename[i];i++){
		if(full_filename[i]=='\\'){
			result=full_filename+i+1;
		}
	}
	return result;
}
#if 1 //in DM, assert_mine in other place
void assert_mine(char *filename,int lineno,int value)
{
        char szBuf[1000];
        
	if(!value){
#if 0	
		gi32LogFlag|=LOG_MASK_PRN;//let next log state work
Log2FreeUart(LOG_MASK_PRN, FL("ASSERT,FN=%s,LN=%d,VL=%d\r\n"),filename,lineno,value);
mymyprintf("ASSERT ERROR\r\n");
		OS_ENTER_CRITICAL();
	    	vMotorPowerCtrl(0);                         /* power off motor and print head */
		vPrnHeadPowerCtrl(0);			//to protect since press key need many time
		for(;;){
			GLedOn();
			RLedOn();
			BLedOn();
		}
#endif
            sprintf(szBuf,"Meet unexpect condition, program will exit.\n"FL("ASSERT,FN=%s,LN=%d,VL=%d\r\n"),filename,lineno,value);
            fprintf(stderr,"%s",szBuf);
            exit(-1);
	}
}
#endif
#if 0
size_t  fread_mine(void * ptr, size_t nitems, FILE * stream)
{
    int offset,nRtn;
    
    for(offset=0;offset<nitems;){
        nRtn=fread((char *)ptr+offset,1,nitems-offset,stream);
        if(nRtn>0){
            offset+=nRtn;
            continue;
        }
        break;
    }
    if(offset>0){
        return offset;
    }else{
        return nRtn;
    }
}
#endif

#if 0
uint16
htons_mine(uint16 n)
{
  return ((n & 0xff) << 8) | ((n & 0xff00) >> 8);
}

uint16
ntohs_mine(uint16 n)
{
  return htons_mine(n);
}

uint32
htonl_mine(uint32 n)
{
  return ((n & 0xff) << 24) |
    ((n & 0xff00) << 8) |
    ((n & 0xff0000) >> 8) |
    ((n & 0xff000000) >> 24);
}

uint32
ntohl_mine(uint32 n)
{
  return htonl_mine(n);
}
#else
void hn_s_convert(const uint8* u8array,uint8* dest)
{
#if __BYTE_ORDER == __LITTLE_ENDIAN 
    dest[1]=u8array[0];
    dest[0]=u8array[1];
#else
    memmove(dest,u8array,2);
#endif
}


void hn_l_convert(const uint8* u8array,uint8 * dest)
{
#if __BYTE_ORDER == __LITTLE_ENDIAN 
    dest[3]=u8array[0];
    dest[2]=u8array[1];
    dest[1]=u8array[2];
    dest[0]=u8array[3];
#else
    memmove(dest,u8array,4);
#endif
}

#endif
#define LWIP_DEBUGF(debug,x) do { \
                                printf x;\
                             } while(0)
//void gen_dump(int flag, const char* message,const uint8* buf, uint32 size);
void ttt(void)
{
}
void gen_dump(int flag, const char* message,const uint8* buf, int32 size)
{
	int		n, m;
	static char linebuf[80];
	int lineoffset;

#if 0
       if(!DEBUGF_OUT_COND(flag)){//just for if not dump, speed its execute, for debug says may sprintf consume too many time
            return;
       }
#endif       
	LWIP_DEBUGF(flag,("%s %d bytes:\r\n",message,(int)size));
	for(n=0;n<size;n+=16)
	{
	        linebuf[0]='\0';
	        lineoffset=0;
		for(m=0;m<16;m++)
		{
			if( n+m < size )
//				LWIP_DEBUGF(flag,("%02x ", 0xff & (int) buf[n+m] ));
                            lineoffset+=sprintf(linebuf+lineoffset,"%02x ", 0xff & (int) buf[n+m] );
			else
//				LWIP_DEBUGF(flag,("   "));
                            lineoffset+=sprintf(linebuf+lineoffset,"   ");
		}
//		LWIP_DEBUGF(flag,("    "));
              lineoffset+=sprintf(linebuf+lineoffset,"    ");
		for(m=0;m<16;m++)
		{
			if( n+m >= size ) break;
//			LWIP_DEBUGF(flag,("%c", (buf[n+m] >= ' ' && buf[n+m] < 127) ? buf[n+m] : '.' ));
                     lineoffset+=sprintf(linebuf+lineoffset,"%c", (buf[n+m] >= ' ' && buf[n+m] < 127) ? buf[n+m] : '.' );
		}
		LWIP_DEBUGF(flag,("%s\r\n",linebuf));
	}
}
#if 1 //DM would use exception class, will define Str2Hex other place
void Str2Hex(unsigned int HexLen, unsigned char *StrBuf,unsigned char *HexBuf)
{
	unsigned char ch1,ch2,ch3;
	unsigned int i;


       ASSERT_MINE(strlen(StrBuf)==2*HexLen);
	
	for(i=0;i<HexLen;i++)
	{
		ch1=StrBuf[i*2];
		ch2=StrBuf[i*2+1];
		if(ch1>='0' && ch1<='9')
			ch3=(ch1-'0')*0x10;
		else if(ch1>='a' && ch1<='f')
			ch3=(ch1-'a'+0x0a)*0x10;
		else if(ch1>='A' && ch1<='F')
			ch3=(ch1-'A'+0x0a)*0x10;
		if(ch2>='0' && ch2<='9')
			ch3+=ch2-'0';
		else if(ch2>='a' && ch2<='f') 
			ch3+=ch2-'a'+0x0a;
		else if (ch2>='A' && ch2<='F')
			ch3+=ch2-'A'+0x0a;
		HexBuf[i]=ch3;
	}
}
#endif

