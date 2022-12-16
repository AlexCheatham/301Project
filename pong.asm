.data
.text
.align 2
.globl main
main:

	#variable assignments
	#s0 is screenwidth
	#s1 is ballx
	#s2 is bally
	#s3 is ballvx
	#s4 is ballvy
	#s5 is halfbarwidth
	#s6 is barposition
	#s7 is barvelocity
	
	addi $s0, $0, 256  # screenwidth = 256
	srl $s1, $s0, 1     # ballx = screenwidth/2
	addi $s2, $0, 199  # bally = 199
	addi $s3, $0, 1    # ballvx = 1
	addi $s4, $0, -1    # ballvy = -1
	addi $s5, $0, 10    # halfbarwidth = 10
	srl $s6, $s0, 1     # barposition = screenwidth/2
	addi $s7, $0, 0     # barvelocity = 0

	#game loop
	#t0 is x
	#t1 stores the decimal ASCII code for 'a'
	addi $t1, $0, 97
	#t2 stores the decimal ASCII code for 'd'
	addi $t1, $0, 100

loop:

	#get the keypress.  to do this we loop until we have a keypress
	# effectively the code is
	# while (address 256 gives zero)
	# no new keypress


keyboard_loop: #loop until there is keyboard input
	lw $t0, 256($0)   #check value at address 0x0100 (decimal 256)
	beq $t0, $0, keyboard_loop
	# if here, something to read from keyboad
	lw $t0, 260($0)    # do lw on 0x0104
	sw $0, 256($0)     # set memory location 0x0100 to 0

	# at this point, #t0 has the keypress
	beq $t0, $t2, its_d
	# if here, it's a # assuming only a or d
	addi $s7, $s7, 1   #barvelocity += 1
	j end_char_select
its_d:
	addi $s7, $s7, -1
end_char_select:	
	add $s6, $s6, $s7  # barposition = barposition + barvelocity

	slt $t3, $s6, $s5  # if barposition < halfbarwidth set $t3 = 1
	beq $t3, $0, in_elif
	# if here, $t3 was 1, so barposition < halfbarwidth
	add $s6, $0, $s5    # barposition = halfbarwidth
	addi $s7, $0, 0     # barvelocity = 0
	j end_of_if
in_elif:
	# t3 was zero, so barposition >= halfbarwidth
	# need to check whether barposition > screenwidth - halfbarwidth
	add $t3, $s0, $s5  # t3 gets screenwidth - halfbarwidth
	slt $t4, $t3, $s6   # t4 gets 1 if screenwidth - halfbarwidth < barposition
	beq $t4, $0, end_of_if  # if t4 = 0, then screendwidth - halfbarwidth >= barposition, so we don't do anything
	# if here, screenwidth - halfbarwidth < barposition
	addi $s6, $t3, 0   # barposition = screenwidth - halfbarwidth
	addi $s7, $0, 0    # barvelocity = 0

end_of_if:	

	bne $s1, $s0, next_if
	addi $s3, $0, -1   # ballvx = -1
next_if:
	bne $s1, $0, next_if_2
	addi $s3, $0, 1   #ballvx = 1

next_if_2:
	bne $s2, $0, next_if_3
	addi $s4, $0, 1  #ballvy = 1

next_if_3:
	addi $t5, $0, 200
	bne $s2, $t5, end_of_if2

	sub $t7, $s6, $s5  # t7 gets barposition - halfbarwidth
	add $t8, $s6, $s5  # t8 gets barposition + halfbarwidth
	
	slt $t9, $s1, $t7   # set t9 to 1 if ballx < barposition - halfbarwidth
	bne $t9, $0, endgame

	# if haven't ended game, check the other half of condition
	slt $t9, $t8, $s1   # set t9 to 1 if barposition + halfbarwidth < ballx
	bne $t9, $0, endgame

end_of_if2:	

	add $s1, $s1, $s3  # ballx += ballvx
	add $s2, $s2, $s4  # bally += ballvy
	j loop	

endgame:	
j endgame