
# EXE_OBJS = make_apr.o linear_test.o 5d_test.o

# 

# ALL_OBJS = $(OBJS) $(EXE_OBJS)

# EXES = $(EXE_OBJS:.o=)

# CC = /opt/gcc-4.1.0/bin/g++


# all : $(EXES)

# $(EXES) : % : %.o $(OBJS)
# 	$(CC) -g -o $@ $^

# $(ALL_OBJS) : %.o : %.cpp
# 	$(CC) -g -c $<

# #
# # make a tags file
# #
# tags :
# 	etags *.cpp *.h

# #
# # rules for automatic dependencies
# #
# DEPS = $(ALL_OBJS:.o=.d)

# $(DEPS) : %.d: %.cpp
# 	set -e; $(CPP) -MM $(CPPFLAGS) $(INCLUDES) $(ORACLE_INCLUDES) $< \
# 		| sed 's/\($*\)\.o[ :]*/\1.o $@ : /g' > $@; \
# 		[ -s $@ ] || rm -f $@

# ifneq ($(MAKECMDGOALS),clean)
# ifneq ($(MAKECMDGOALS),distclean)
# include $(DEPS)
# endif
# endif


% :
	MYEXE=make_apr    make -f exe.mk $@
	MYEXE=linear_test make -f exe.mk $@
	MYEXE=5d_test     make -f exe.mk $@
