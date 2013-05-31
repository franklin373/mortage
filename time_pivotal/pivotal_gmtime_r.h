#ifndef __PIVOTAL_GMTIME_R_H__
#define __PIVOTAL_GMTIME_R_H__

#include <time.h>

typedef long long time64_t;

time64_t pivot_time_t (const time_t * now, time64_t * _t);
struct tm *gmtime64_r (const time64_t * _t, struct tm *p);
struct tm *pivotal_gmtime_r (const time_t * now, const time_t * _t, struct tm *p);
time64_t mktime64 (struct tm * t);
struct tm *pivotal_localtime_r (const time_t * now, const time_t * _t, struct tm *p);
struct tm *localtime64_r (const time64_t * _t, struct tm *p);
time64_t currentTime64(void);/******add by llf********************/

#endif
