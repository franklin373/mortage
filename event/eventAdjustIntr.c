#include <stdio.h>
#include "event.h"
#include "includes.h"
#if 0
typedef struct{
    EVENT_INTERFACE_DECLARE
    long double m_intr;
}EVENT_CLASS_ADJUST_INTR;
#endif
static void event_class_adjust_intr_display(EVENT_INTERFACE *pIntf)
{
    EVENT_CLASS_ADJUST_INTR *this_ptr;
	
    this_ptr=(EVENT_CLASS_ADJUST_INTR *)pIntf;
	printf("event_adjust_intr:%d,%s\n",pIntf->mei_type,TM_to_asc_simple(pIntf->mei_time));
	printf("intr=%Lf\n",this_ptr->m_intr);
}
void event_class_adjust_intr_init(EVENT_INTERFACE *pIntf,time64_t time,long double intr)
{
    EVENT_CLASS_ADJUST_INTR *this_ptr;
	event_class_base_init_helper(pIntf, ME_ADJUST_INTR, time,event_class_adjust_intr_display);

    this_ptr=(EVENT_CLASS_ADJUST_INTR *)pIntf;
    this_ptr->m_intr=intr;
}

