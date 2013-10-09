;;;;
;;;; extract SQL statements from buffers
;;;; 

(load-library "extract-utils")

;; regular expressions that begin a SQL statement
;;
(defvar sql-begin-regexp "SELECT\\|UPDATE\\|DELETE\\|INSERT")

;; regular expressions that end a SQL statement
;;
(defvar sql-end-regexp "^$")

;; where to put extracted SQL
;;
(defvar sql-extract-buffer "*sql-extract*")

;; extract SQL from a buffer and copy it into a common area
;;
(defun extract-sql-from-buffer (buf)
  "Extract SQL statements from buffer BUF.  Append to buffer *sql-extract*."
  (interactive "BBuffer to extract from: ")
  (extract-lines-to-buffer buf
			   sql-extract-buffer
			   sql-begin-regexp
			   sql-end-regexp
			   t))
