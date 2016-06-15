#include <stdio.h>
#include <Xm/Label.h>
#include <Xm/Form.h>
#include <Xm/Separator.h>
#include <Xm/PushB.h>

#include "WObj/NButtonDialogWObj.h"

void NButtonDialogWObj::_popdownCallbackWrapper(Widget w, XtPointer clientdata,
                                             XtPointer calldata)
{
   ((NButtonDialogWObj*)clientdata)->_popdownCallback(w,calldata);
}

void NButtonDialogWObj::_popdownCallback(Widget w, XtPointer calldata)
{
   popDown();
}

NButtonDialogWObj::NButtonDialogWObj(char* name, Widget parent)
              : PopupWObj(name, parent)
{
   // Create a form to manage everything as a child of our ancestor's 
   // popup shell.
   _form = XtVaCreateManagedWidget("form",xmFormWidgetClass, _baseWidget,NULL);

   _numbuttons = 0;
}

NButtonDialogWObj::~NButtonDialogWObj(void)
{
   int i;

   for (i = 0; i < _numbuttons; i++)
      {
         delete [] _labels[i];
      }
}

Widget NButtonDialogWObj::getFormWidget(void)
{
   return _form;
}

void NButtonDialogWObj::setDialogContents(Widget contents)
{
   Widget separator, tmpbutton;
   double fudge,deltax,deltax_space,deltax_button,curx;
   int i;

   // Create the rest of the dialog component.

   if (contents == NULL)
      {
         contents = XtVaCreateManagedWidget("filler",xmLabelWidgetClass,_form,NULL);
      }

   XtVaSetValues(contents,
                 XmNleftAttachment,  XmATTACH_FORM,
                 XmNtopAttachment,   XmATTACH_FORM,
                 XmNrightAttachment, XmATTACH_FORM,NULL);

   separator = XtVaCreateManagedWidget("separator",xmSeparatorWidgetClass,_form,
                                       XmNorientation,     XmHORIZONTAL,
                                       XmNtopAttachment,   XmATTACH_WIDGET,
                                       XmNtopWidget,       contents,
                                       XmNtopOffset,       5,
                                       XmNleftAttachment,  XmATTACH_FORM,
                                       XmNrightAttachment, XmATTACH_FORM,
                                       NULL);

   _buttonform = XtVaCreateManagedWidget("buttonform",xmFormWidgetClass,_form,
                                        XmNtopAttachment,    XmATTACH_WIDGET,
                                        XmNtopWidget,        separator,
                                        XmNleftAttachment,   XmATTACH_FORM,
                                        XmNrightAttachment,  XmATTACH_FORM,
                                        XmNbottomAttachment, XmATTACH_FORM,NULL);
   // Create all the control buttons.
 
   if (_numbuttons == 0)
      addButton("Dismiss",NULL,NULL);
 
   fudge = 1.0 / _numbuttons;
   deltax = 100.0 / ((2.0 * _numbuttons) + 1.0);
   deltax_space = fudge * deltax;
   deltax_button = (100.0 - (deltax_space * (_numbuttons + 1.0))) / _numbuttons;
   curx = deltax_space;
   for (i = 0; i < _numbuttons; i++)
      {
         tmpbutton = XtVaCreateManagedWidget(_labels[i],xmPushButtonWidgetClass,
                                             _buttonform,
                                             XmNfractionBase,     100,
                                             XmNleftAttachment,   XmATTACH_POSITION,
                                             XmNleftPosition,     (int) curx,
                                             XmNrightAttachment,  XmATTACH_POSITION,
                                             XmNrightPosition,  
                                                ((int) (curx + deltax_button)),
                                             XmNtopAttachment,    XmATTACH_FORM,
                                             XmNtopOffset,        5,
                                             XmNbottomAttachment, XmATTACH_FORM,
                                             XmNbottomOffset,     5, NULL);
         if (_callbacks[i] != NULL)
            XtAddCallback(tmpbutton,XmNactivateCallback,_callbacks[i],
                          _clientdata[i]);
         else
            XtAddCallback(tmpbutton,XmNactivateCallback,
                          _popdownCallbackWrapper,(XtPointer) this);

         curx = curx + deltax_space + deltax_button;
      }
}

void NButtonDialogWObj::addButton(char* buttonlabel, XtPointer thisptr, 
                               CallbackWrapper cbw)
{
 
   if (buttonlabel == NULL)
      buttonlabel = "Close";

   _labels[_numbuttons] = new char[strlen(buttonlabel)+1];
   strcpy(_labels[_numbuttons],buttonlabel);

   _clientdata[_numbuttons] = thisptr;
   _callbacks[_numbuttons] = cbw;

   _numbuttons = _numbuttons + 1;
}


