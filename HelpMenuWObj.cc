
#include "WObj/HelpMenuWObj.h"

HelpMenuWObj::HelpMenuWObj(char* name, Widget parent)
            : MenuWObj(name,parent,"Help")
{
   XtVaSetValues(parent,
                 XmNmenuHelpWidget, _cascadebutton,
                 NULL);
}
