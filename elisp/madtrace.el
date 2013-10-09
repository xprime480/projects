(defvar tracecount 1)
;;(defvar tracemsg "log_message \"   spot #%d\\n\"\n")
(defvar tracemsg "std::cout << \"   spot #%d\\n\";\n")
(defun insert-trace-message () 
  (interactive)
  (insert (format tracemsg (setq tracecount (1+ tracecount)))))
(global-set-key '[f6] 'insert-trace-message)













