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
(define (Stack) 
  (list )
  )

(define (push s val)
  (append (list val) s)
  )

(define (pop s) 
  (cdr s)
  )

(define (speek s)
  (car s)
  )

(define (ssize s)
  (length s)
  )

;Queue Methods
(define (helper q)
  (inspect q)
  (cond 
    ((null? (car q)) q)
    (else 
      (inspect (speek (car q)))
      (define s2 (push (cdr q) (speek (car q))))
      (inspect s2)
      (helper (cons (pop (car q)) s2))
      )
    )
  )

(define (Queue) 
  (cons (Stack) (Stack))
  )

(define (enqueue q val) 
  (cons (push (car q) val) (cdr q))
  )

(define (dequeue q)
  ;(inspect q)
  (cond 
    ((null? (cdr q)) (cons () (pop (reverse (car q)))))
    (else (cons (car q) (pop (cdr q))))
    )
  )

(define (qpeek q)
  (cond 
    ((null? (cdr q)) (speek (reverse (car q))))
    (else (speek (cdr q)))
    )
  )

(define (qsize q)
  (+ (ssize (car q)) (ssize (cdr q)))
  )