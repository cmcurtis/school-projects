(define (main)
    (setPort (open (getElement ScamArgs 1) 'read))
    (define arg1 (readExpr))
    (define arg2 (readExpr))
    (define arg3 (readExpr))
    (println "((crazyTriangle " arg1 " " arg2 ") " arg3 ")")
    ((crazyTriangle arg1 arg2) arg3)
    )

(define (crazyTriangle a b)
    (define (printTriangle z)
        (define (printSpace d) 
            (cond 
                ((= d z) (display ""))
                (else (display " ")
                    (printSpace (+ d 1))
                    )
                )
            )
        ;function to print row of triangle
        (define (printItem m n max-len)
            (cond
                ((= n 0) 
                    (printSpace (+ m 1))
                    (display a)
                    )
                ((= n m) (display b))
                (else 
                    (display (pascalItem m n))
                    )
                )
            )
        ;functions to do the math
        (define (pascalItem m n)
            (cond 
                ((= n 0) a)
                ((= n m) b)
                (else (+ (pascalItem (- m 1) (- n 1))
                        (pascalItem (- m 1) n))
                        )
                )
            )
        ;functions to do the math
        (define (pascal-iter m n max-len)
            (cond 
                ((and (< m max-len) (< n max-len))
                    (printItem m n max-len)
                    (cond
                        ((= m n) 
                            (display "\n") 
                            (pascal-iter (+ m 1) 0 max-len))
                        (else 
                            (display " ")
                            (pascal-iter m (+ n 1) max-len))
                        )
                    )
                (else
                    )
                )
            )
        (pascal-iter 0 0 z)
        )
    printTriangle
    )