
(defvar p4-work-dir "/home/I809989/pio/review/pio/pio")

(defun p4-update-diff ()
  (interactive)
  (save-excursion
    (p4-get)
    (cd p4-work-dir)
    (p4-have)
    ))



(p4-update-diff)
