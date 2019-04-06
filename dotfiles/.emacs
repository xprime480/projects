;; Mike Davis .emacs file based loosely on
;; Red Hat Linux default .emacs initialization file

;; Are we running XEmacs or Emacs?
(defvar running-xemacs (string-match "XEmacs\\|Lucid" emacs-version))

;; Set up the keyboard so the delete key on both the regular keyboard
;; and the keypad delete the character under the cursor and to the right
;; under X, instead of the default, backspace behavior.
;;
(global-set-key [delete] 'delete-char)
(global-set-key [kp-delete] 'delete-char)

;; Turn on font-lock mode for Emacs
(cond ((and (not running-xemacs) (eq window-system 'x))
       (global-font-lock-mode t)))

;; Always end a file with a newline
;;(setq require-final-newline t)

;; Stop at the end of the file, not just add lines
(setq next-line-add-newlines nil)

;; Enable wheelmouse support by default
(cond (window-system
       (mwheel-install)
       ;; use extended compound-text coding for X clipboard
       (set-selection-coding-system 'compound-text-with-extensions)))

(setq enable-recursive-minibuffers t)

(push (concat (getenv "HOME") "/elisp") load-path)
(load-library "local-defs")
;;(set-build-env)
(load-library "savehist")

(setq auto-mode-alist
      (append (list (cons "\\.h$" 'c++-mode)
		    (cons "\\.xml$" 'text-mode)
		    (cons "\\.mak$" 'makefile-mode)
		    (cons "\\.gdbinit$" 'shell-script-mode)
		    (cons "\\.xml" 'xml-mode))
	      auto-mode-alist))
(add-hook 'c++-mode-hook 'auto-fill-mode)
(add-hook 'text-mode-hook 'auto-fill-mode)
(add-hook 'sql-mode-hook (lambda () (setq tab-width 3)))
(add-hook 'f90-mode-hook 'abbrev-mode)

(setq hostname (nth 0 (split-string (getenv "HOSTNAME") "\\.")))

(add-to-list 'default-frame-alist '(font . "10x20"))
(add-to-list 'default-frame-alist '(geometry . "80x25+50+50"))
(if (eq window-system 'x) 
    (add-to-list 'default-frame-alist (cons 'background-color 
					    (cond
					     (t "white")))))

(display-time)

(read-abbrev-file)
(setq vc-diff-switches "-w")		; ignore whitespace

(defun proc-command-line-in-dir (flag cmd)
  (let ((name (car command-line-args-left)))
    (if name
	(let ((path (concat "~/ss2/research/" name)))
	  (cd path)
	  (apply cmd (list path))
	  (setq command-line-args-left
		(cdr command-line-args-left)))
      (progn
	(message (format "%s requires a directory name" flag))
	(sit-for 2)))))

(defun proc-work-switch (arg)
  (proc-command-line-in-dir arg 'dired))

(defun proc-build-switch (arg)
  (proc-command-line-in-dir arg
			    (lambda (p) (compile "make"))))


;;(setq py-python-command "/usr/bin/python24")
(setq py-python-command "/usr/bin/python")

(setq command-switch-alist
      (append (list (cons "--work" 'proc-work-switch)
		    (cons "--build" 'proc-build-switch))
	      command-switch-alist))
(custom-set-variables
  ;; custom-set-variables was added by Custom.
  ;; If you edit it by hand, you could mess it up, so be careful.
  ;; Your init file should contain only one such instance.
  ;; If there is more than one, they won't work right.
 '(delete-selection-mode nil)
 '(menu-bar-mode t)
 '(savehist-additional-variables (quote (compile-history)))
 '(savehist-mode t nil (savehist))
 '(scroll-bar-mode (quote right))
 '(tool-bar-mode nil nil (tool-bar)))
(custom-set-faces
  ;; custom-set-faces was added by Custom.
  ;; If you edit it by hand, you could mess it up, so be careful.
  ;; Your init file should contain only one such instance.
  ;; If there is more than one, they won't work right.
 )

(savehist-mode 1)
;;(setq scheme-program-name "guile")

(add-hook 'compilation-mode-hook '(lambda () 
				    (setq compile-history
					  (delete-dups compile-history))))

(defun safe-require (dir sym)
  (and (file-exists-p dir)
       (push dir load-path)
       (require sym)))

;; start the Emacs server, will be of help to Perforce/Emacs integration.
(if (< 1 0)
    (progn
      (defun server-ensure-safe-dir (dir) "NOOP" t)
      (server-start))
  (message "Omitting server-start"))

(put 'narrow-to-region 'disabled nil)
(put 'downcase-region 'disabled nil)
(put 'upcase-region 'disabled nil)
