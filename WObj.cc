
#include "WObj/WObj.h"

WObj::WObj(char* name, Widget parent)
{
   if (name != NULL)
      {
         _widgetName = new char[strlen(name)+1];
         strcpy(_widgetName,name);
      }
   _baseWidget = NULL;
}

WObj::~WObj(void)
{

   delete [] _widgetName;

   // Make sure the widget hasn't already been destroyed
   if (_baseWidget != NULL) 
   {
       // Remove destroy callback so Xt can't call the callback
       // with a pointer to an object that has already been freed
       XtRemoveCallback ( _baseWidget,
                         XmNdestroyCallback,
                         &WObj::widgetDestroyedCallback,
                         (XtPointer) this );

       // Destroy the widget tree.
       XtDestroyWidget(_baseWidget);
   }
}

Widget WObj::getWidget(void)
{
   return _baseWidget;
}

void WObj::widgetDestroyedCallback ( Widget, XtPointer clientData, 
                                    XtPointer calldata)
{
   WObj* obj = (WObj*) clientData;     
    
   obj->widgetDestroyed();
}

void WObj::widgetDestroyed()
{
   _baseWidget = NULL;
}

void WObj::installDestroyHandler()
{
   if (_baseWidget != NULL)
      {
         XtAddCallback ( _baseWidget,
                        XmNdestroyCallback,
                        &WObj::widgetDestroyedCallback, 
                        (XtPointer) this );
      }
}
