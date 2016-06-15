#ifndef MOUSE_H
#define MOUSE_H

#include <Xm/Xm.h>
#include <Xm/Form.h>
#include <Xm/RowColumn.h>
#include <Xm/Scale.h>
#include <Xm/PushB.h>
#include <Xm/Separator.h>
#include "WObj.h"

class Mouse : public WObj
{
   private:
  
   protected:
      Display *_display;
      Widget  _basewidget;
      Widget  _accel;
      Widget  _threshold;

      double _orig_accel;
      int    _orig_threshold;
      double _cur_accel;
      int    _cur_threshold;

      void updateScales(void);
         // Sets the position of the thumb in each scale to the current values
         // of acceleration and threshold.

      void updatePointerControl(void);
         // Calls XtChangePointerControl with the values of _cur_accel and
         // _cur_threshold;

      // Callbacks

      static void  accelScaleDragCallbackWrapper(Widget w, XtPointer clientdata,
                                                 XtPointer calldata);
      virtual void accelScaleDragCallback(Widget w, XtPointer calldata);

      static void  threshScaleDragCallbackWrapper(Widget w, XtPointer clientdata,
                                                  XtPointer calldata);
      virtual void threshScaleDragCallback(Widget w, XtPointer calldata);


      virtual void saveCallback(Widget w, XtPointer calldata);


      virtual void resetCallback(Widget w, XtPointer calldata);


      virtual void defaultCallback(Widget w, XtPointer calldata);


      static void  quitCallbackWrapper(Widget w, XtPointer clientdata, 
                                       XtPointer calldata);
      virtual void quitCallback(Widget w, XtPointer calldata);


   public:
      static void  saveCallbackWrapper(Widget w, XtPointer clientdata,
                                       XtPointer calldata);
      static void  resetCallbackWrapper(Widget w, XtPointer clientdata,
                                        XtPointer calldata);
      static void  defaultCallbackWrapper(Widget w, XtPointer clientdata,
                                          XtPointer calldata);

      Mouse(char* name, Widget parent);

      void readParameters(void);
         // Attempts to read and set the mouse parameters from the file $HOME/.xmouse
};

#endif // MOUSE_H
