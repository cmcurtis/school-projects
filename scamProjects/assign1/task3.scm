(define (main)
    (setPort (open (getElement ScamArgs 1) 'read))
    (define arg1 (readExpr))
    (define arg2 (readExpr))
    (println "((root-n " arg1 ") " arg2 ") is " (fmt "%.15f" ((root-n arg1) arg2)))
    )

(define (improve x y n)
    (/ (+ (* (- n 1.0) y) (/ x (^ y (- n 1.0)))) n)
    )

(define (root-n n)
    (define (helper x)
        (define (iter old guess x n)
            (cond 
                ((and (< (/ old guess) 1.000000001) (> (/ old guess) .999999999)) guess)
                (else (iter guess (improve x guess n) x n))
                )
            )
        (real (iter 0 1 x n) )
        )
    helper
    )