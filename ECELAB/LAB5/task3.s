.include "p24Hxxxx.inc"
.global __reset 
.bss

check_val: .space 2
c: .space 2
ones_count: .space 1
first_one: .space 1

.text

__reset: 
mov 0xF508, W1  ;initialize check_val
clr W2			;make c zero
clr W3			;make ones_count zero
clr W4			;make first_one zero

top:
cp W2, #16 
BRA Z, done     ;if c is 16 go to done
LSR W1, W2, W1 	;shift check_val right by c
ADD #1, W2 		;increment c

AND #1, W1		;check if bit is one
BRA Z, top   	;if not go back through loop

setOne: 
ADD #1, W3 	;increment ones_count
cp W3, #1		
BRA Z, setFirst ;if ones_count is 1 branch to setFirst

setFirst:
ADD W2, W4 	;add c's value to first_one
BRA top


done: 
mov 0xF508, W1
mov W1, check_val
mov W2, c
mov W3, ones_count
mov W4, first_one

goto done

.end