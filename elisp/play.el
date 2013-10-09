
(defun subsets (set)
  (subset-helper (list (list)) (reverse set)))

(defun subset-helper (partial set)
  (if (null set)
      partial
    (subset-helper
     (append (mapcar (lambda (x) (cons (car set) x)) partial) partial)
     (cdr set))))

(defun histogram (vals)
  (histogram-helper '() vals))

(defun histogram-helper (hg vals)
  (if (null vals)
      hg
    (let* ((val (car vals))
	   (rest (cdr vals))
	   (found (assq val hg)))
      (histogram-helper (append (list (cons val (1+ (or (cdr found) 0))))
				(assq-delete-all val hg))
			rest))))

(defun repeat (count what)
  (repeat-helper '() count what))

(defun repeat-helper (out count what)
  (if (<= count 0)
      out
    (repeat-helper (append (list what) out) (1- count) what)))

(defun range (low high)
  (range-helper '() low high))

(defun range-helper (out low high)
  (if (> low high)
      out
    (range-helper (cons high out) low (1- high))))

(range 1 5)

(subsets '())
(subsets (range 1 1))
(subsets (range 1 3))
(subsets (range 1 6))

(mapcar (lambda (x) (apply '+ x)) (subsets (range 1 6)))

(defun test-histogram (l)
  (mapcar (lambda (x) (princ x) (terpri)) 
	  (sort (histogram l) (lambda (a b) (< (car a) (car b))))))

(test-histogram (mapcar (lambda (x) (apply '+ x)) (subsets (range 1 6))))

(test-histogram (append (repeat 100 10) (repeat 25 6)))
