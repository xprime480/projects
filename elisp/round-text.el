(defun round-text-4 ()
  (interactive)
  (save-excursion
    (let ((lo (point))
	  (hi (progn (search-forward "\"") (backward-char) (point))))
      (let ((newtext (format "%.4e" 
			     (string-to-number (buffer-substring lo hi)))))
	(kill-region lo hi)
	(insert newtext)))))