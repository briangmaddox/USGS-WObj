#ifndef WOBJ_H
#define WOBJ_H

#include <Xm/Xm.h>

// The following structure allows us to pass the thisptr and some useful
// client data to a callback.
class WObjClientData
{
   public:
      WObjClientData(void)
         {};

      WObjClientData(XtPointer thisptr, XtPointer data)
         {_thisptr = thisptr; _actual_clientdata = data; }

      void setThisPointer(XtPointer thisptr)
         { _thisptr = thisptr; }

      void setClientData(XtPointer data)
         {_actual_clientdata = data;}

      XtPointer getThisPointer(void) const
         { return _thisptr; }

      XtPointer getClientData(void) const
         { return _actual_clientdata; }

   private:
      XtPointer _thisptr;
      XtPointer _actual_clientdata;
};


typedef void (*CallbackWrapper) (Widget w, XtPointer clientdata, XtPointer calldata);

class WObj
{
   public:
 
      WObj(char* name, Widget parent);
      virtual ~WObj();

      Widget getWidget(void);

   protected:
      char* _widgetName;
      Widget _baseWidget;

      void installDestroyHandler();
         // Any subclass that directly sets _baseWidget must call this method
         // before leaving its constructor.

      static void widgetDestroyedCallback ( Widget w, XtPointer clientdata, 
                                         XtPointer calldata);
      virtual void widgetDestroyed(); 
};

#endif // WOBJ_H


