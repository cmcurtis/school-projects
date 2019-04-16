(define (main)
  (setPort (open (getElement ScamArgs 1) 'read))
  (define env this)
  (define (iter expr)
    (if (not (eof?)) 
      (begin 
        (eval expr env)
        (iter (readExpr)))
      )
    )
  (iter (readExpr))
  )

(define (replace func x)
  
  )

;$
Your replace function needs to work recursively. That is to say, it needs to replace the symbol in all local function definitions, including lambdas.
You may find the predicate functions object? useful this feature as you should not descend into these kinds of objects. 
Neither should you process any quoted expression. You may assume the given function performs no assignments of any kind. 

You can obtain the body of a function definition as follows: 
    (define (square x) (* x x))
    (define body (get 'code square))
    (inspect body)
  
You can get the formal parameters by substituting 'parameters for 'code in the get expression. 
The code inspection displays the list (begin (* x x)) whose car is the symbol begin and whose cadr is the list (* x x). 

You can update the body of the function as follows: 
    (set 'code '(begin (+ x x)) square)
    (inspect (square 5))