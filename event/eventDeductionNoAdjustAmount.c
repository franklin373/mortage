#include "event.h"
#include "includes.h"
#if 0
typedef struct{
    EVENT_INTERFACE_DECLARE
	long double m_ratio_llf;
}EVENT_CLASS_DEDUCTION_NO_ADJUST_AMOUNT;
#endif
static void event_class_deduction_no_adjust_display(EVENT_INTERFACE *pIntf)
{
    EVENT_CLASS_DEDUCTION_NO_ADJUST_AMOUNT *this_ptr;
	
    this_ptr=(EVENT_CLASS_DEDUCTION_NO_ADJUST_AMOUNT *)pIntf;
	printf("event_deduction_no_adjust:%d,%s\n",pIntf->mei_type,TM_to_asc_simple(pIntf->mei_time));
	printf("amount=%Lf,ratio=%Lf\n",this_ptr->m_deduction_amount,this_ptr->m_ratio_llf);
}
void event_class_deduction_no_adjust_init(EVENT_INTERFACE *pIntf,time64_t time,long double deduction_amount,long double ratio_llf)
{
    EVENT_CLASS_DEDUCTION_NO_ADJUST_AMOUNT *this_ptr;
	event_class_base_init_helper(pIntf, ME_DEDUCTION_NO_ADJUST_AMOUNT, time,event_class_deduction_no_adjust_display);

    this_ptr=(EVENT_CLASS_DEDUCTION_NO_ADJUST_AMOUNT *)pIntf;
	this_ptr->m_deduction_amount=deduction_amount;
	this_ptr->m_ratio_llf=ratio_llf;
}
