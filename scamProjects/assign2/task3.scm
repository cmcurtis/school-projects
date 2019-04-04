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

;Stack Methods
;constructor
(define (Stack) 
  (define items (list nil))
  this
  )

(define (push s val)
  (inspect (class s))
  ;(cons val s) ;?
  
  )

(define (pop s) 
  (head cdr s)
  (car s)
  )

(define (speek s)
  (car s)
  )

(define (ssize s)
  (define (iter store items) 
    (cond 
      ((null? items) store)
      (else 
        (iter (+ store 1) (cdr items)) ;?
        )
      )
    )
  (iter 0 s)
  )

;Queue Methods
;Queue: constructor
(define (Queue) 
  (define items (list nil))
  this
  )

(define (enqueue q val) 
  )

(define (dequeue q)
  )

(define (qpeek q)
  )

(define (qsize q)
  (define (iter store items) 
    (cond 
      ((null? items) store)
      (else 
        (iter (+ store 1) (cdr items)) ;?
        )
      )
    )
  (iter 0 s)
  )