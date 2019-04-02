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
  )

(define (pop s) 
  )

(define (speek s)
  )

(define (ssize s)
  )

;Queue Methods
;Queue: constructor
(define (Queue) 
  (define head nil)
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
  )