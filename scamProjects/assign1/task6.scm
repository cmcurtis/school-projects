(define (main)
    (setPort (open (getElement ScamArgs 1) 'read))
    (define arg1 (eval (readExpr) this))
    (define arg2 (readExpr))
    (println "(S " arg1 " " arg2 ") is " (fmt "%.15f" (S arg1 arg2)))
    (println "(w " arg1 " " arg2 ") is " (fmt "%.15f" (w arg1 arg2)))
    )

(define (S f x)
    (define (iter index store src)
        (cond 
            ((= src 0) (f src))
            ((= index src) (+ store (f index)))
            (else 
                (iter (+ index 1) (+ store (f index)) src)
                )
            )
        )
    (iter 0 0 x)
    )

(define (w f y)
    (cond
        ((= y 0) (f y))
        (else
            (define a (S f (+ y 1)))
            (define b (S f (- y 1)))
            (define c (S f y))
            ;(inspect a)
            ;(inspect b)
            ;(inspect c)
            (/
                (- (* a b) (* c c))
                (+ (- a (* 2 c)) b)
                )
            )
        )
    )