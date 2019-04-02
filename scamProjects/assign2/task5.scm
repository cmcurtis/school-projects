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
(define (create )
  
  )

;produces the predecessor of the given Church numeral
(define (pred )
  
  )