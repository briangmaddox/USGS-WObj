#include <Xm/Xm.h>
#include <X11/Shell.h>
#include <X11/Xmu/Editres.h>
#include "WObj/PopupWObj.h"

PopupWObj::PopupWObj(char* name, Widget parent) : WObj(name, parent)
{
   _isPoppedUp = false;

   _baseWidget = XtVaCreatePopupShell(name, vendorShellWidgetClass, parent, NULL);
   installDestroyHandler();

   XtVaSetValues(_baseWidget,
                 XmNdeleteResponse,    XmDO_NOTHING,
                 NULL);

//   XtAddEventHandler(_baseWidget, (EventMask) 0, True, 
//                    _XEditResCheckMessages,NULL);
}

void PopupWObj::popUp(void)
{
   _isPoppedUp = true;
   XtPopup(_baseWidget,XtGrabNone);
}

void PopupWObj::popDown(void)
{
   _isPoppedUp = false;
   XtPopdown(_baseWidget);
}

bool
PopupWObj::isPoppedUp(void)
{
   return _isPoppedUp;
}