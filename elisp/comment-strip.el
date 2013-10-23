;;;
;;; Strip c-style and c++ style comments from a buffer.
;;;

(defun comment-stripper-new-style () 
  (interactive)
  (beginning-of-buffer)
  (while (re-search-forward "//" nil t)
    (backward-char 2)
    (kill-line)
    (if (not (bolp))
	(insert "\n"))))

(defun comment-stripper-old-style () 
  (interactive)
  (debug)
  (beginning-of-buffer)
  (while (re-search-forward "/\*" nil t)
    (backward-char 2)
    (let ((s (point)))
      (re-search-forward "\*/")
      (delete-region s (point)))))

(defun comment-stripper ()
  (interactive)
  (save-excursion
    (comment-stripper-new-style)
    (comment-stripper-old-style)))

