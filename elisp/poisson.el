
;; this would be the right way to go if we had proper 
;; tail recursion elimination
;;
(defun factr (i n f)
  (if (> i n)
      f
    (factr (1+ i) n (* f i))))

;; factorial of N
;;
(defun fact (n)
  (factr 2 n 1.0))

;; probability of COUNT items from a poisson distribution with MEAN
;; 
(defun p-poisson (mean count)
  (/ (* (exp (- mean))
	(expt mean count))
     (fact count)))

;; this would be the right way to go if we had proper 
;; tail recursion elimination
;;
(defun seqr (i n l)
  (if (> i n)
      l
    (seqr (1+ i) n (append l (list i)))))

(defun seq (n)
  (seqr 0 n '()))

(defun n-or-less (mean n)
  (apply '+
	 (mapcar (lambda (k) (p-poisson mean k)) (seq n))))

(defun p-between (mean min max)
  (- (n-or-less mean max) (if (= min 0) 0 (n-or-less mean (- min 1)))))

(p-between 60.0 0 60.0)
