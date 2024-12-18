(define (digits n)
    (if (< n 10) (list n)
        (append (digits (div n 10)) (list (remainder n 10)))
    )
)

(define (left_pad lst n)
    (if (= (length lst) n) lst
        (left_pad (cons 0 lst) n)
    )
)
;; '(5)
;; (apply  (append () () () ()) )
(define (lunar_addition_with_lists a b)
    (if (null? a) '()
        (cons (max (car a) (car b)) (lunar_addition_with_lists (cdr a) (cdr b)))
    ) 
)

(define (to_number lst num)
    (if (null? lst) num
        (to_number (cdr lst) (+ (* num 10) (car lst)))
    )
)

(define (lunar_addition a b)
    (let (
            (a_digits (digits a))
            (b_digits (digits b))
        )
        (to_number
            (lunar_addition_with_lists
                (left_pad a_digits (max (length a_digits) (length b_digits)))
                (left_pad b_digits (max (length a_digits) (length b_digits)))
            )
            0
        )
    )
)
