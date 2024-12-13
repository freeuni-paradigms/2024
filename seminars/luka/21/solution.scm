(define (digits n)
	(if (< n 10)
		(list n)
		(append (digits (div n 10)) (list (remainder n 10)))
	)
)


;; (define (mapfn x)
;;   (expt x (length lst))
;;   )

(define (power n k)
	(if (zero? k)
		1
		(* n (power n (- k 1)))
	)
)

(define (list_power lst)
	(map (lambda (x) (power x (length lst))) lst)
)

(define (sum lst)
	(if (null? lst) 0 (+ (car lst) (sum (cdr lst))))
)

(define (narcisisstic? n)
	(= n (sum (list_power (digits n))))
)

(define (count n lst)
	(sum (map (lambda (x) (if (= x n) 1 0)) lst))	
)

(define (count2 n lst)
	(if (null? lst)
		0
		(if (= (car lst) n)
			(+ 1 (count2 n (cdr lst)))
			(count2 n (cdr lst))
		)
	)
)

(define (set lst)
	(if (null? lst)
		'()
		(if (= (count (car lst) (cdr lst)) 0)
			(cons (car lst) (set (cdr lst)))
			(set (cdr lst))
		)
	)
)

(define (frequency lst)
	(map (lambda (x) (list x (count x lst))) (set lst))
)

(define (multiplyone n k)
	(if (= n 0) 
		'()
		(cons k (multiplyone (- n 1) k))
	)
)

;; ((1 1 1) (2 2 2)) -> (append (1 1 1) (2 2 2))
(define (multiply n lst)
	(apply append (map (lambda (x) (multiplyone n x)) lst))
)


(define (ksubset n lst)
	(if (= n 0)
		'(())
		(if (null? lst)
			'()
			(append 
				(map (lambda (x) (cons (car lst) x)) (ksubset (- n 1) (cdr lst)))
				(ksubset n (cdr lst)) 
			)
		)
	)
)



