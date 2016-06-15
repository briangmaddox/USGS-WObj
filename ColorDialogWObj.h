#ifndef COLORDIALOGWOBJ_H
#define COLORDIALOGWOBJ_H

#include "NButtonDialogWObj.h"
#include "ColorChooserWObj.h"

class ColorDialogWObj : public NButtonDialogWObj
{
   private:

   protected:
      ColorChooserWObj* _colorchooser;

   public:

      ColorDialogWObj(char* name, Widget parent);

};

#endif // COLORDIALOGWOBJ_H
