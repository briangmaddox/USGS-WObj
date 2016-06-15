#ifndef TOPLEVELWOBJ_H
#define TOPLEVELWOBJ_H

#include "WObj/WObj.h"

class TopLevelWObj : public WObj
{
   protected:
      XtAppContext _appContext;
      Display *_display;

   public:

   TopLevelWObj(char* appclass, int* argc, char** argv);

   XtAppContext getAppContext(void);
   Display* getDisplay(void);
};

#endif // TOPLEVELWOBJ_H
