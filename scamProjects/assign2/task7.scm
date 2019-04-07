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

(define (matrix-*-vector m v)
  (map (lambda (col) (dot-product col v)) m)
  )

(define (transpose m)
  (accumulate-n cons nil m)
  )

(define (matrix-*-matrix m n)
  (let ((cols (transpose m))) 
    (map (lambda (row) (matrix-*-vector cols row)) n)
    )
  )
  
(define (dot-product v w)
  (accumulate + 0 (map * v w))
  )

(define (accumulate op initial sequence)
  ;(inspect sequence)
  (cond
    ((null? sequence) initial)
    (else (op (car sequence) (accumulate op initial (cdr sequence))))
    )
  )

(define (accumulate-n op init seqs)
  ;(inspect seqs)
  (cond
    ((null? (car seqs)) nil)
    (else (cons (accumulate op init (map car seqs)) (accumulate-n op init (map cdr seqs))))
    )
  )