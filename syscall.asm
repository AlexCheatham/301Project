#In file syscall.asm
syscall:
beq $v0, $0, main
addi $k1, $0, 10
beq $v0, $k1, syscall10
addi $k1, $0, 12
beq $v0, $k1, syscall12
addi $k1, $0, 15
beq $v0, $k1, syscall15
addi $k1, $0, 20
beq $v0, $k1, syscall20
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

syscall15:
sw $a0, 48($0) #0x0030 = 48 = note frequency (hz)
sw $a1, 52($0) #0x0034 = 52 = volume
sw $a2, 56($0) #0x0038 = 56 = duty cycle
lw $0, 60($0)  #0x003c = 60 = have buzzer make a sound
jr $k0

syscall20:
sw $0, 64($0) #0x0040 = 64 = store x value
sw $0, 68($0) #0x0044 = 68 = store y value
lw $k1, 64($0)
sw $k1, 32($0) #load x value into k1 and store in in the moniter
lw $k1, 68($0)
sw $k1, 36($0) #load y value into k1 and store it in the moniter
sw $a0, 40($0) #load moniter color
sw $0, 44($0) #display pixel

syscall80:
sw $a0, 32($0) #0x0020 = 32 = monitor x coordinate
sw $a1, 36($0) #0x0024 = 36 = monitor y coordinate
sw $a2, 40($0) #0x0028 = 40 = monitor color
sw $0, 44($0)  #0x002c = 44 = display pixel
jr $k0
