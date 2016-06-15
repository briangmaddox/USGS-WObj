#include <X11/Xmu/Editres.h>
#include "WObj/TopLevelWObj.h"


TopLevelWObj::TopLevelWObj(char* appclass, int* argc, char** argv) : WObj(NULL,NULL)
{

   _baseWidget = XtVaAppInitialize(&_appContext, appclass, NULL, 0, argc, argv,
                                   NULL, NULL);
   installDestroyHandler();

//   XtAddEventHandler(_baseWidget, (EventMask) 0, True, 
//                    _XEditResCheckMessages,NULL);

   _display = XtDisplay(_baseWidget);

    XtVaSetValues ( _baseWidget,
                   XmNmappedWhenManaged, FALSE,
                   XmNx, DisplayWidth ( _display, 0 ) / 2,
                   XmNy, DisplayHeight ( _display, 0 ) / 2,
                   XmNwidth,  1,
                   XmNheight, 1,
                   NULL );


  

   XtRealizeWidget(_baseWidget);

}

XtAppContext TopLevelWObj::getAppContext(void)
{
   return _appContext;
}

Display* TopLevelWObj::getDisplay(void)
{
   return _display;
}


