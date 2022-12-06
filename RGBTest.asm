main:

    #Mixing palette
    addi $t0, $0, 255 #blue
    sll $t1, $t0, 8  #green
    sll $t2, $t0, 16 #red

    addi $s0, $0, 0 #x coordinate
    addi $s1, $0, 0 #y coordinate
    addi $s2, $0, 0 #color
    sw $s0, 32($0) #0x0020 = 32 = monitor x coordinate
    sw $s1, 36($0) #0x0024 = 36 = monitor y coordinate
    sw $t0, 40($0) #0x0028 = 40 = monitor color
    sw $0, 44($0)  #0x002c = 44 

loop:
    addi $s0, $s0, 1
    addi $s1, $s1, 1
    sw $s0, 32($0) #0x0020 = 32 = monitor x coordinate
    sw $s1, 36($0) #0x0024 = 36 = monitor y coordinate
    sw $t1, 40($0) #0x0028 = 40 = monitor color
    sw $0, 44($0)  #0x002c = 44

    addi $s0, $s0, 1
    addi $s1, $s1, 1
    sw $s0, 32($0) #0x0020 = 32 = monitor x coordinate
    sw $s1, 36($0) #0x0024 = 36 = monitor y coordinate
    sw $t2, 40($0) #0x0028 = 40 = monitor color
    sw $0, 44($0)  #0x002c = 44 

    addi $s0, $s0, 1
    addi $s1, $s1, 1
    sw $s0, 32($0) #0x0020 = 32 = monitor x coordinate
    sw $s1, 36($0) #0x0024 = 36 = monitor y coordinate
    sw $t0, 40($0) #0x0028 = 40 = monitor color
    sw $0, 44($0)  #0x002c = 44 
    j loop