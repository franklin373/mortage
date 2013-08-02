#include <stdio.h>
#include "includes.h"

/*
long double INTR_pow_days(struct tag_interest *pIntr,long double amount,int days);
long double INTR_pow_month(struct tag_interest *pIntr,long double amount);
long double GS_t2m(struct tag_interest *pIntr,long double sum,int terms,int days_diff);
long double GS_m2t(struct tag_interest *pIntr,long double sum,long double ammount,int days_diff);
void TM_to_asc(time64_t tm,char *asc);
int TM_from_asc(time64_t *p_tm,char *asc);
int TM_sub_day_adj(time64_t tA,time64_t tB);
*/
void caseMortageCircle()
{
	mortageCircle();
}
void caseTestCompSum(long double ammount,int terms)
{
	struct tag_interest intr;
	long double intr_year;
	long double sum;

	intr_year=/*0.055675*/0.0655/**0.85*/;
	INTR_init(&intr,intr_year);
	printf("intr_year=%Lf,sizeof(time64_t)=%d\n",intr_year,sizeof(time64_t));
	INTR_disp(&intr);
	printf("ammount=%Lf,term=%d\n",ammount,terms);
	sum=GS_mt2s(&intr,ammount,terms,30);
	printf("<sum>=<%Lf>\n",sum);
}
void caseTest()
{
	struct tag_interest intr;
	long double result_day_10,result_day_30;
	long double ammount,terms;
	long double intr_year;

	intr_year=/*0.051*/0.0655*0.85;
	INTR_init(&intr,intr_year);
	printf("intr_year=%Lf,sizeof(time64_t)=%d\n",intr_year,sizeof(time64_t));
	INTR_disp(&intr);
	result_day_10=INTR_pow_days(&intr,1000000.0,10);
	result_day_30=INTR_pow_days(&intr,1000000.0,30);
//	result_mon_1=INTR_pow_month(&intr,1000000.0);
	printf("<day_10,day_30>=<%Lf,%Lf>\n",result_day_10,result_day_30);
	ammount=GS_t2m(&intr,1000000.0,12*20,30);
	terms=GS_m2t(&intr,1000000.0,ammount,30);
	printf("<ammount,terms>=<%Lf,%Lf>\n",ammount,terms);
	{//test time
		time64_t tm_A,tm_B;
		char ascii_time[100];
		int result;

		tm_A=currentTime64();
		TM_to_asc(tm_A,ascii_time);
		result=TM_from_asc(&tm_B,ascii_time);
		printf("<tmA,tmB,ascii_time,result>=<%d,%d,%s,%d>\n",(int)tm_A,(int)tm_B,ascii_time,result);
	}
	{
		time64_t tm_A,tm_B;
		int result;

		TM_from_asc(&tm_A,"20120528");
		TM_from_asc(&tm_B,"20130528");
		result=TM_sub_day_adj(tm_A,tm_B);
		printf("result=%d\n",result);
	}
	{
		time64_t t64A,t64B,t64C;
		
		printf("begin test time...\n");
		TM_from_asc(&t64A,"20130803");
		TM_from_asc(&t64B,"20130903");
		t64C=nextMonth(t64A);
		printf("%lld,%lld,%lld,%lld,%lld,%lld\n",t64A/86400,t64B/86400,t64C/86400,t64A,t64B,t64C);
	}
}
int initSerialPort(HANDLE *pHandle)
{
//	char filename[100];
	HANDLE fd;
	int nRtn;
//	int baud_rate;
       char szPortNo[10];
       char szBaudRate[10];
       int port_no;
       int baud_rate;


	
       ASSERT_MINE(0==TCU_GetProfileString(CONF_FILENAME,"COMMU","PortNo",szPortNo,sizeof szPortNo,0));
       ASSERT_MINE(1==sscanf(szPortNo,"%d",&port_no));
       ASSERT_MINE(0==TCU_GetProfileString(CONF_FILENAME,"COMMU","BaudRate",szBaudRate,sizeof szBaudRate,0));
       ASSERT_MINE(1==sscanf(szBaudRate,"%d",&baud_rate));
	nRtn=Com_Port_Connect_By_Port_No(port_no,getBaudrate(baud_rate),&fd);
	if(nRtn!=0){
	    fprintf(stderr,"error, after Com_Port_Connect, return %d\n",nRtn);
	    return -9;
	}
	fprintf(stdout,"serial port handle=%x\n",(int)fd);
	*pHandle=fd;
	return 0;
}
void usage(char *cmd)
{
    fprintf(stderr,"usage:\n");
    fprintf(stderr,"          %s circle\n",cmd);
    fprintf(stderr,"          %s testCompSum amount term\n",cmd);
    fprintf(stderr,"          %s test\n",cmd);
    exit(-1);
}
void initGlobalContext()
{

}
int main(int argc,char *argv[])
{
//    HANDLE fd1;
    int nRtn;

    if(argc<2){
        usage(argv[0]);
    }
    initGlobalContext();
#if 0	
    nRtn=initSerialPort(&fd1);
    ASSERT_MINE(nRtn==0);
#endif
    if(strcmp(argv[1],"circle")==0){
        caseMortageCircle();
    }else if(strcmp(argv[1],"testCompSum")==0){
    	long double ammout;
		int term;
		
    	if(argc!=4){
			usage(argv[0]);
    	}
		nRtn=sscanf(argv[2],"%Lf",&ammout);
		if(nRtn!=1){
			usage(argv[0]);
		}
		nRtn=sscanf(argv[3],"%d",&term);
		if(nRtn!=1){
			usage(argv[0]);
		}
    	caseTestCompSum(ammout,term);
    }else if(strcmp(argv[1],"test")==0){
    	caseTest();
//        case1();
//        case2();
//        case3();
    }else{
        usage(argv[0]);
    }


    return 0;
}
