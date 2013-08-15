
BASEDIR=${HOME}/working/examples/cpp

CFLAGS += -std=c++11 -I${BASEDIR}/include -L${BASEDIR}/lib

% : %.cpp
	make -C ${BASEDIR}/utils all
	g++ $(CFLAGS) -g -o $@ $< -lutils

clean :
	-rm *.exe *~

