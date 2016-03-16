;;-*-coding: emacs-mule;-*-
(define-abbrev-table 'html-mode-abbrev-table '(
    ))

(define-abbrev-table 'sgml-mode-abbrev-table '(
    ))

(define-abbrev-table 'vc-git-log-view-mode-abbrev-table '(
    ))

(define-abbrev-table 'apropos-mode-abbrev-table '(
    ))

(define-abbrev-table 'awk-mode-abbrev-table '(
    ))

(define-abbrev-table 'c++-mode-abbrev-table '(
    (".inc" "#include \"\"" nil 0)
    ("catch" "catch" c-electric-continued-statement 0)
    ("else" "else" c-electric-continued-statement 2)
    ("fpr" "
    fprintf(stderr, \": %f\\n\", );

" nil 13)
    ("gmd" "AprPriceRange::getMinDelta()" nil 4)
    ("while" "while" c-electric-continued-statement 0)
    ))

(define-abbrev-table 'c-mode-abbrev-table '(
    ("else" "else" c-electric-continued-statement 0)
    ("for" "for ( ;; ) {
}" nil 1)
    ("if" "if ( ) {
}" nil 4)
    ("while" "while" c-electric-continued-statement 0)
    ))

(define-abbrev-table 'comint-mode-abbrev-table '(
    ))

(define-abbrev-table 'diff-mode-abbrev-table '(
    ))

(define-abbrev-table 'emacs-lisp-mode-abbrev-table '(
    ))

(define-abbrev-table 'f90-mode-abbrev-table '(
    ("`ab" "allocatable" nil 0)
    ("`al" "allocate" nil 0)
    ("`as" "assignment" nil 0)
    ("`ba" "backspace" nil 0)
    ("`bd" "block data" nil 0)
    ("`c" "character" nil 0)
    ("`cl" "close" nil 0)
    ("`cm" "common" nil 0)
    ("`cn" "contains" nil 0)
    ("`cx" "complex" nil 0)
    ("`cy" "cycle" nil 0)
    ("`de" "deallocate" nil 0)
    ("`df" "define" nil 0)
    ("`di" "dimension" nil 0)
    ("`dw" "do while" nil 0)
    ("`el" "else" nil 0)
    ("`eli" "else if" nil 0)
    ("`elw" "elsewhere" nil 0)
    ("`eq" "equivalence" nil 0)
    ("`ex" "external" nil 0)
    ("`ey" "entry" nil 0)
    ("`fa" ".false." nil 0)
    ("`fl" "forall" nil 0)
    ("`fo" "format" nil 0)
    ("`fu" "function" nil 0)
    ("`i" "integer" nil 0)
    ("`if" "interface" nil 0)
    ("`im" "implicit none" nil 1)
    ("`in " "include" nil 0)
    ("`it" "intent" nil 0)
    ("`lo" "logical" nil 0)
    ("`mo" "module" nil 0)
    ("`na" "namelist" nil 0)
    ("`nu" "nullify" nil 0)
    ("`op" "optional" nil 0)
    ("`pa" "parameter" nil 0)
    ("`pi" "private" nil 0)
    ("`pm" "program" nil 0)
    ("`po" "pointer" nil 0)
    ("`pr" "print" nil 0)
    ("`pu" "public" nil 0)
    ("`r" "real" nil 0)
    ("`rc" "recursive" nil 0)
    ("`rt" "return" nil 0)
    ("`rw" "rewind" nil 0)
    ("`se" "select" nil 0)
    ("`sq" "sequence" nil 0)
    ("`su" "subroutine" nil 2)
    ("`t" "type" nil 0)
    ("`ta" "target" nil 0)
    ("`tr" ".true." nil 0)
    ("`wh" "where" nil 0)
    ("`wr" "write" nil 0)
    ("sub" "    SUBROUTINE
      IMPLICIT NONE
    ENDSUBROUTINE

" nil 6)
    ("wr" "WRITE (*,*) " nil 1)
    ))

(define-abbrev-table 'fundamental-mode-abbrev-table '(
    ))

(define-abbrev-table 'global-abbrev-table '(
    ("abo" "	    /*!
	      If , the program aborts. 
	    */" nil 40)
    ("bri" "    /*!
      \\brief
    
      \\param

      \\return
    */" nil 19)
    ("dep" "      /*!
	This function is deprecated, calling it aborts the program.
      */" nil 0)
    ("ilc" "  /*!
  */" nil 7)
    ("inc" "#include \".h\"" nil 9)
    ("mxd" "#if defined(MAX_DEBUG)
" nil 11)
    ("ova" "      /*!
	This program should never be called, calling it aborts the
	program.  It is only called if because a template overload for
	some datatype was not defined.
      */" nil 14)
    ("rgc" "    /*
     *
     */
" nil 3)
    ("sex" "Support::Exception" nil 8)
    ("thr" "      /*!
	If , the program throws a Support::Exception. 
      */" nil 26)
    ("var" "    /*!
      \\brief
    */" nil 59)
    ))

(define-abbrev-table 'gud-mode-abbrev-table '(
    ))

(define-abbrev-table 'idl-mode-abbrev-table '(
    ))

(define-abbrev-table 'java-mode-abbrev-table '(
    ("catch" "catch" c-electric-continued-statement 0)
    ("else" "else" c-electric-continued-statement 0)
    ("finally" "finally" c-electric-continued-statement 0)
    ("while" "while" c-electric-continued-statement 0)
    ))

(define-abbrev-table 'lisp-mode-abbrev-table '(
    ))

(define-abbrev-table 'log-edit-mode-abbrev-table '(
    ))

(define-abbrev-table 'log-view-mode-abbrev-table '(
    ))

(define-abbrev-table 'makefile-automake-mode-abbrev-table '(
    ))

(define-abbrev-table 'makefile-bsdmake-mode-abbrev-table '(
    ))

(define-abbrev-table 'makefile-gmake-mode-abbrev-table '(
    ))

(define-abbrev-table 'makefile-imake-mode-abbrev-table '(
    ))

(define-abbrev-table 'makefile-makepp-mode-abbrev-table '(
    ))

(define-abbrev-table 'makefile-mode-abbrev-table '(
    ))

(define-abbrev-table 'nroff-mode-abbrev-table '(
    ))

(define-abbrev-table 'objc-mode-abbrev-table '(
    ("else" "else" c-electric-continued-statement 0)
    ("while" "while" c-electric-continued-statement 0)
    ))

(define-abbrev-table 'occur-mode-abbrev-table '(
    ))

(define-abbrev-table 'outline-mode-abbrev-table '(
    ))

(define-abbrev-table 'perl-mode-abbrev-table '(
    ))

(define-abbrev-table 'php-mode-abbrev-table '(
    ("GL" "GLOBAL" nil 0)
    ("else" "else" c-electric-continued-statement 0)
    ("ex" "extends" nil 0)
    ("fu" "function" nil 0)
    ("req" "require(" nil 0)
    ("ret" "return" nil 0)
    ("while" "while" c-electric-continued-statement 0)
    ))

(define-abbrev-table 'pike-mode-abbrev-table '(
    ("else" "else" c-electric-continued-statement 0)
    ("while" "while" c-electric-continued-statement 0)
    ))

(define-abbrev-table 'python-mode-abbrev-table '(
    ))

(define-abbrev-table 'rpm-spec-mode-abbrev-table '(
    ))

(define-abbrev-table 'sh-mode-abbrev-table '(
    ))

(define-abbrev-table 'shell-mode-abbrev-table '(
    ))

(define-abbrev-table 'sql-mode-abbrev-table '(
    ("del" "delete" nil 0)
    ("ins" "insert" nil 0)
    ("sel" "select" nil 0)
    ("upd" "update" nil 0)
    ))

(define-abbrev-table 'text-mode-abbrev-table '(
    ))

(define-abbrev-table 'vc-annotate-mode-abbrev-table '(
    ))

(define-abbrev-table 'vc-dired-mode-abbrev-table '(
    ))

(define-abbrev-table 'vc-log-mode-abbrev-table '(
    ))

