#include <stdlib.h>
#include <string.h>
#include "iter.h"
#include "includes.h"

static int line2DeductionNoAdjOrAdjEvent(char *line,EVENT_INTERFACE *pEvent)
{
	struct tm tm_A;
	time64_t time64A;
	long double amount,ratio;
	
	memset(&tm_A,'\0',sizeof(tm_A));
	tm_A.tm_year=getNum(line,4)-1900;
	tm_A.tm_mon=getNum(line+4,2)-1;
	tm_A.tm_mday=getNum(line+6,2);
	time64A=mktime64(&tm_A);
	sscanf(line+12,"%Lf,%Lf",&amount,&ratio);
	if(0==memcmp(line+8,",FM,",4)){
		event_class_deduction_no_adjust_init(pEvent,time64A,amount,ratio);
	}else if(0==memcmp(line+8,",FT,",4)){
		event_class_deduction_adjust_init(pEvent,time64A,amount,ratio);
	}else{
		ASSERT_MINE(0);
	}
	return 0;
}
static int iter_peek_deduction_ahead(ITER_INTERFACE *pIter,EVENT_INTERFACE *pEvent)
{
	struct tag_iter_file *pIterFile;
	char *pLine;

	pIterFile=(struct tag_iter_file *)pIter->pData;
	pLine=iter_peek_file(pIterFile);
	if(pLine==NULL){
		return -1;
	}
	line2DeductionNoAdjOrAdjEvent(pLine,pEvent);
	return 0;
}
static void iter_next_deduction_ahead(ITER_INTERFACE *pIter)
{
	struct tag_iter_file *pIterFile;
	
	pIterFile=(struct tag_iter_file *)pIter->pData;
	iter_next_file(pIterFile);
}
ITER_INTERFACE *iter_init_deduction_ahead()
{
	ITER_INTERFACE *pIterResult;
	struct tag_iter_file *pIterFile;

	pIterResult=malloc(sizeof(ITER_INTERFACE));
	pIterFile=malloc(sizeof(struct tag_iter_file));
	ASSERT_MINE(0==iter_file_init(pIterFile,"list_deduction_ahead.txt"));
	pIterResult->pData=pIterFile;
	pIterResult->ici_peek=iter_peek_deduction_ahead;
	pIterResult->ici_next=iter_next_deduction_ahead;
	return pIterResult;
}

