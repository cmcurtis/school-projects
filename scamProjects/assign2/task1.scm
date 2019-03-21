(define (main)
  (define env this)
  (define (iter expr)
        (if (not (eof?)) (begin (eval expr env) (iter (readExpr))))
        )
  (iter (readExpr))
  
  )