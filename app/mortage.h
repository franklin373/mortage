#ifndef __MORTAGE_H__
#define __MORTAGE_H__

struct tagDebt{
	long double balance;
	long double balancePayNone;
	long double balancePayLlf;
	time64_t time;
	long double deductionPerMonAmount;
	int deductionPerMonDay;
	struct tag_interest intr;
};
int mortageStep(struct tagDebt *pDebt,EVENT_INTERFACE *pEvent);
int diff_day(int dayPerMon,time64_t begin);
int mortageCircle(void);
extern struct tagDebt global_debt;
void debt_display(struct tagDebt *pDebt);

#endif
