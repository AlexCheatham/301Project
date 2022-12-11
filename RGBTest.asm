main:

    #Mixing palette
    addi $t0, $0, 255 #blue
    sll $t1, $t0, 8  #green
    sll $t2, $t0, 16 #red

    addi $a0, $0, 0 #x coordinate
    addi $a1, $0, 0 #y coordinate
    addi $a2, $t0, 0 #color
    addi $v0, $0, 80 #moniter syscall
    syscall


loop:
    addi $a0, $a0, 1
    addi $a1, $a0, 1
    addi $a2, $t1, 0
    addi $v0, $0, 80 #moniter syscall
    syscall

    addi $a0, $a0, 1
    addi $a1, $a0, 1
    addi $a2, $t2, 0
    addi $v0, $0, 80 #moniter syscall
    syscall

    addi $a0, $a0, 1
    addi $a1, $a0, 1;
    addi $a2, $t0, 0
    addi $v0, $0, 80 #moniter syscall
    syscall
    j loop