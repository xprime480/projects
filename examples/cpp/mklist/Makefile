# .PHONY : all clean test

# EXE = 

# all : $(EXE)

# LSRC =	ExpSolver.cpp \
# 	ListMaker.cpp \
# 	ExponentialGenerator.cpp \
# 	UniformGenerator.cpp \
# 	util.cpp

# MSRC =	mklist.cpp \
# 	edsolver.cpp

# SRC =	$(LSRC) $(MSRC)

# LOBJ = $(LSRC:.cpp=.o)
# OBJ = $(SRC:.cpp=.o)
# DEP = $(OBJ:.o=.d)

# LIB = libmklist.a

# CFLAGS += -O0

# $(EXE) : % : %.o
# 	g++ $(CFLAGS) -g -o $@ $< -L. -lmklist

# $(EXE) : $(LIB)

# $(LIB) : $(LOBJ)
# 	ar rcs $@ $+

# $(OBJ) : %.o : %.cpp
# 	g++ $(CFLAGS) -o $@ -g -c $<

# $(DEP) : %.d: %.cpp
# 	@echo Building dependencies for $< && \
# 	set -e; g++ -MM $< \
# 		| sed 's/\($*\)\.o[ :]*/\1.o $@ : /g' > $@; \
# 		[ -s $@ ] || rm -f $@

# clean : 
# 	@-rm $(LIB) $(OBJ) $(DEP) *~

# test : all

# -include $(DEP)



EXE_LIST   = mklist edsolver
LOCAL_TEST = local_test

% :
	for x in $(EXE_LIST) ; do MYEXE=$${x} make -f exe.mk $@ ; done

local_test : all
	./edsolver 50 15
	./mklist -s
	./mklist -s -p 1 -e 20
	./mklist -s -p 1 -l 100 -e 33 -o 15
