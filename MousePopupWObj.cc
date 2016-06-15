
#include "MousePopupWObj.h"

MousePopupWObj::MousePopupWObj(char* name, Widget parent)
              : NButtonDialogWObj(name, parent)
{
   _mousewobj = new Mouse("mouse",getFormWidget());

//   addButton("save",(XtPointer)_mousewobj,Mouse::saveCallbackWrapper);
   addButton("Reset", (XtPointer)_mousewobj,Mouse::resetCallbackWrapper);
   addButton("Default",(XtPointer)_mousewobj,Mouse::defaultCallbackWrapper);
   addButton("Close",NULL,NULL);

   setDialogContents(_mousewobj->getWidget());
}

