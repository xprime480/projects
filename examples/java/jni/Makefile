
LIBS  = libYuch.la libGorf.la
JAVA  = Yuch.java Gorf.java
CLASS = $(JAVA:.java=.class)
OBJ   = $(JAVA:.java=.o)
HDR   = $(JAVA:.java=.h)
BIN   = Yuch

all : $(BIN) $(LIBS)

Yuch : Yuch.java Gorf.class
	gcj -fjni --main=$@ -o $@ $(JAVA)

$(LIBS) : lib%.la : %.o
	libtool g++ -rpath `pwd` -o $@ -shared $*.lo

$(CLASS) : %.class : %.java
	gcj -C $<

$(OBJ) : %.o : %.cpp %.h JNIutils.h
	libtool g++ -c $*.cpp

$(HDR) : %.h : %.class
	gcjh -jni $*

clean : 
	-rm $(BIN) $(OBJ) $(HDR) $(LIBS) $(CLASS) >/dev/null 2>&1

