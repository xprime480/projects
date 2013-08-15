
BASEDIR=${HOME}/working/examples/cpp

% : %.cpp
	make -C ${BASEDIR}/utils all
	g++ -std=c++11 $(CFLAGS) -I${BASEDIR}/include -L${BASEDIR}/lib -g -o $@ $< -lutils

clean :
	-rm *.exe *~

