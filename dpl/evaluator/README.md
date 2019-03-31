Author: Caley Curtis

To write a program, define a main function, then call the function.
  Example:
    function main {} BEGIN
      #statements to execute#
      END
    call main{}

To run your program: *****

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

functions will return the last statement in the definition

If statement structure:
  Example:
  if { #condition# } BEGIN
    #do something#
    END
  else BEGIN
    #do something else#
    END

While loop structure:
  while{ #condition# } BEGIN
    # do something #
  END

comparisons can be made as follows:
less than : <
greater than : >
equal to : == 
less than or equal to : =<
greater than or equal to : =>


Arrays are created as such where size is the desired size of the array:
  let x = call newArray{#size#}

You can set a spot in an array, where i is the index, v is the value to be set and x is the array:
  call setArray{x, i, v}

You can get a value from an array in a similar fashion:
  v = call getArray{x, i}

Comments can be made as follows: 
  # this is a comment #

