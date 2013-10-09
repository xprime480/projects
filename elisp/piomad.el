;;; set the path to include all needed libraries
;;;
(setenv "LD_LIBRARY_PATH"
	(concat (getenv "HOME")
		"/pio/review/pio/pio/dev/src/common/hana/lib"
		":"
		(getenv "LD_LIBRARY_PATH")))
