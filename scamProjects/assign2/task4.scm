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

(define (let*->lambdas source)
  (define start (car source)) ;"define" 
  (define funcName (cadr source))
  (define keyword (caar (cddr source)))
 
  (if (equal? 'let* keyword) 
    (begin
      (define body (cdr (caddr source)))
      (define varList (car body))
      (define var (car (caar body)))
      (define expr1 (cadr (caar body)))
      (cond 
        ((null? (cdr varList)) (list start funcName (list (helper var (cdr body)) expr1)))
        (else (list start funcName (varHelper varList body)))
        )
      ) 
    source ;no let* found
    ) 
  )

(define (varHelper vList body)
  (define (recur var)
    (cond 
      ((null? (cdr var)) (list (helper (caar var) (cdr body)) (cadr (car var))))
      (else (list (list 'lambda (list (caar var)) (recur (cdr vList))) (cadr (car var))))
      )
    )
  (recur vList)
  )


(define (helper var body)
  (define (iter body expr)
    (cond
      ((null? (cdr body)) (append expr (list (car body))))
      (else (iter (cdr body) (append expr (list (car body))))) 
      )
    )
  (iter body (list 'lambda (list var)))
  )