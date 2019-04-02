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
  (inspect params)
  (inspect l)
  (getList l)
  (cond
    ((eq? #t (integer? (car l)))
      (cond 
        (((= (length l) params) (apply f (car l))))
        (else (lambda (@) (curry f (append (car l) @))))
        )
      )
    ((= (length l) params) (apply f l))
    (else 
      (lambda (@) (curry f (append l @)))
      )
    )
  )

(define (integer? x) 
  (eq? (type x) 'INTEGER)
  )

(define (getList l)
  (inspect (cdr l))
  (inspect (car l))
  )