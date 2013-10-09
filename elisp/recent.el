
(defun reload (buffer)
  (switch-to-buffer buffer)
  (revert-buffer t t t))

(defun fiffer ()
  (interactive)
  (reload "trace_new.log")
  (reload "trace_old.log")
  (ediff-buffers "trace_new.log" "trace_old.log"))
