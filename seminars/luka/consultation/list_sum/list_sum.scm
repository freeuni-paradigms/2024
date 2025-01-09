
(define (get-digits rem)
	(if (= rem 0) '()
		(cons (remainder rem 10) (get-digits (div rem 10)))	
	)
)

(define (reversed-sum lst current-remainder)
	(if (null? (car lst)) (get-digits current-remainder)
		(let ((x (+ (apply + (map car lst)) current-remainder)))
			(cons (remainder x 10) (reversed-sum (map cdr lst) (div x 10)))
		)
	)
)

(define (sum l)
	(reverse (reversed-sum (map reverse l) 0))
)



;; !!!ამ ხაზის ქვემოთ არაფერი შეცვალოთ!!!

;; 1
(display (if (equal? (sum '((1 2)
			    (5 3)))
		     '(6 5)) "1 SUCCESS" "1 FAILURE"))(newline)
;; 2
(display (if (equal? (sum '((6 3)
			    (5 9)))
		     '(1 2 2)) "2 SUCCESS" "2 FAILURE"))(newline)
;; 3
(display (if (equal? (sum '((1 2 3)
			    (3 1 4)
			    (1 0 1)))
		     '(5 3 8)) "3 SUCCESS" "3 FAILURE"))(newline)
;; 4
(display (if (equal? (sum '((8 7 2 3 6 1)
			    (1 0 3 5 0 0)
			    (3 4 0 0 1 6)
			    (6 2 6 1 1 5)))
		     '(1 9 4 1 9 9 2)) "4 SUCCESS" "4 FAILURE"))(newline)

