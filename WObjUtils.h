#ifndef _WOBJUTILS_H_
#define _WOBJUTILS_H_

Widget createLabel(char* name, Widget parent, char* labelstr);
Widget setLabel(Widget label, char* labelstr);

void setTextField(Widget textfield, char* val);
void setTextField(Widget textfield, double val);
char* getCharTextField(Widget w);
double getDoubleTextField(Widget w);

#endif // _WOBJUTILS_H_
