#include "event.h"
/*
typedef int (*II_FUNC_PEEK)(ITER_INTERFACE *pIntf,EVENT_INTERFACE *pEvent);
typedef void (*II_FUNC_NEXT)(ITER_INTERFACE *pIntf);
*/
void EI_display(EVENT_INTERFACE *pIntf)
{
    pIntf->ei_display(pIntf);
}