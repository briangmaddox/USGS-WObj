#ifndef WARNINGWOBJ_H
#define WARNINGWOBJ_H

#include "WObj/WObj.h"

class WarningWObj : public WObj
{
   public:
      // Displays a message in an Motif Warning Dialog.
      // Popup and popdown by using XtManageChild and XtUnmanageChild on
      // the baseWidget (getWidget()).

      WarningWObj(char* name, Widget parent);
      void setMessage(char* message);

      void setOKCallback(XtPointer thisptr, CallbackWrapper cbw);
         // Sets the callback to be called when the "OK" button is pressed.

   protected:

   private:
};

#endif // WARNINGWOBJ_H