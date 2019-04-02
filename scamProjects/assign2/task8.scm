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
(define (node value left right) 
  (define (display) (print value))
  this
  )

(define (newBST value)
  (node value nil nil)
  )

(define (displayBST root)
  (define (iter root indent)
    (if (valid? root)
      (begin
        (iter (root'right) (string+ indent "    "))
        (print indent)
        ((root'display))
        (println)
        (iter (root'left) (string+ indent "    "))
        )
      )
    )
  (iter root "")
  )

;  takes a binary search tree and a value and returns a new binary search tree that includes that value
(define (insertBST tree value)
  
  )