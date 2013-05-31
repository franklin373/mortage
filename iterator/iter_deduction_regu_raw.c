#include <stdlib.h>
#include <string.h>
#include "iter.h"
#include "includes.h"

static int line2DeductionNoAdjEvent(char *line,EVENT_INTERFACE *pEvent)
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
static int iter_peek_deduction_regu_raw(ITER_INTERFACE *pIter,EVENT_INTERFACE *pEvent)
{
	struct tag_iter_file *pIterFile;
	char *pLine;

	pIterFile=(struct tag_iter_file *)pIter->pData;
	pLine=iter_peek_file(pIterFile);
	if(pLine==NULL){
		return -1;
	}
	line2DeductionNoAdjEvent(pLine,pEvent);
	return 0;
}
static void iter_next_deduction_reg_raw(ITER_INTERFACE *pIter)
{
	struct tag_iter_file *pIterFile;
	
	pIterFile=(struct tag_iter_file *)pIter->pData;
	iter_next_file(pIterFile);
}
ITER_INTERFACE *iter_init_deduction_reg_raw()
{
	ITER_INTERFACE *pIterResult;
	struct tag_iter_file *pIterFile;

	pIterResult=malloc(sizeof(ITER_INTERFACE));
	pIterFile=malloc(sizeof(struct tag_iter_file));
	ASSERT_MINE(0==iter_file_init(pIterFile,"list_deduction_regu.txt"));
	pIterResult->pData=pIterFile;
	pIterResult->ici_peek=iter_peek_deduction_regu_raw;
	pIterResult->ici_next=iter_next_deduction_reg_raw;
	return pIterResult;
}

