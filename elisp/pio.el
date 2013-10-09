;; #######################################################################
;;
;; 2010-05-14 MIRKO.LUEDDE@SAP.COM: 
;;
;; This is a SAMPLE CONFIGURATION FILE for the Emacs 
;; development environment.
;;
;; #######################################################################

;;; uncomment this line to disable loading of "default.el" at startup
;; (setq inhibit-default-init t)

;; Cscope source code navigation
(push "/mnt/install/tools/cscope/elisp" load-path)
(require 'xcscope)

;; Perforce revision control.  This uses an improved variant of "p4.el".
(push "/mnt/install/tools/p4/elisp" load-path)
(require 'mlu.perforce)

;; R statistics system.
(push "/mnt/install/tools/ess/share/emacs/site-lisp" load-path)
(require 'ess-site)

;; start the Emacs server, will be of help to Perforce/Emacs integration.
(server-start)

(tool-bar-mode 0)

;; turn on font-lock mode
(when (fboundp 'global-font-lock-mode)
  (global-font-lock-mode t))

;; enable visual feedback on selections
(setq transient-mark-mode t)

;; default to better frame titles
(setq frame-title-format
      (concat  "%b - emacs@" system-name))
(custom-set-variables
  ;; custom-set-variables was added by Custom -- don't edit or cut/paste it!
  ;; Your init file should contain only one such instance.
 '(delete-selection-mode nil nil (delsel))
 '(scroll-bar-mode (quote right))
 '(show-paren-mode t nil (paren))
 '(truncate-partial-width-windows nil))
(custom-set-faces
  ;; custom-set-faces was added by Custom -- don't edit or cut/paste it!
  ;; Your init file should contain only one such instance.
 )
