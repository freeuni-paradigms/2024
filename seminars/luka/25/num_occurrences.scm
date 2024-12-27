(define (num-occurrences seq eq?)
  (map
    (lambda (x) 
      (apply + (map 
        (lambda (y) 
        (if (eq? x y) 1 0 )) seq))
    )
    seq
  )
)
