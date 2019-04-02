(define (main)
  (setPort (open (getElement ScamArgs 1) 'read))
  (define env this)
  (define (iter expr)
    (if (not (eof?)) 
      (begin 
        (eval expr env)
        (iter (readExpr)))
      )
    )
  (iter (readExpr))
  )

(define (range x y z)
  ;x is base and z is top and y is step 
  (define (iter base top step store l)
    (cond 
      ((= store top) (append l (list top)))
      ((> store top) l)
      (else 
        (iter base top step (+ step store) (append l (list store)))
        )
      )
    )
  
  (iter x y z x nil)
  )

(define (for-loop l f)
  (define (iter x) 
    (cond 
      ((null? x))
      (else 
        (f (car x))
        (iter (cdr x))
        )
      )
    )
  (iter l)
  )
