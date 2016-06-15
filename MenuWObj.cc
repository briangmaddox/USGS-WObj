#include <string.h>
#include <Xm/CascadeB.h>
#include <Xm/PushB.h>
#include <Xm/RowColumn.h>
#include <Xm/Separator.h>
#include <Xm/ToggleB.h>
#include "WObj/MenuWObj.h"

MenuWObj::MenuWObj(char* name, Widget parent, char* cascadebuttonlabel)
        : WObj(name,parent)
{
   // Create a cascadebutton and menupane as children of parent. The cascade
   // button will have name and labelString cascadebuttonlabel.

   _numButtons = 0;

   _menupane = XmCreatePulldownMenu(parent,name,NULL,0);

   if (cascadebuttonlabel != NULL)
      {
         _cascadebutton = XtVaCreateManagedWidget(cascadebuttonlabel,
                                                 xmCascadeButtonWidgetClass,
                                                 parent,NULL);
         XtVaSetValues(_cascadebutton,
                       XmNsubMenuId,    _menupane,
                       NULL);
      }

   _baseWidget = _menupane;
   installDestroyHandler();
}

MenuWObj::~MenuWObj(void)
{
   for (int i = 0; i < _numButtons; i++)
     {
        delete [] _buttons[i].label;
     }
}

void MenuWObj::addButtonItem(char* buttonlabel, XtPointer thisptr,
                             CallbackWrapper cbw)
{
   Widget tmpbutton;

   tmpbutton = XtVaCreateManagedWidget(buttonlabel, 
                                       xmPushButtonWidgetClass,
                                       _menupane,
                                       NULL);
   if (cbw != NULL)
      XtAddCallback(tmpbutton,XmNactivateCallback,cbw,thisptr);

   addButtonToList(tmpbutton,buttonlabel);
}

void MenuWObj::addSeparatorItem(void)
{
   Widget tmpsep;

   tmpsep = XtVaCreateManagedWidget("separator",
                                    xmSeparatorWidgetClass,
                                    _menupane,
                                    NULL);
}

void MenuWObj::addSubMenuItem(char* buttonlabel, Widget submenu)
{
   _cascadebutton = XtVaCreateManagedWidget(buttonlabel,
                                            xmCascadeButtonWidgetClass,
                                            _menupane, NULL);

   XtVaSetValues(_cascadebutton,
                 XmNsubMenuId,    submenu,
                 NULL);
}

void MenuWObj::addToggleButtonItem(char* buttonlabel,
                                   XtPointer thisptr,
                                   CallbackWrapper valueChangedCallback)

{
   Widget tmpbutton;

   tmpbutton = XtVaCreateManagedWidget(buttonlabel,
                                       xmToggleButtonWidgetClass,
                                       _menupane,
                                       XmNvisibleWhenOff, True,
                                       NULL);

   // If there's a callback, install it.
   if (thisptr != NULL)
      XtAddCallback(tmpbutton,XmNvalueChangedCallback,
                    valueChangedCallback, (XtPointer) thisptr);
}

bool
MenuWObj::setSensitive(char* buttonlabel, bool flag)
{
   Widget button;

   button = findButton(buttonlabel);
   if (button != NULL)
      {
         if (flag == true)
            XtSetSensitive(button, True);
         else
            XtSetSensitive(button, False);
         return true;
      }

   return false;
}

void
MenuWObj::setMapCallback(XtPointer clientdata, CallbackWrapper cbw)
{
   XtAddCallback(_menupane, XmNmapCallback, cbw, clientdata);
}

void
MenuWObj::addButtonToList(Widget button, char* buttonlabel)
{
   _buttons[_numButtons].button = button;
   _buttons[_numButtons].label = new char[strlen(buttonlabel)+1];
   strcpy(_buttons[_numButtons].label, buttonlabel);
   _numButtons++;
}

Widget
MenuWObj::findButton(char* buttonlabel)
{
   int i;
   bool found;

   i = 0;
   found = false;
   while ((i < _numButtons) && (!found))
      {
         if (strcmp(_buttons[i].label, buttonlabel) == 0)
            found = true;
         else
            i = i + 1;
      }

   if (found)
      return _buttons[i].button;

   return NULL;
}
