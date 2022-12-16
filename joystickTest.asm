main:
loop:
addi $v0, $0, 20
syscall
addi $t0, $v0, 0 #t0 = x value
addi $t1, $v0, 0 #t1 = y value
srl $t0, $t0, 4
sll $t1, $t1, 28
srl $t1, $t1, 28
addi $v0, $0, 80
addi $a0, $t0, 0
addi $a1, $t1, 0
syscall
j loop