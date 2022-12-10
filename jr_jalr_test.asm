addi $t0, $0, 16 #address of instruction 4, addi 100 to t2
jalr $t1, $t0 #jump to instruction 4, next instruction stored in t1
addi $t0, $0, 112
j end #jump to end of program once 112 is added to t0
addi $t2, $0, 100
jr $t1 #once t2 has 100 added, jump back to value in t1 and continue program
end:
j end