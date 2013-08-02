#include "includes.h"

/*
struct tagDebt{
	long double balance;
	long double balancePayNone;
	long double balancePayLlf;
	time64_t time;
	long double deductionPerMonAmount;
	int deductionPerMonDay;
	struct tag_interest intr;
};
*/
/*
long double GS_t2m(struct tag_interest *pIntr,long double sum,int terms,int days_diff);
long double GS_m2t(struct tag_interest *pIntr,long double sum,long double ammount,int days_diff);
*/
int diff_day(int dayPerMon,time64_t begin)
{
	struct tm tm_A;
	
	gmtime64_r(&begin,&tm_A);
	return (dayPerMon-tm_A.tm_mday>0?dayPerMon-tm_A.tm_mday:dayPerMon-tm_A.tm_mday+30);
}
int roundTerms(long double ldTerms)
{
	int nTerms;

	nTerms=(int)(ldTerms+29.0/30);
	return nTerms;
}
int mortageStep(struct tagDebt *pDebt,EVENT_INTERFACE *pEvent)
{
	int days;
	long double prevBalance;
	
	days=TM_sub_day_adj(pEvent->mei_time,pDebt->time);
	if(days<0){
		time_t a,b;

		a=pEvent->mei_time;
		b=pDebt->time;
		printf(FL("%d,<0x%llx,0x%llx>,%s,%s\n"),pEvent->mei_type,pEvent->mei_time,pDebt->time,TM_to_asc_simple(pEvent->mei_time),TM_to_asc_simple(pDebt->time));
	}
	ASSERT_MINE(days>=0);
	pDebt->balance=INTR_pow_days(&(pDebt->intr),pDebt->balance,days);
	pDebt->balancePayNone=INTR_pow_days(&(pDebt->intr),pDebt->balancePayNone,days);
	pDebt->balancePayLlf=INTR_pow_days(&(pDebt->intr),pDebt->balancePayLlf,days);
	pDebt->time=pEvent->mei_time;
	printf("%s,%Lf,",TM_to_asc_simple(pEvent->mei_time),pDebt->balance);
	prevBalance=pDebt->balance;
	switch(pEvent->mei_type){
	case ME_DEDUCTION_NO_ADJUST_AMOUNT:
		{
			EVENT_CLASS_DEDUCTION_NO_ADJUST_AMOUNT *this_ptr;
			long double this_time_pay;

			this_ptr=(EVENT_CLASS_DEDUCTION_NO_ADJUST_AMOUNT *)pEvent;
			this_time_pay=MIN(pDebt->balance,this_ptr->m_deduction_amount);
			pDebt->balance-=this_time_pay;
			pDebt->balancePayLlf-=this_time_pay*this_ptr->m_ratio_llf;
		}
		break;
	case ME_DEDUCTION_ADJUST_AMOUNT:
		{
			EVENT_CLASS_DEDUCTION_ADJUST_AMOUNT *this_ptr;
			long double ldTerms;
			int nTerms;
			long double this_time_pay;

			/******************compute to Term******************************/
			ldTerms=GS_m2t(&(pDebt->intr),pDebt->balance,pDebt->deductionPerMonAmount,diff_day(pDebt->deductionPerMonDay,pEvent->mei_time));
			nTerms=roundTerms(ldTerms);
			/******************process**************************************/
			this_ptr=(EVENT_CLASS_DEDUCTION_ADJUST_AMOUNT *)pEvent;
			this_time_pay=MIN(pDebt->balance,this_ptr->m_deduction_amount);
			pDebt->balance-=this_time_pay;
			pDebt->balancePayLlf-=this_time_pay*this_ptr->m_ratio_llf;
			/******************adjust ammount ******************************/
			pDebt->deductionPerMonAmount=GS_t2m(&(pDebt->intr),pDebt->balance,nTerms,diff_day(pDebt->deductionPerMonDay,pEvent->mei_time));
		}
		break;
	case ME_ADJUST_INTR:
		{
			EVENT_CLASS_ADJUST_INTR *this_ptr;
			long double ldTerms;
			int nTerms;

			/******************compute to Term******************************/
			ldTerms=GS_m2t(&(pDebt->intr),pDebt->balance,pDebt->deductionPerMonAmount,diff_day(pDebt->deductionPerMonDay,pEvent->mei_time));
			nTerms=roundTerms(ldTerms);
			/******************process**************************************/
			this_ptr=(EVENT_CLASS_ADJUST_INTR *)pEvent;
			INTR_init(&(pDebt->intr),this_ptr->m_intr);
			/******************adjust ammount ******************************/
			pDebt->deductionPerMonAmount=GS_t2m(&(pDebt->intr),pDebt->balance,nTerms,diff_day(pDebt->deductionPerMonDay,pEvent->mei_time));
		}
		break;
	default:
		ASSERT_MINE(0);
		break;
	}
	printf("%Lf,%Lf\n",pDebt->balance,prevBalance-pDebt->balance);
	return 0;
}
