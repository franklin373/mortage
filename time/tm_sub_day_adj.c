#include "time_pivotal/pivotal_gmtime_r.h"
#include "time/tm_morgage.h"

int TM_sub_day_adj(time64_t tA,time64_t tB)
{
	struct tm tm_A,tm_B;
	int diff_y,diff_m,diff_d;

	gmtime64_r(&tA,&tm_A);
	gmtime64_r(&tB,&tm_B);

	diff_y=tm_A.tm_year-tm_B.tm_year;
	diff_m=tm_A.tm_mon-tm_B.tm_mon;
	diff_d=tm_A.tm_mday-tm_B.tm_mday;
	return (diff_y*12+diff_m)*30+diff_d;
}
time64_t nextMonth(time64_t tA)
{
	struct tm tm_A;

	gmtime64_r(&tA,&tm_A);//cannot use localtime64_r, or diff 8 hours
	if(tm_A.tm_mon==11){
		tm_A.tm_year++;
		tm_A.tm_mon=0;
	}else{
		tm_A.tm_mon++;
	}
	return mktime64(&tm_A);
}
