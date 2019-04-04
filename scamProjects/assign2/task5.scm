(define (main)
  (setPort (open (getElement ScamArgs 1) 'read))
  (define env this)
  (define (iter expr)
      (if (not (eof?)) (begin 
        (eval expr env) 
        (iter (readExpr))))
      )
  (iter (readExpr))
  )

; takes an Arabic number and produces the equivalent Church numeral
(define (create n)
  (lambda (f) 
    (lambda (x) 
      (define (iter src store)
        (cond 
          ((= n src) (f store))
          (else (iter (+ 1 src) (f store)))
          )
        )
      (iter 1 x)
      )
    )
  )

;produces the predecessor of the given Church numeral
(define (pred n)
  (lambda (f) 
    (lambda (x) 
      (((n (lambda (g) 
              (lambda (h) 
                (h (g f))
                )
              )
          ) (lambda (u) x)) (lambda (u) u)
        )
      )
    )
  )