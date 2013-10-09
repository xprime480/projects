;;;;
;;;; Tools to help extract blocks from a buffer
;;;;

;; 
;;
(defun extract-buffer-substring (startfn endfn)
  "Extract a string from the current buffer defined by STARTFN and ENDFN.

STARTFN and ENDFN are functions of 0 parameters."

  (buffer-substring (funcall startfn) (funcall endfn)))

;; append a string from the current buffer to the target buffer
;;
(defun append-buffer-substring (buffer startfn endfn)
  "Append a string delimited by STARTFN and ENDFN to BUFFER."

  (interactive)
  (let ((s (extract-buffer-substring startfn endfn)))
    (if (not (string= "" s))
	(save-excursion
	  (set-buffer buffer)
	  (goto-char (point-max))
	  (insert s)
	  t)
      nil)))

;; look forward in the current buffer to next occurence of a tag
;; 
(defun next-occurence (re)
  "Return the point matching the begining of the line containing RE.

The beginning of the line containing point-max is returned if RE not 
matched."

  ;; re-search-forward leaves you at end-of-buffer on failure
  (if (re-search-forward re nil 1)
      (beginning-of-line))
  (point))

;; look for first of a list of regular expressions, and move there
;;
(defun goto-next-of (res)
  "Move point to the beginning of the line containing nearest match from RES.

If no regular expression from RES matches, move to the last line of
the visible part of the buffer."

  (goto-char (apply 'min (mapcar 'next-occurence res))))

;; extract some lines from one buffer and put in another
;;
(defun extract-lines-to-buffer (input output re-from re-to &optional copylast)
  "Extract blocks delimited by RE-FROM and RE-TO from buffer INPUT to OUTPUT.

If COPYLAST is non-nil, include line containing end."

  (let ((buf-src (get-buffer-create input))
	(buf-dst (get-buffer-create output)))
    (save-excursion
      (set-buffer buf-src)
      (goto-char (point-min))
      (while (append-buffer-substring 
	      buf-dst			; target buffer
	      (lambda () 		; get begining of region
		(next-occurence re-from))
	      (lambda () 		; get end of region
		(let ((tmp (next-occurence re-to)))
		  ;; todo - special case of match on last line of buffer
		  (if copylast
		      (progn
			(next-line 1)
			(beginning-of-line)
			(point))
		    tmp))))))))

