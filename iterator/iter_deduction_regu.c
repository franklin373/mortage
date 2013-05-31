#include "iter.h"
#include "includes.h"


#if 0
int iter_peek_deduction_regu(EVENT_INTERFACE *pEvent)
{
	return 0;
}
void iter_next_deduction_regu()
{
}
static int line2DeductionRegEvent(char *line,EVENT_INTERFACE *pEvent)
{
	struct tm tm_A;
	time64_t time64A;
	long double ratio;
	
	memset(&tm_A,'\0',sizeof(tm_A));
	tm_A.tm_year=getNum(line,4)-1900;
	tm_A.tm_mon=getNum(line+4,2)-1;
	tm_A.tm_mday=global_debt.deductionPerMonDay;
	time64A=mktime64(&tm_A);
	sscanf(strstr(line,",")+1,"%Lf",&ratio);
	event_class_deduction_no_adjust_init(pEvent,time64A,global_debt.deductionPerMonAmount,ratio);
	return 0;
}
#else
static char event_buf_inner[MAX_EVENT_INTF_ITEM_SIZE];
static EVENT_INTERFACE *pEventBuffer=(EVENT_INTERFACE *)event_buf_inner;
static int iter_peek_deduction_regu(ITER_INTERFACE *pIter,EVENT_INTERFACE *pEvent)
{
	memcpy(pEvent,pEventBuffer,MAX_EVENT_INTF_ITEM_SIZE);
	return 0;
}
static void iter_next_deduction_reg(ITER_INTERFACE *pIter)
{
	char event_buf_inner_stack[MAX_EVENT_INTF_ITEM_SIZE];
	EVENT_INTERFACE *pEventBufferStack=(EVENT_INTERFACE *)event_buf_inner_stack;
	ITER_INTERFACE *pIterRaw=pIter->pData;
	time64_t nextMon;
	int nRtn;

	nextMon=nextMonth(pEventBuffer->mei_time);
	nRtn=IIF_peek(pIterRaw,pEventBufferStack);
	if(nRtn!=0||nextMon<pEventBufferStack->mei_time){
		pEventBuffer->mei_time=nextMon;
	}else{
		memcpy(pEventBuffer,pEventBufferStack,MAX_EVENT_INTF_ITEM_SIZE);
		IIF_next(pIterRaw);
	}
}
ITER_INTERFACE *iter_init_deduction_reg()
{
	ITER_INTERFACE *pIterResult;
	ITER_INTERFACE *pIterRaw;

	pIterResult=malloc(sizeof(ITER_INTERFACE));
	pIterRaw=iter_init_deduction_reg_raw();
	pIterResult->pData=pIterRaw;
	pIterResult->ici_peek=iter_peek_deduction_regu;
	pIterResult->ici_next=iter_next_deduction_reg;
	IIF_peek(pIterRaw,pEventBuffer);
	IIF_next(pIterRaw);
	return pIterResult;
}
#endif
