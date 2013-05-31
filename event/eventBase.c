#include "event.h"

void event_class_base_init_helper(EVENT_INTERFACE *pIntf,const char mei_type,time64_t time,EI_FUNC_DISPLAY func_display)
{
    pIntf->mei_type=mei_type;
	pIntf->mei_time=time;
	pIntf->ei_display=func_display;
}
