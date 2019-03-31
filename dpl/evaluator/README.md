Author: Caley Curtis

To write a program, define a main function, then call the function.
  Example:
    function main {} BEGIN
      #statements to execute#
      END
    call main{}

In your main function you can define variables with or without assigning value:
  Example:
    let x = "hello"
    let y

you can also define other functions:
  Example:
  function foo{a, b} BEGIN
    let z = a + b
  END

and call those functions:
  Example:
  let c = call foo{5, 8} 

