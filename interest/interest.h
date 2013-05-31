#ifndef __INTEREST_H__
#define __INTEREST_H__

struct tag_interest{
	long double day;
	long double month;
};
void INTR_init(struct tag_interest *pIntr,long double intr_year);
void INTR_disp(struct tag_interest *pIntr);
long double INTR_pow_days(struct tag_interest *pIntr,long double amount,int days);
long double INTR_pow_month(struct tag_interest *pIntr,long double amount);
long double GS_t2m(struct tag_interest *pIntr,long double sum,int terms,int days_diff);
long double GS_m2t(struct tag_interest *pIntr,long double sum,long double ammount,int days_diff);

#endif
