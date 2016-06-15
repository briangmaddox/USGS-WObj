
#include <stdio.h>
#include <stdlib.h>
#include <X11/Intrinsic.h>
#include <Xm/Label.h>
#include <Xm/TextF.h>

Widget createLabel(char* name, Widget parent, char* labelstr)
{
   Widget tmplabel;
   XmString xmstr;

   xmstr = XmStringCreateLtoR(labelstr,XmFONTLIST_DEFAULT_TAG);
   tmplabel = XtVaCreateManagedWidget(name,xmLabelWidgetClass,
                 parent,
                 XmNlabelString,         xmstr,
                 NULL);
   XmStringFree(xmstr);

   return tmplabel;
}

Widget setLabel(Widget label, char* labelstr)
{
   XmString xmstr;

   xmstr = XmStringCreateLtoR(labelstr,XmFONTLIST_DEFAULT_TAG);
   XtVaSetValues(label,
                 XmNlabelString,  xmstr,
                 NULL);
   XmStringFree(xmstr);
}

void setTextField(Widget textfield, char* val)
{
   XmTextFieldSetString(textfield,val);
}

void setTextField(Widget textfield, double val)
{
   char buf[1000];

   sprintf(buf,"%6.3lf",val);
   XmTextFieldSetString(textfield,buf);
}

char* getCharTextField(Widget w)
{
   return XmTextFieldGetString(w);
}

double getDoubleTextField(Widget w)
{
   char* buf;
   double retval;

   buf = XmTextFieldGetString(w);
   retval = strtod(buf,(char**)NULL);
   XtFree(buf);
 
   return retval;
}
