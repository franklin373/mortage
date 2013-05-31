#include <string.h>
#include "iter.h"
#include "includes.h"


//#define MAX_EVENT_INTF_ITEM_SIZE (sizeof(EVENT_INTERFACE)+32)

/*
struct tagEventIter{
	time64_t time;
	int seq;
};
*/
/*deduction_reg,deduction_ahead,intr_adj*/
#if 0
void iter_init(struct tagEventIter *pIter)
{
	int i;
	
	pIter->time=0;
	pIter->seq=0;
	for(i=0;i<3;i++){
		pEventArray[i]=(EVENT_INTERFACE *)(event_array_buf+i*MAX_EVENT_INTF_ITEM_SIZE);
	}
}
int iter_event(struct tagEventIter *pIter,EVENT_INTERFACE *pEvent)
{
	time64_t min_time;
	int equal_continue_cnt;
	int i;

	iter_deduction_reg_next(pIter->time,pEventArray[0]);
	iter_deduction_ahead_next(pIter->time,pEventArray[1]);
	iter_intr_adj_next(pIter->time,pEventArray[3]);

	min_time=(time64_t)-1;
	for(i=0;i<3;i++){
		if(min_time>pEventArray[i]->mei_time){
			min_time=pEventArray[i]->mei_time;
		}
	}

	equal_continue_cnt=0;
	for(i=0;i<3;i++){
		if(min_time==pEventArray[i]->mei_time){
			if(pIter->time==min_time){
				if(equal_continue_cnt<pIter->seq){
					++equal_continue_cnt;
					continue;
				}else{
					++pIter->seq;
					memcpy(pEvent,pEventArray[i],MAX_EVENT_INTF_ITEM_SIZE);
					return 0;
				}
			}else{
				pIter->time=min_time;
				pIter->seq=0;
				memcpy(pEvent,pEventArray[i],MAX_EVENT_INTF_ITEM_SIZE);
				return 0;
			}
		}
	}
	return -1;
}
int iter_peek_deduction_regu(EVENT_INTERFACE *pEvent);
void iter_next_deduction_regu(void);
int iter_peek_deduction_ahead(EVENT_INTERFACE *pEvent);
void iter_next_deduction_ahead(void);
int iter_peek_intr_adj(EVENT_INTERFACE *pEvent);
void iter_next_intr_adj(void);
#else
ITER_INTERFACE *pIterArray[3];
char event_array_buf[3*MAX_EVENT_INTF_ITEM_SIZE];
EVENT_INTERFACE *pEventArray[3];
int peekResult[3];
void iter_init_1()
{
	int i;

	for(i=0;i<3;i++){
		pEventArray[i]=(EVENT_INTERFACE *)(event_array_buf+i*MAX_EVENT_INTF_ITEM_SIZE);
	}
	pIterArray[ITER_INTR_ADJ]=iter_init_intr_adj();
}
void iter_init_2()
{
	pIterArray[ITER_DEDUCTION_REGU]=iter_init_deduction_reg();
	pIterArray[ITER_DEDUCTION_AHEAD]=iter_init_deduction_ahead();
}
int iter_event(EVENT_INTERFACE *pEvent)
{
	time64_t min_time;
	int i;
	int nRtn;

	for(i=0;i<3;i++){
		nRtn=IIF_peek(pIterArray[i],pEventArray[i]);
		peekResult[i]=nRtn;
	}
	
	min_time=~(((unsigned long long)1)<<63);//not unsigned
	for(i=0;i<3;i++){
		if(peekResult[i]){
			continue;
		}
		if(min_time>pEventArray[i]->mei_time){
			min_time=pEventArray[i]->mei_time;
		}
	}

	for(i=0;i<3;i++){
		if(peekResult[i]){
			continue;
		}
		if(min_time==pEventArray[i]->mei_time){
			IIF_next(pIterArray[i]);
			memcpy(pEvent,pEventArray[i],MAX_EVENT_INTF_ITEM_SIZE);
			return 0;
		}
	}
	/***************error happened******************************************/
	for(i=0;i<3;i++){
		if(peekResult[i]==0){
			printf("i=%d\n",i);
			EI_display(pEventArray[i]);
		}
		printf("peekResult[%d]=%d\n",i,peekResult[i]);
	}
	debt_display(&global_debt);
#if 0	
	printf("min_time=0x%Lx,%s\n",min_time,TM_to_asc_simple(min_time));
#else
	printf("min_time=0x%llx\n",min_time);
#endif
	return -1;
}
#endif
