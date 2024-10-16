.text

# გვაქვს 2 რიცხვი N და M. 1 <= N, M <= 1000
# უნდა დავბეჭდოთ ყველა მარტივი რიცხვი რომელიც არის [N, M] შუალედში

addi x19, x0, 50    # N
addi x20, x0, 200  # M

addi x12, x0, 0 # ramdeni martivi ricxvi gvaqvs jer

addi x13, x0, 2 # current number

BEGIN_LOOP:
    bgt x13, x20, END # i < M
    
    addi x14, zero, 0 # meramdene prime-s vamowmebt exla
    CHECK_PRIME_LOOP:
        bge x14, x12, IS_PRIME # j < prime_ricxvebis_raodenoba
        # sp[0], sp[1],  ... sp[j]. ((char *) sp) + j * sizeof(int) 
        addi x15, x14, 0
        addi x16, x0, 4
        mul x15, x15, x16 # x15 = j * sizeof(int)
        add x15, sp, x15 # x15 = &sp[j]
        lw x15, 0(x15) # x15 = *x15
        
        rem x16, x13, x15
        beqz x16, CHECK_PRIME_LOOP_END # current_number % current_prime == 0
        
        addi x14, x14, 1
        j CHECK_PRIME_LOOP
    IS_PRIME:
        addi x12, x12, 1
        addi sp, sp, -4
        sw x13, 0(sp)
        
        blt x13, x19, CHECK_PRIME_LOOP_END
        addi x10, x0, 1
        addi x11, x13, 0
        ecall
        
        addi x11, x0, 0x20
        addi x10, x0, 11
        ecall
    CHECK_PRIME_LOOP_END:
    addi x13, x13, 1
    j BEGIN_LOOP
END:
addi x10, x0, 10
ecall