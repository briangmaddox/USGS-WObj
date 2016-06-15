#include <stdio.h>
#include <Xm/Form.h>
#include <Xm/Label.h>
#include <Xm/List.h>
#include <Xm/Frame.h>
#include "ColorChooserWObj.h"

#define RGBTXTFILEPATH "/usr/lib/X11/rgb.txt"

ColorChooserWObj::colordb_rec* ColorChooserWObj::_colors[1000];
int ColorChooserWObj::_numcolors;
bool ColorChooserWObj::first_time;

ColorChooserWObj::ColorChooserWObj(char* name, Widget parent)
                : WObj(name,parent)
{

   char buffer[100];
   FILE* infile;
   int i, red, green, blue;
   int pos;

   _baseWidget = XtVaCreateManagedWidget(name,
                                         xmFormWidgetClass,
                                         parent,
                                         NULL);

   _label = XtVaCreateManagedWidget("label",
                                    xmLabelWidgetClass,
                                    _baseWidget,
                                    XmNleftAttachment,    XmATTACH_FORM,
                                    XmNtopAttachment,     XmATTACH_FORM,
                                    XmNrightAttachment,   XmATTACH_FORM,
                                    NULL);

   _scrolledlist = XmCreateScrolledList(_baseWidget,"list",NULL,0);
   XtVaSetValues(XtParent(_scrolledlist),
                 XmNleftAttachment,       XmATTACH_FORM,
                 XmNleftOffset,           10,
                 XmNtopAttachment,        XmATTACH_WIDGET,
                 XmNtopWidget,            _label,
                 XmNtopOffset,            10,
                 XmNrightAttachment,      XmATTACH_FORM,
                 XmNrightOffset,          10,
                 NULL);
    XtManageChild(_scrolledlist);

   _frame = XtVaCreateManagedWidget("frame",
                                    xmFrameWidgetClass,
                                    _baseWidget,
                                    XmNfractionBase,      100,
                                    XmNleftAttachment,    XmATTACH_POSITION,
                                    XmNleftPosition,      10,
                                    XmNtopAttachment,     XmATTACH_WIDGET,
                                    XmNtopWidget,         XtParent(_scrolledlist),
                                    XmNtopOffset,         15,
                                    XmNrightAttachment,   XmATTACH_POSITION,
                                    XmNrightPosition,     90,
                                    XmNbottomAttachment,  XmATTACH_POSITION,
                                    XmNbottomPosition,    95,
                                    NULL);

   _colorlabel = XtVaCreateManagedWidget("colorlabel",
                                         xmLabelWidgetClass,
                                         _frame,NULL);

   // Read the color database.

   infile = fopen(RGBTXTFILEPATH,"r");
   if (infile == NULL)
      {
         fprintf(stderr,"ColorChooserWObj::ctor, Could not open '%s' for reading.\n",
                 RGBTXTFILEPATH);
         return;
      }

   _numcolors = 0;
   fgets(buffer,81,infile);
   while (!feof(infile))
      {
         if (buffer[0] != '!')
            {
               _colors[_numcolors] = new colordb_rec;
               sscanf(buffer,"%d %d %d", &red, &green, &blue);
               _colors[_numcolors]->r = red;
               _colors[_numcolors]->g = green;
               _colors[_numcolors]->b = blue;

               pos = 11;
               while ((pos < 80) && 
                      ((buffer[pos] == ' ') || (buffer[pos] == '\t')))
                  pos = pos + 1;

               _colors[_numcolors]->name = new char[strlen(&(buffer[pos]))+1];
               strcpy(_colors[_numcolors]->name,&(buffer[pos]));
               _colors[_numcolors]->name[strlen(&(buffer[pos]))-1] = '\0';
               _numcolors = _numcolors + 1;
            }
         fgets(buffer,81,infile);
      }
   fclose(infile);

   printf("Number of colors: %d\n",_numcolors);

   for (i = 0; i < _numcolors; i++)
      {
         printf("'%s' (%d,%d,%d)\n",_colors[i]->name,
                _colors[i]->r, _colors[i]->g, _colors[i]->b);
      }

   XmString* tmpstrings;
   // Make XmStrings outta the names and add them to the scrolled list..
   tmpstrings = new XmString[_numcolors];
   for (i = 0; i < _numcolors; i++)
      {
         tmpstrings[i] = XmStringCreateSimple(_colors[i]->name);
      }
   XmListAddItemsUnselected(_scrolledlist,tmpstrings,_numcolors,1);
   for (i = 0; i < _numcolors; i++)
      XmStringFree[i];
   delete [] tmpstrings;
}



