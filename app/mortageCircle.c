#include "includes.h"
/*
int mortageStep(struct tagDebt *pDebt,EVENT_INTERFACE *pEvent)
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

int debt_init(struct tagDebt *pDebt)
{
	char event_buf[MAX_EVENT_INTF_ITEM_SIZE];
	EVENT_INTERFACE *pEvent=(EVENT_INTERFACE *)event_buf;
	long double intr;
	int nRtn;
	int nTerms;
	char szBuf[200];
	
    ASSERT_MINE(0==TCU_GetProfileString(CONF_FILENAME,"DEBT","TotalAmount",szBuf,sizeof szBuf,0));
    nRtn=sscanf(szBuf,"%Lf",&pDebt->balance);
    ASSERT_MINE(nRtn==1);
	pDebt->balancePayNone=pDebt->balance;
	pDebt->balancePayLlf=pDebt->balance;
	
    ASSERT_MINE(0==TCU_GetProfileString(CONF_FILENAME,"DEBT","DateBegin",szBuf,sizeof szBuf,0));
	ASSERT_MINE(0==TM_from_asc(&(pDebt->time),szBuf));

    ASSERT_MINE(0==TCU_GetProfileString(CONF_FILENAME,"DEBT","DeductionPerMonDay",szBuf,sizeof szBuf,0));
    nRtn=sscanf(szBuf,"%d",&pDebt->deductionPerMonDay);
    ASSERT_MINE(nRtn==1);

	//first should get intr, so need iter_intr, but iter_regu need use mon pay
	//so iter_init later.
	iter_init_1();
	for(intr=0;;){
		nRtn=IIF_peek(pIterArray[ITER_INTR_ADJ],pEvent);
		if(nRtn!=0){
			break;
		}
		if(pEvent->mei_time>pDebt->time){
			break;
		}else{
			EVENT_CLASS_ADJUST_INTR *this_ptr;

			this_ptr=(EVENT_CLASS_ADJUST_INTR *)pEvent;		
			intr=this_ptr->m_intr;
			IIF_next(pIterArray[ITER_INTR_ADJ]);
		}
	}
	if(intr==0){
		ASSERT_MINE(0);
	}
	INTR_init(&(pDebt->intr), intr);

    ASSERT_MINE(0==TCU_GetProfileString(CONF_FILENAME,"DEBT","DeductionTerms",szBuf,sizeof szBuf,0));
    nRtn=sscanf(szBuf,"%d",&nTerms);
    ASSERT_MINE(nRtn==1);
	pDebt->deductionPerMonAmount=GS_t2m(&(pDebt->intr),pDebt->balance,nTerms,diff_day(pDebt->deductionPerMonDay,pDebt->time));
	
	iter_init_2();
	return 0;
}
struct tagDebt global_debt;
int mortageCircle()
{
//	struct tagEventIter eventIter;

//	iter_init(&eventIter);
	debt_init(&global_debt);
	for(;global_debt.balance>0;){
		char event_buf[MAX_EVENT_INTF_ITEM_SIZE];
		EVENT_INTERFACE *pEvent=(EVENT_INTERFACE *)event_buf;

		ASSERT_MINE(0==iter_event(pEvent));
		mortageStep(&global_debt,pEvent);
	}
	return 0;
}
