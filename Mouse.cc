#include <stdio.h>
#include <stdlib.h>
#include "Mouse.h"

Mouse::Mouse(char* name, Widget parent) : WObj(name,parent)
{
   Widget rowcol;
   int accel_num, accel_denom, tmpthresh;
   double accel_val;

   _display = XtDisplay(parent);

   rowcol = XtVaCreateManagedWidget("rowcol",xmRowColumnWidgetClass,parent,NULL);

   _accel = XtVaCreateManagedWidget("accel",xmScaleWidgetClass,rowcol,NULL);
   XtAddCallback(_accel,XmNdragCallback,accelScaleDragCallbackWrapper,
                 (XtPointer) this);

   _threshold = XtVaCreateManagedWidget("threshold",xmScaleWidgetClass,rowcol,NULL);
   XtAddCallback(_threshold,XmNdragCallback,threshScaleDragCallbackWrapper,
                 (XtPointer) this);

   _baseWidget = rowcol;
 
#if 0
   save_button = XtVaCreateManagedWidget("save_button",xmPushButtonWidgetClass,
                                         form1, NULL);
   XtAddCallback(save_button,XmNactivateCallback,saveCallbackWrapper,
                 (XtPointer) this);

   reset_button = XtVaCreateManagedWidget("reset_button",xmPushButtonWidgetClass,
                                          form1,NULL);
   XtAddCallback(reset_button,XmNactivateCallback,resetCallbackWrapper,
                 (XtPointer) this);

   default_button = XtVaCreateManagedWidget("default_button",xmPushButtonWidgetClass,
                                            form1,NULL);
   XtAddCallback(default_button,XmNactivateCallback,defaultCallbackWrapper,
                 (XtPointer) this);


   quit_button = XtVaCreateManagedWidget("quit_button",xmPushButtonWidgetClass,
                                         form1,NULL);
   XtAddCallback(quit_button,XmNactivateCallback,quitCallbackWrapper,
                 (XtPointer) this);
#endif

   // Get the current accel and threshold values and init the scale positions.

   XGetPointerControl(_display,&accel_num,&accel_denom,&tmpthresh);
   accel_val = (accel_num * 1.0) / accel_denom;

   _orig_accel = accel_val;
   _orig_threshold = tmpthresh;
   _cur_accel = _orig_accel;
   _cur_threshold = _orig_threshold;

   updateScales();
}

void Mouse::updateScales(void)
{
   XmScaleSetValue(_accel,(int)(_cur_accel * 100.0));
   XmScaleSetValue(_threshold,_cur_threshold);
}

void Mouse::updatePointerControl(void)
{
   int accel_num;

   accel_num = (int) (_cur_accel * 100.0);
 
   XChangePointerControl(_display,True,True,accel_num,100,
                         _cur_threshold);
   XFlush(_display);
}

void Mouse::accelScaleDragCallbackWrapper(Widget w, XtPointer clientdata, 
                                          XtPointer calldata)
{
   ((Mouse*) clientdata) -> accelScaleDragCallback(w,calldata);
}

void Mouse::accelScaleDragCallback(Widget w, XtPointer calldata)
{
   XmScaleCallbackStruct *xsc;

   xsc = (XmScaleCallbackStruct*) calldata;

   _cur_accel = (xsc->value) / 100.0;
   updatePointerControl();
}

void Mouse::threshScaleDragCallbackWrapper(Widget w, XtPointer clientdata, 
                                          XtPointer calldata)
{
   ((Mouse*) clientdata) -> threshScaleDragCallback(w,calldata);
}

void Mouse::threshScaleDragCallback(Widget w, XtPointer calldata)
{
   XmScaleCallbackStruct *xsc;

   xsc = (XmScaleCallbackStruct*) calldata;

   _cur_threshold = xsc->value;
   updatePointerControl();
}

void Mouse::saveCallbackWrapper(Widget w, XtPointer clientdata, XtPointer calldata)
{
   ((Mouse*) clientdata) -> saveCallback(w,calldata);
}

void Mouse::saveCallback(Widget w, XtPointer calldata)
{
   // Save Mouse settings in $HOME/.xmouse

   char* tmp;
   char* savefile;
   FILE* outfile;

   tmp = getenv("HOME");
   if (tmp == NULL)
      {
         printf("HOME not set. Mouse settings not saved.\n");
         exit(1);
      }

   savefile = new char[strlen(tmp)+100];
   sprintf(savefile,"%s/.xmouse",tmp);

   outfile = fopen(savefile,"w");
   if (outfile == NULL)
      {
         printf("Couldn't open '%s' for writing. Mouse settings not saved.\n",
                savefile);
         exit(2);
      }

   fprintf(outfile,"%f\n%d\n",_cur_accel,_cur_threshold);
   fclose(outfile);

}

void Mouse::resetCallbackWrapper(Widget w, XtPointer clientdata, XtPointer calldata)
{
   ((Mouse*) clientdata) -> resetCallback(w,calldata);
}

void Mouse::resetCallback(Widget w, XtPointer calldata)
{
   _cur_accel = _orig_accel;
   _cur_threshold = _orig_threshold;
   updateScales();
   updatePointerControl();
}

void Mouse::defaultCallbackWrapper(Widget w, XtPointer clientdata, XtPointer calldata)
{
   ((Mouse*) clientdata) -> defaultCallback(w,calldata);
}

void Mouse::defaultCallback(Widget w, XtPointer calldata)
{
   // Reset accel and threshold to default values.

   int accel_num, accel_denom, tmpthresh;
   double accel_val;

   XChangePointerControl(_display, True, True, -1, -1, -1);
   XFlush(_display);

   XGetPointerControl(_display,&accel_num,&accel_denom,&tmpthresh);
   accel_val = (accel_num * 1.0) / accel_denom;

   _orig_accel = accel_val;
   _orig_threshold = tmpthresh;
   _cur_accel = _orig_accel;
   _cur_threshold = _orig_threshold;

   updateScales();

}

void Mouse::quitCallbackWrapper(Widget w, XtPointer clientdata, 
                                       XtPointer calldata)
{
   ((Mouse*) clientdata) -> quitCallback(w,calldata);
}

void Mouse::quitCallback(Widget w, XtPointer calldata)
{
   exit(0);
}

void Mouse::readParameters(void)
{
   char* tmp;
   char* savefile;
   FILE* infile;

   tmp = getenv("HOME");
   if (tmp == NULL)
      {
         printf("HOME not set.\n");
         exit(1);
      }

   savefile = new char[strlen(tmp)+100];
   sprintf(savefile,"%s/.xmouse",tmp);

   infile = fopen(savefile,"r");
   if (infile == NULL)
      {
         printf("Couldn't open '%s' for reading.\n",
                savefile);
         exit(2);
      }

   fscanf(infile,"%lf",&_cur_accel);
   fscanf(infile,"%d",&_cur_threshold);
   fclose(infile);

   printf("'%s'\n%f\n%d\n",savefile,_cur_accel,_cur_threshold);

   updatePointerControl();
}