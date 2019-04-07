(define (main)
  (setNilDisplay 'nil)
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
    (list '())
    (let ((rest (powerSet (cdr s))))
      (merge rest (map (lambda (x) (cons (car s) x)) rest))
      )
    )
  )

(define (merge s t) 
  (cond
    ((null? s) t)
    ((null? t) s)
    ((< (length (car s)) (length (car t))) 
      (append (list (car s)) (merge (cdr s) t)))
    (else 
      (append (list (car t)) (merge s (cdr t)) ))
  )
)