#include <stdio.h>
#include "global.h"
#include "time_pivotal/pivotal_gmtime_r.h"
#include <string.h>
#include "time/tm_morgage.h"

void TM_to_asc(time64_t tm,char *asc)
{
	struct tm tm_A;

	gmtime64_r(&tm,&tm_A);
	sprintf(asc,"%04d%02d%02d",1900+tm_A.tm_year,1+tm_A.tm_mon,tm_A.tm_mday);
}
char * TM_to_asc_simple(time64_t tm)
{
	static char buf[500];
	static int i=0;

	if(i==10){
		i=0;
	}else{
		i++;
	}
	TM_to_asc(tm,buf+20*i);
	return buf+20*i;
}
#if 0
struct tm {
    int tm_sec;         /* seconds */
    int tm_min;         /* minutes */
    int tm_hour;        /* hours */
    int tm_mday;        /* day of the month */
    int tm_mon;         /* month */
    int tm_year;        /* year */
    int tm_wday;        /* day of the week */
    int tm_yday;        /* day in the year */
    int tm_isdst;       /* daylight saving time */
};
#endif
void dispTm4Dbg(struct tm *pTM)
{
	printf("<sec,min,hour>=<%d,%d,%d>\n",pTM->tm_sec,pTM->tm_min,pTM->tm_hour);
	printf("<mday,mon,year>=<%d,%d,%d>\n",pTM->tm_mday,pTM->tm_mon,pTM->tm_year);
	printf("<wday,yday,isdst>=<%d,%d,%d>\n",pTM->tm_wday,pTM->tm_yday,pTM->tm_isdst);
}
int getNum(char *num_buf,int len)
{
	int result;
	int i;

	result=0;
	for(i=0;i<len;i++){
		if('0'<=num_buf[i]&&num_buf[i]<='9'){
			result=10*result+num_buf[i]-'0';
		}else{
			return -1;
		}
	}
	return result;
}
int TM_from_asc(time64_t *p_tm,char *asc)
{
	time64_t result;
	struct tm tm_A;
#if 0
	char *ptr;
	ptr=strptime(asc, "%Y-%m-%d", &tm_A);
	if(ptr!=NULL&&*ptr=='\0'){
	}else{
		return -1;
	}
{
#if 0
static char tmp_buf[100];
asciitime_r(&tm_A,tmp_buf);
#endif
printf("just test %04d-%02d-%02d\n",1900+tm_A.tm_year,1+tm_A.tm_mon,tm_A.tm_mday);
}
dispTm4Dbg(&tm_A);
#else
#if 0
	result=time(NULL);
	localtime64_r(&result,&tm_A);
dispTm4Dbg(&tm_A);
#else	
	memset(&tm_A,'\0',sizeof(tm_A));
#endif
	tm_A.tm_year=getNum(asc,4)-1900;
	tm_A.tm_mon=getNum(asc+4,2)-1;
	tm_A.tm_mday=getNum(asc+6,2);
//dispTm4Dbg(&tm_A);
#endif
	result=mktime64(&tm_A);
//printf("result=0x%x\n",result);
	*p_tm=result;
	return 0;
}
