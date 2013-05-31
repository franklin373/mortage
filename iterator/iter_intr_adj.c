#include <stdlib.h>
#include <string.h>
#include "iter.h"
#include "includes.h"

static int line2IntrEvent(char *line,EVENT_INTERFACE *pEvent)
{
	struct tm tm_A;
	time64_t time64A;
	long double intr;
	
	memset(&tm_A,'\0',sizeof(tm_A));
	tm_A.tm_year=getNum(line,4)-1900;
	tm_A.tm_mon=getNum(line+4,2)-1;
	tm_A.tm_mday=getNum(line+6,2);
	time64A=mktime64(&tm_A);
	sscanf(strstr(line,",")+1,"%Lf",&intr);
	event_class_adjust_intr_init(pEvent,time64A,intr);
	return 0;
}
static int iter_peek_intr_adj(ITER_INTERFACE *pIter,EVENT_INTERFACE *pEvent)
{
	struct tag_iter_file *pIterFile;
	char *pLine;

	pIterFile=(struct tag_iter_file *)pIter->pData;
	pLine=iter_peek_file(pIterFile);
	if(pLine==NULL){
		return -1;
	}
	line2IntrEvent(pLine,pEvent);
	return 0;
}
static void iter_next_intr_adj(ITER_INTERFACE *pIter)
{
	struct tag_iter_file *pIterFile;
	
	pIterFile=(struct tag_iter_file *)pIter->pData;
	iter_next_file(pIterFile);
}
ITER_INTERFACE *iter_init_intr_adj()
{
	ITER_INTERFACE *pIterResult;
	struct tag_iter_file *pIterFile;

	pIterResult=malloc(sizeof(ITER_INTERFACE));
	pIterFile=malloc(sizeof(struct tag_iter_file));
	ASSERT_MINE(0==iter_file_init(pIterFile,"list_intr_adj.txt"));
	pIterResult->pData=pIterFile;
	pIterResult->ici_peek=iter_peek_intr_adj;
	pIterResult->ici_next=iter_next_intr_adj;
	return pIterResult;
}
