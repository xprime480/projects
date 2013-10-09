(defun canonicalize (dir)
  (expand-file-name (expand-file-name (concat dir "/."))))

(defun locate-toplevel (dir)
  (let ((dir (canonicalize dir)))
    (or (string-equal dir "/")
	(if (file-exists-p (concat dir "/research.mk.in"))
	    dir
	    (locate-toplevel (concat dir "/.."))))))

(defun set-build-env ()
  (let ((root (locate-toplevel default-directory)))
  (and (stringp root)
       (setenv "WORK_ROOT" root)
       (cd root))))
