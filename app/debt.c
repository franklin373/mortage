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
void debt_display(struct tagDebt *pDebt)
{
	printf("<balance,balancePayNone,balancePayLlf>,<%Lf,%Lf,%Lf>\n",pDebt->balance,pDebt->balancePayNone,pDebt->balancePayLlf);
	printf("<time,MonAmount,PerMonDay>,<%s,%Lf,%d>\n",TM_to_asc_simple(pDebt->time),pDebt->deductionPerMonAmount,pDebt->deductionPerMonDay);
	INTR_disp(&(pDebt->intr));
}
