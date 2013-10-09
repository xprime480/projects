(defun subsets (set)
  (subset-helper (list (list)) (reverse set)))
subsets

(defun subset-helper (partial set)
  (if (null set)
      partial
    (subset-helper
     (append (mapcar (lambda (x) (cons (car set) x)) partial) partial)
     (cdr set))))
