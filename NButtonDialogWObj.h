#ifndef NBUTTONDIALOGWOBJ_H
#define NBUTTONDIALOGWOBJ_H

#include "WObj/PopupWObj.h"



class NButtonDialogWObj : public PopupWObj
{
   private:

   protected:
      Widget _form;           // Topmost form widget (child of popup shell)
      Widget _buttonform;     // Form to hold the control buttons.
      CallbackWrapper _callbacks[10];
      XtPointer _clientdata[10];
      char* _labels[10];
      int _numbuttons;

      // Callback for the default "Close" button.
      static void _popdownCallbackWrapper(Widget w, XtPointer clientdata,
                                     XtPointer calldata);
      virtual void _popdownCallback(Widget w, XtPointer calldata);

   public:

      // Usage:
      //    (1) Create an instance of NButtonDialogWObj. 
      //    (2) Create a widget to appear in the dialog as a child of the
      //        widget returned from getFormWidget. If you have multiple widgets
      //        you want to appear in the dialog, create a composite or constraint 
      //        widget to manage them. There can only be one direct descendant of
      //        the dialog form widget.
      //    (3) Call addButton as many times as desired to set up the control
      //        buttons for the dialog.
      //    (4) Call setDialogContents passing the widget to appear in the dialog.


      NButtonDialogWObj(char* name, Widget parent);
      ~NButtonDialogWObj(void);

      Widget getFormWidget(void);
         // Returns the topmost form widget in the dialog. Clients should create
         // a manager widget with this widget as its parent. All widgets to appear
         // in the dialog should be children of that manager widget.
 
      void setDialogContents(Widget contents);
         // Once you've created a manager widget containing the dialog contents, 
         // call this method passing the manager widget.

      void addButton(char* buttonlabel, XtPointer thisptr, 
                     CallbackWrapper cbw);
         // Adds a button at the bottom of the dialog which invokes the callback
         // wrapper cbw passing thisptr as client data.
         // Passing NULL for thisptr and cbw creates a button which will pop the
         // dialog down. Passing NULL for buttonlabel as well creates a "Close"
         // button.
};

#endif // NBUTTONDIALOGWOBJ_H
