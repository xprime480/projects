OBJS       =	levenshtein.o	\
		ForwardStrPointer.o \
		Score.o \
		DistanceWithTranspose.o \
		Trie.o \
		TrieNode.o \
		MatchData.o

BASEDIR    = $(shell pwd)/..
LIB        = libapproxmatch.a

include $(BASEDIR)/generic.mk

lib : $(LIB)

$(LIB) : $(OBJS)
	-rm $(LIB)
	ar cr $(LIB) $+
