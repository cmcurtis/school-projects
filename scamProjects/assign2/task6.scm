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

(define (powerSet s)
  (if (null? s)
    (list `())
    (let ((rest (powerSet (cdr s))))
      (append rest (map (lambda (x) (cons (car s) x)) rest))
      )
    )
  )