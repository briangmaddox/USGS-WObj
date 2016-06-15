#ifndef POPUPWOBJ_H
#define POPUPWOBJ_H

#include "WObj/WObj.h"

class PopupWObj : public WObj
{
   public:

      PopupWObj(char* name, Widget parent);
      virtual void popUp(void);
      virtual void popDown(void);
      virtual bool isPoppedUp(void);

   protected:

   private:
      bool _isPoppedUp;

};

#endif // POPUPWOBJ_H
