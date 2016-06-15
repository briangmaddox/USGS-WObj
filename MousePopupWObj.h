#ifndef MOUSEPOPUPWOBJ_H
#define MOUSEPOPUPWOBJ_H

#include "NButtonDialogWObj.h"
#include "Mouse.h"

class MousePopupWObj : public NButtonDialogWObj
{
   private:

   protected:
      Mouse *_mousewobj;

   public:

      MousePopupWObj(char* name, Widget parent);

};

#endif // MOUSEPOPUPWOBJ_H
