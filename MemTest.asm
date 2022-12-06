main:
    addi $sp, $sp, -4   #free space on the stack
    addi $t0, $t0, 123 #store 1234 into t0
    sw $t0, 0($sp)    #store t0 onto the stack
    lw $t1, 0($sp)    #store value from stack into t1

end:
    j end