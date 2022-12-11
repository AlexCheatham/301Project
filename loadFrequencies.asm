#loads C major scale into each register
#storing frequency of A
main:
addi $a0, $0, 440
addi $a1, $0, 45
addi $a2, $0, 24
addi $v0, $0, 15
syscall
addi $t0, $t0, 1
j main