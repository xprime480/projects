(defvar fixdir-root "/home/I809989/research/FinScience")

(defvar file-locations 
  (list (concat fixdir-root "/libsrc/datax")
	(concat fixdir-root "/libsrc/framework")
	(concat fixdir-root "/libsrc/pob")
	(concat fixdir-root "/libsrc/support")
	(concat fixdir-root "/include/datax")
	(concat fixdir-root "/include/framework")
	(concat fixdir-root "/include/pob")
	(concat fixdir-root "/include/support")))

(defvar dstdir-prefix (concat fixdir-root "/include/"))

(defun locate-file-helper (name places)
  (if (consp places)
      (let ((place (car places)))
	(if (file-exists-p (concat place "/" name))
	    place
	  (locate-file-helper name (cdr places))))
    nil))

(defun locate-file (name)
  (locate-file-helper name file-locations))

(defun lastsubdir (dir)
  (car (nreverse (split-string dir "/"))))

(defun srcdir-to-dstdir (src)
  (if (string= dstdir-prefix (substring src 0 (length dstdir-prefix)))
      src
    (concat dstdir-prefix (lastsubdir src))))

(defun relocate-file (file srcdir)
  (let ((tbuf "**fixdir**")
	(dstdir (srcdir-to-dstdir srcdir))
	(lastdir (lastsubdir srcdir)))
    (if (get-buffer tbuf)
	(kill-buffer tbuf))
    (if (not (string= srcdir dstdir))
	(rename-file (concat srcdir "/" file) (concat dstdir "/" file)))
    
    (with-output-to-temp-buffer tbuf
      (princ (concat "find " fixdir-root " -name '*.d' -exec grep -q " file " {} \\\; -print | xargs rm"))
      (terpri)
      (princ "make tags")
      (terpri))
    (save-excursion
      (set-buffer tbuf)
      (bash-buffer nil))
    (kill-buffer tbuf)
    (visit-tags-table fixdir-root)
    (tags-query-replace (concat "\\([<\"]\\)" file)
			(concat "\\1" lastdir "/" file) nil nil nil)))

(defun fix-dir (file) 
  (interactive "sFile: ")
  (let ((dir (locate-file file)))
    (if dir
	(relocate-file file dir)
      (message (concat "No file named " file " was found in the path")))))
