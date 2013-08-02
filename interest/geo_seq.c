#include "includes.h"
#if 0
long double GS_t2m(struct tag_interest *pIntr,long double sum,int terms)
{
	long double q;
	long double amount;

	q=1.0/(1.0+pIntr->month);
	amount=(1-q)/(q*(1.0-pow(q,terms)));
	amount*=sum;
	return amount;
}
long double GS_m2t(struct tag_interest *pIntr,long double sum,long double ammount)
{
	long double q;
	long double q_pow_n;
	long double terms;

	q=1.0/(1.0+pIntr->month);
	q_pow_n=1-(sum/q*(1.0-q)/ammount);
	terms=log(q_pow_n)/log(q);
	return terms;
}
#else
long double GS_t2m(struct tag_interest *pIntr,long double sum,int terms,int days_diff)
{
	long double q;
	long double amount;
	long double sum_compute;

	sum_compute=sum*(1.0+pIntr->month*days_diff/30.0);

	q=1.0/(1.0+pIntr->month);
	amount=(1-q)/(1.0-pow(q,terms));
	amount*=sum_compute;
	return amount;
}
long double GS_m2t(struct tag_interest *pIntr,long double sum,long double ammount,int days_diff)
{
	long double q;
	long double q_pow_n;
	long double terms;
	long double sum_compute;

	sum_compute=sum*(1.0+pIntr->month*days_diff/30.0);

	q=1.0/(1.0+pIntr->month);
	q_pow_n=1-(sum_compute*(1.0-q)/ammount);
	terms=log(q_pow_n)/log(q);
	return terms;
}
long double GS_mt2s(struct tag_interest *pIntr,long double ammount,int terms,int days_diff)
{
	long double q;
	long double q_pow_n;
	long double sum_computer;
	long double sum;

//printf("pIntr->month=%Lf\n",pIntr->month);
	q=1.0/(1.0+pIntr->month);
//printf("q=%Lf\n",q);
	q_pow_n=pow(q,terms);
//printf("q_pow_n=%Lf\n",q_pow_n);
	sum_computer=ammount*(1.0-q_pow_n)/(1.0-q);
//printf("sum_computer=%Lf\n",sum_computer);
	sum=sum_computer/(1.0+pIntr->month*days_diff/30.0);
	return sum;
}
#endif
