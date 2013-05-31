#ifndef __EVENT_H__
#define __EVENT_H__
#include "time_pivotal/pivotal_gmtime_r.h"

#define ME_ADJUST_INTR (1)
#define ME_DEDUCTION_ADJUST_AMOUNT (2)
#define ME_DEDUCTION_NO_ADJUST_AMOUNT (3)

struct tag_event_interface;
typedef struct tag_event_interface EVENT_INTERFACE;
typedef void (*EI_FUNC_DISPLAY)(EVENT_INTERFACE *pIntf);
#define EVENT_INTERFACE_DECLARE                           \
    char  mei_type;                                      \
    EI_FUNC_DISPLAY ei_display;							\
    time64_t mei_time;
struct tag_event_interface{
    EVENT_INTERFACE_DECLARE
};
void event_class_base_init_helper(EVENT_INTERFACE *pIntf,const char mei_type,time64_t time,EI_FUNC_DISPLAY func_display);

typedef struct{
    EVENT_INTERFACE_DECLARE
    long double m_intr;
}EVENT_CLASS_ADJUST_INTR;
typedef struct{
    EVENT_INTERFACE_DECLARE
    long double m_deduction_amount;
	long double m_ratio_llf;
}EVENT_CLASS_DEDUCTION_ADJUST_AMOUNT;
typedef struct{
    EVENT_INTERFACE_DECLARE
    long double m_deduction_amount;
	long double m_ratio_llf;
}EVENT_CLASS_DEDUCTION_NO_ADJUST_AMOUNT;
#define MAX_EVENT_INTF_ITEM_SIZE (sizeof(EVENT_INTERFACE)+32)


void event_class_adjust_intr_init(EVENT_INTERFACE *pIntf,time64_t time,long double intr);
void event_class_deduction_adjust_init(EVENT_INTERFACE *pIntf,time64_t time,long double deduction_amount,long double ratio_llf);
void event_class_deduction_no_adjust_init(EVENT_INTERFACE *pIntf,time64_t time,long double deduction_amount,long double ratio_llf);
void EI_display(EVENT_INTERFACE *pIntf);


#endif

