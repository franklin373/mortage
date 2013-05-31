#ifndef __TM_MORGAGE_H__
#define __TM_MORGAGE_H__

void TM_to_asc(time64_t tm,char *asc);
char * TM_to_asc_simple(time64_t tm);
int TM_from_asc(time64_t *p_tm,char *asc);
int TM_sub_day_adj(time64_t tA,time64_t tB);
time64_t nextMonth(time64_t tA);

#endif
