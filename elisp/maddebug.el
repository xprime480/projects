
(defvar debug-test-program "./fs_optimizer")

(defun debug-proc (proc-name)
  "Run a gdb session for a process"
  (let* ((simple-name (file-name-nondirectory proc-name))
	 (target-buffer (get-buffer (format "*gud-%s" simple-name))))
    (and target-buffer (kill-buffer target-buffer)))
  (gdb (format "gdb %s" proc-name)))

(defun debug-test ()
  (interactive)
  (find-file (format "%s/.gdbinit" debug-base-dir))
  (debug-proc debug-test-program)
  nil)

(global-set-key [f3] 'debug-test)


