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

(define (curry f @) 
  (define params (length (get 'parameters f)))
  (define l @)
  (cond
    ((null? l) (lambda (@) (curry f @)))
    ((eq? #f (integer? (car l)))
      (cond 
        ((= (length (car l)) params) (apply f (car l)))
        (else 
          (lambda (@) (curry f (append (car l) @))))
        )
      )
    ((= (length l) params) (apply f l))
    (else 
      (lambda (@) (curry f (append l @)))
      )
    )
  )