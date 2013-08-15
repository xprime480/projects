INCL_DEPS = $(OBJS:.o=.d)

%.d: %.cpp
	set -e; $(CPP) -MM $(CPP_FLAGS) $(INCL_FLAGS) $< \
		| sed 's/\($*\)\.o[ :]*/\1.o $@ : /g' > $@; \
		[ -s $@ ] || rm -f $@

ifneq ($(MAKECMDGOALS),clean)
-include $(INCL_DEPS)
endif
