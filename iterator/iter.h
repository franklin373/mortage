#ifndef __ITER_H__
#define __ITER_H__
#include <stdio.h>
#include "event/event.h"


#define ITER_DEDUCTION_REGU (0)
#define ITER_DEDUCTION_AHEAD (1)
#define ITER_INTR_ADJ (2)



struct tag_iter_interface;
typedef struct tag_iter_interface ITER_INTERFACE;
typedef int (*II_FUNC_PEEK)(ITER_INTERFACE *pIntf,EVENT_INTERFACE *pEvent);
typedef void (*II_FUNC_NEXT)(ITER_INTERFACE *pIntf);
#define ITER_INTERFACE_DECLARE                          \
/*    int ici_type;   */                                 	\
    II_FUNC_PEEK ici_peek;                       		\
    II_FUNC_NEXT ici_next;                       		\
    void *pData;
struct tag_iter_interface{
    ITER_INTERFACE_DECLARE
};

struct tag_iter_file{
	FILE *fp;
	char line[500];
	int isEnd;
};


#if 0
struct tagEventIter{
	time64_t time;
	int seq;
};
int iter_deduction_ahead_next(time64_t time,EVENT_INTERFACE *pEvent);
int iter_deduction_reg_next(time64_t time,EVENT_INTERFACE *pEvent);
int iter_intr_adj_next(time64_t time,EVENT_INTERFACE *pEvent);
void iter_init(struct tagEventIter *pIter);
int iter_event(struct tagEventIter *pIter,EVENT_INTERFACE *pEvent);
#elif 0
int iter_peek_deduction_ahead(EVENT_INTERFACE *pEvent);
void iter_next_deduction_ahead(void);
int iter_peek_deduction_regu(EVENT_INTERFACE *pEvent);
void iter_next_deduction_regu(void);
int iter_peek_intr_adj(EVENT_INTERFACE *pEvent);
void iter_next_intr_adj(void);
int iter_event(EVENT_INTERFACE *pEvent);
#else
int iter_file_init(struct tag_iter_file *pIter,const char *file_name);
char *iter_peek_file(struct tag_iter_file *pIter);
void iter_next_file(struct tag_iter_file *pIter);
int IIF_peek(ITER_INTERFACE *pIntf,EVENT_INTERFACE *pEvent);
void IIF_next(ITER_INTERFACE *pIntf);
ITER_INTERFACE *iter_init_deduction_reg_raw(void);
ITER_INTERFACE *iter_init_intr_adj(void);
ITER_INTERFACE *iter_init_deduction_reg(void);
ITER_INTERFACE *iter_init_deduction_ahead();
void iter_init_1(void);
void iter_init_2(void);
int iter_event(EVENT_INTERFACE *pEvent);
#endif
extern ITER_INTERFACE *pIterArray[];


#endif
