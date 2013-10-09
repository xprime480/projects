;;; -*- Mode: lisp-interaction -*-
;;;


(defun fs_set_env (dir)
  (let* ((root (concat (concat (getenv "HOME") "/research/") dir)))
    (setenv "WORK_ROOT" root)
    (cd root)))

(fs_set_env "work")
(fs_set_env "newdatalayer")





