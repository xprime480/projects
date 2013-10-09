
(defun p4-info-insert-dir (dir patterns)
  (mapcar (lambda (p) 
	    (mapcar (lambda (x) 
		      (save-excursion
			(find-file x)
			(p4-info-insert)
			(save-buffer)
			(kill-buffer (current-buffer))))
		    (file-expand-wildcards (concat dir p))))
	  patterns))

(p4-info-insert-dir 
 "/home/I809989/pio/review/pio/pio/dev/src/dm/utils/"
 '("*.h" "*.cpp"))


