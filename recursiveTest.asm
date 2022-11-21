main:
    addi $a0, $0, 100
    jal f
    addi $s0, $v0, 0
    j end

f:
    bne $a0, $0, fend
    addi $v0, $0, 0
    jr $ra
fend:
    addi $sp, $sp, -8
    sw $ra 0($sp)
    sw $s0 4($sp)
    addi $s0, $a0, 0
    addi $a0, $a0, -1
    jal f
    add $v0, $v0, $s0
    lw $s0 4($sp)
    lw $ra 0($sp)
    add $sp, $sp, 8
    jr $ra

end:
    j end