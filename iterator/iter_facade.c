#include "iter.h"
/*
typedef int (*II_FUNC_PEEK)(ITER_INTERFACE *pIntf,EVENT_INTERFACE *pEvent);
typedef void (*II_FUNC_NEXT)(ITER_INTERFACE *pIntf);
*/
int IIF_peek(ITER_INTERFACE *pIntf,EVENT_INTERFACE *pEvent)
{
    return pIntf->ici_peek(pIntf,pEvent);
}
void IIF_next(ITER_INTERFACE *pIntf)
{
    pIntf->ici_next(pIntf);
}

