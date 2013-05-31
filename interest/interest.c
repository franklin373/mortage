#include <stdio.h>
#include <math.h>
#include "interest/interest.h"

#if 0
struct tag_interest{
	long double day;
	long double month;
};
#endif
void INTR_init(struct tag_interest *pIntr,long double intr_year)
{
#if 0
	pIntr->month=pow(1+intr_year,1.0/12)-1;
	pIntr->day=pow(1+pIntr->month,1.0/30)-1;
#else
	pIntr->month=intr_year/12.0;
	pIntr->day=intr_year/360.0;
#endif
}
void INTR_disp(struct tag_interest *pIntr)
{
	printf("interest month=%Lf,q=%Lf\n",pIntr->month,1.0/(pIntr->month+1.0));
	printf("interest day=%Lf\n",pIntr->day);
}
long double INTR_pow_days(struct tag_interest *pIntr,long double amount,int days)
{
	int i;
	long double result=amount;

#if 0
	for(i=0;i<days;i++){
		result*=(1.0+pIntr->day);
	}
#else
	result=amount*(1.0+days*pIntr->day);
#endif
	return result;
}
#if 0
long double INTR_pow_month(struct tag_interest *pIntr,long double amount)
{
	long double result;

	result=amount*(1.0+pIntr->month);
	return result;
}
#endif
