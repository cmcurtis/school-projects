(define (main)
    (setPort (open (getElement ScamArgs 1) 'read))
    (define arg1 (readExpr))
    (define arg2 (readExpr))
    (println "(halve " arg1 ") is " (halve arg1))
    (println "(double " arg1 ") is " (double arg1))
    (println "(div2? " arg1 ") is " (div2? arg1))
    (println "(ethiop " arg1 " " arg2 ") is " (ethiop arg1 arg2))
    )

(define (double y)
    (+ y y)
    )

(define (getBit x)
    (cond 
        ((= x 0) 1)
        (else 
            (define (iter store src) 
                (cond 
                    ((= src x) (double store))
                    (else (iter (double store) (+ src 1)))
                    )
                )
            (iter 1 1)
            )
        )
    )

(define (halve x)
    (define (iter sum d src) 
        (define b (getBit src))
        (cond
            ((= src 0) d)
            ((> (+ sum b) x) (iter sum d (- src 1)))
            (else (iter (+ sum b) (+ d (getBit (- src 1))) (- src 1)))
            )
        )
    (iter 0 0 24)
    )

(define (div2? z)
    (define (iter sum src) 
        (define b (getBit src))
        (cond
            ((= src 0)
                (cond
                    ((= (+ sum b) z) #f)
                    (else #t)
                    )
                )
            ((> (+ sum b) z) (iter sum (- src 1)))
            (else (iter (+ sum b) (- src 1)))
            )
        )
    (iter 0 24)
    )

(define (ethiop x y)
    (define (iter store src1 src2)
        (cond
            ((= src2 0) store)
            ((equal? #f (div2? src2)) (iter (+ store src1) (double src1) (halve src2)))
            (else (iter store (double src1) (halve src2)))
            )
        )
    (iter 0 x y)
    )