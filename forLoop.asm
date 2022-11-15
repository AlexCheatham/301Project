          .data #This is boilerplate stuff to get QTSPIM to read this file the right way
          .text
          .align 2
          .globl main 
main:
	addi $t0, $0, 100            #set upper limite of loop
	addi $s1, $0, 0              #s1 is current number (being added) start with zero
	addi $s0, $0, 0              #s0 is the running total
	
loop:
	addi $s1, $s1, 1
	add $s0, $s0, $s1
	bne $s1, $t0, loop
end:
	j end                       #End the program