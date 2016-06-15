#ifndef COLORCHOOSERWOBJ_H
#define COLORCHOOSERWOBJ_H

#include "WObj.h"

class ColorChooserWObj : public WObj
{
   private:

   public:

      struct colordb_rec
      {
         char* name;
         int r,g,b;
      };

   protected:

      static colordb_rec* _colors[1000];
      static int _numcolors;
      static bool first_time = true;

      Widget _label;
      Widget _scrolledlist;
      Widget _frame;
      Widget _colorlabel;

   public:

      ColorChooserWObj(char* name, Widget parent);

};

#endif // COLORCHOOSERWOBJ_H
