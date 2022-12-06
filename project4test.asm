loop:
    lw $t0, 16($0) #0x0010 = 16 = keyboard ready
    beq $t0, $0, loop
    lw $s1, 20($0) #0x0014 = 20 = keyboard character
end:
    j end