
#include "ColorDialogWObj.h"

ColorDialogWObj::ColorDialogWObj(char* name, Widget parent)
                : NButtonDialogWObj(name,parent)
{
   _colorchooser = new ColorChooserWObj("colorchooser",getFormWidget());

   addButton("Apply",NULL,NULL);
   addButton("Close",NULL,NULL);

   setDialogContents(_colorchooser->getWidget());
}