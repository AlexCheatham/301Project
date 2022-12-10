#In file syscall.asm
syscall:
beq $v0, $0, main
addi $k1, $0, 10
beq $v0, $k1, syscall10
addi $k1, $0, 12
beq $v0, $k1, syscall12
addi $k1, $0, 80
beq $v0, $k1, syscall80

syscall10:
j syscall10
jr $k0

syscall12:
lw $k1 16($0) #0x0010 = 16 = keyboard ready
beq $k1, $0, syscall12end #if keypress take value from keyboard, otherwise return 0, no keypress available k1 will be 0
lw $v0, 20($0) #0x0014 = 20 = keyboard character
jr $k0 #returns keypress value
syscall12end:
addi $v0, $0, 0
jr $k0 #returns 0

syscall80:
sw $a0, 32($0) #0x0020 = 32 = monitor x coordinate
sw $a1, 36($0) #0x0024 = 36 = monitor y coordinate
sw $a2, 40($0) #0x0028 = 40 = monitor color
sw $0, 44($0)  #0x002c = 44 = display pixel
jr $k0