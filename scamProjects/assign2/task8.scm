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
  (define n (newBST value))
  (define (search tree value)
    (cond
      ((< value (tree'value)) 
        (cond
          ((null? (tree'left)) (node (tree'value) n (tree'right)))
          (else (node (tree'value) (search (tree'left) value) (tree'right)))
          )
        )
      (else 
        (cond 
          ((null? (tree'right)) (node (tree'value) (tree'left) n))
          (else  (node (tree'value) (tree'left) (search (tree'right) value)))
          )
        )
      )
    )
  (search tree value)
  )