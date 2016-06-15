CXX=g++
CXXFLAGS= -I/usr/X11R6/include -I..
LIBS=-L/usr/X11R6/lib -lXm -lXext -lXt -lX11 #-lPW

OBJS = 	WObj.o			\
	TopLevelWObj.o		\
	PopupWObj.o		\
	NButtonDialogWObj.o	\
	MenuWObj.o		\
	HelpMenuWObj.o		\
	ErrorWObj.o		\
	WarningWObj.o		\
	WObjUtils.o

libWObj.a: $(OBJS)
	ar r libWObj.a $(OBJS)

clean:
	rm -rf libwobj.a *.o core

.depend depend: 
	$(CXX) $(CXXFLAGS) -MM $(OBJS:.o=.cc) >.depend

include .depend


install:
	cp *.h ../include/WObj/
	cp libWObj.a ../lib/
