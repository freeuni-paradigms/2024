; 1
(define (first-elem lst)
    (if 
        (null? lst) 
        "None"
        (car lst)
    )
)

; 2
(define (abs_ x)
    (if 
        (< x 0)
        (* x -1)
        x
    )
)

; 3
(define (right-triangle lst)
    (=  
        (+
            (* (car lst) (car lst))
            (* (cadr lst) (cadr lst))
        )
        (* (caddr lst) (caddr lst))
    )
)

; 4
(define (last-elem lst)
    (cond 
        ((null? lst) "None")
        ((null? (cdr lst)) (car lst))
        (#t (last-elem (cdr lst)))
    )
)

; 5
(define (length_ lst)
    (if 
        (null? lst) 
        0
        (+ (length_ (cdr lst)) 1)
    )
)

; 6
(define (k-th-element lst k)
    (cond
        ((null? lst) "None")
        ((zero? k) (car lst))
        (#t (k-th-element (cdr lst) (- k 1)))
    )
)

; 7
(define (filter-range lst a b)
    (if 
        (> a b) 
        (filter-range lst b a)
        (if
        (null? lst) `()
        (append (if 
                        (and (>= (car lst) a) (<= (car lst) b)) 
                        (list (car lst)) `()
                    )
                (filter-range (cdr lst) a b)
            ) 
        )
    )
)

(define (prime_helper n k)
    (cond
        ((= k 1) #t)
        ((= (remainder n k) 0) #f)
        (#t (prime_helper n (- k 1)))
    )
)

; 8
(define (prime? n)
    (if 
        (< n 2) #f
        (prime_helper n (- n 1))
    )
)

; 9 - next seminar
(define (primes? lst)
    (if
        (null? lst) lst
        (cons (prime? (car lst)) (primes? (cdr lst)))
    )
)