#include <Xm/MessageB.h>
#include "WObj/WarningWObj.h"

WarningWObj::WarningWObj(char* name, Widget parent) : WObj(name,parent)
{
   _baseWidget = XmCreateWarningDialog(parent,name,NULL,0);
   XtVaSetValues(_baseWidget,
                 XmNdialogStyle,  XmDIALOG_PRIMARY_APPLICATION_MODAL,
                 NULL);

   XtUnmanageChild(XmMessageBoxGetChild(_baseWidget,XmDIALOG_HELP_BUTTON));
}

void WarningWObj::setMessage(char* message)
{
   XmString tmpstr;

   tmpstr = XmStringCreateLtoR(message,XmFONTLIST_DEFAULT_TAG);
   XtVaSetValues(_baseWidget,
                 XmNmessageString,     tmpstr,
                 NULL);
   XmStringFree(tmpstr);
}

void
WarningWObj::setOKCallback(XtPointer thisptr, CallbackWrapper cbw)
{
   XtAddCallback(_baseWidget, XmNokCallback, cbw, (XtPointer) thisptr);
}