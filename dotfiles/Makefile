
FILES ?= \
        .abbrev_defs	\
	.bash_logout	\
	.bash_profile	\
	.bashalias	\
	.bashrc		\
	.dbinit		\
	.emacs		\
	.gdbinit	\
	.gitconfig	\
	.profile	\
	.pyinit		\
	.sqliterc	\
	.vimrc		\
	.wgetrc

DESTDIR ?= $(HOME)

install :
	@for f in $(FILES) ; \
		do diff -q $$f $(DESTDIR)/$$f >/dev/null || \
		(echo "Installing $$f" && cp -p $$f $(DESTDIR)/$$f ); \
	done
