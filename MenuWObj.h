#ifndef MENUWOBJ_H
#define MENUWOBJ_H

#include "WObj/WObj.h"

class MenuWObj : public  WObj
{
   public:
      MenuWObj(char* name, Widget parent, char* cascadebuttonlabel);
      ~MenuWObj(void);

      void addButtonItem(char* buttonlabel, XtPointer thisptr,
                         CallbackWrapper cbw);
      void addSeparatorItem(void);
      void addSubMenuItem(char* buttonlabel, Widget submenu);
      void addToggleButtonItem(char* buttonlabel, 
                               XtPointer thisptr, 
                               CallbackWrapper valueChangedcallback);

      bool setSensitive(char* buttonlabel, bool flag);
         // If flag is true, the button with label 'buttonlabel' is set sensitive.
         // Otherwise, it's set insensitive. 
         // Return value: The return value indicates whether or not the operation
         // was successful.

      void setMapCallback(XtPointer clientdata, CallbackWrapper cbw);
         // The user of this class can provide a funtion to be called just before
         // the menu is mapped. This is useful for setting the sensitivity of
         // menu items.

   protected:
      Widget _menupane;
      Widget _cascadebutton;
      
      struct ButtonRecord
      {
         Widget button;
         char* label;
      };

      ButtonRecord _buttons[20];
      int _numButtons;

      void addButtonToList(Widget button, char* buttonlabel);
      Widget findButton(char* buttonlabel);

   private:
};

#endif // MENUWOBJ_H
