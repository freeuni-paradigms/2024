;1 reverse duplicate

(define (reverse lst)
  (if (null? lst)
    '()
    (append
      (reverse (cdr lst))
      (list (car lst))
    )
  )
)

(define (reverseDup lst)
  (let ((reversed (reverse lst))) (append reversed reversed))
)

(define (binpow a b)
  (if (zero? b) 1 
    (let
      ((x (binpow a (div b 2))))
      (if (zero? (remainder b 2)) 
        (* x x)
        (* x x a)
      )
    )
  )
)


(define (fib-helper a b n)
  (if (zero? n) a
    (fib-helper b (+ a b) (- n 1))  
  )
)

(define (fib n)
  (fib-helper 0 1 n)
)

(define (fib1 n)
  (let loop
	 (
	  (a 0)
	  (b 1)
	  (i 0)
	  )
	 (if (= i n) a
		(loop b (+ a b) (+ i 1))
	  )
	 )
  )

(define (partition k lst)
  (if (null? lst) '(()())
    (let
      ((p (partition k (cdr lst))))

      (if (< (car lst) k)
        (list (cons (car lst) (car p)) (cadr p))
        (list (car p) (cons (car lst) (cadr p)))
      )
    )
  )  
)

;; (remove-all (1 3 2) 3)
;; (append (1) () (2))

(define (remove-all lst elem)
  (apply append
    (map
      (lambda (x)
        (if (equal? elem x) '()
          (list x)
        )
      )
      lst
    )
  )
)

(define (permutation? l1 l2)
  (if (not (equal? (length l1) (length l2))) #f
    (if (null? l1) #t  
      (permutation? (remove-all l1 (car l1)) (remove-all l2 (car l1)))
    )
  )
)



(define (contains lst x)
  (if (null? lst) #f
    (or (equal? (car lst) x) (contains (cdr lst) x))  
  )
)

(define (dfs g curr end visited) ; -> t/f
  (if (= curr end) #t
    (contains 
      (map
        (lambda (n)
          (if (not (contains visited n)) (dfs g n end (cons n visited))
            #f
          )
        )
        (get_neighbours g curr)
      )
      #t
    )
  )
)

(define (myfilter lst blacklist)
  (apply append (map (lambda (x) (if (contains blacklist x) '() (list x))) lst))
)

(define (dedup lst)
  (if (null? lst) '()
    (if (contains (cdr lst) (car lst))
      (dedup (cdr lst))
      (cons (car lst) (dedup (cdr lst)))
    )
  )
)

(define (get_neighbours g x)
  (apply append
    (map
      (lambda (edge) 
        (cond
          ((= x (car edge)) (list (cadr edge)))
          ((= x (cadr edge)) (list (car edge)))
          (#t '())
        )
      )
      g
    )
  )
)

(define (bfs g queue end visited) ; -> t/f
  (if (contains visited end) #t
    (if (null? queue) #f
      (let ((next_wave (myfilter (dedup (apply append (map (lambda (x) (get_neighbours g x)) queue))) visited) ))
        (bfs g next_wave end (dedup (append visited next_wave)))
      )
    )
  )
)

(define (isWay? g start end)
  (bfs g (list start) end (list start))
)

