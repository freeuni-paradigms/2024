.text


# int fib(int n)
# {
#     if (n <= 1) {
#         return n;
#     }
#     int x = fib(n - 1);
#     int y = fib(n - 2);
#     return x + y
# }
#
# int main()
# {
#     int x = fib(5);
#     printf("%d\n", x);
#     return 0;
# }

main:
    addi sp, sp, -4

    addi sp, sp, -8
    li x10, 10
    sw  x10, 4(sp)
    sw ra, 0(sp)

    call fib

    lw ra, 0(sp)    # gavaqrot argumentebi
    addi sp, sp, 8
    sw a0, 0(sp)
    
    li x10, 1       # davbechdot x
    lw x11, 0(sp)
    ecall
    
    addi sp, sp, 4  # gavaqrot x

    li x10, 10
    ecall

    fib:
        addi sp, sp, -8 
        lw x10, 12(sp)
        li x11, 1
        BGT x10, x11, rec
        mv a0, x10 # addi a0, x10, 0
        j end

   rec:
        lw x12, 12(sp)
        addi x12, x12, -1 # x12 = n - 1       
        addi sp, sp, -8
        sw x12, 4(sp)
        sw ra, 0(sp) 
        call fib
        lw ra, 0(sp)
        addi sp, sp, 8
        sw a0, 4(sp)   
        
        
        lw x12, 12(sp)
        addi x12, x12, -2
        addi sp, sp, -8
        sw x12, 4(sp)
        sw ra, 0(sp)
        call fib
        lw ra, 0(sp)
        addi sp, sp, 8
        sw a0, 0(sp)
        
        lw a0, 0(sp)
        lw a1, 4(sp)
        add a0, a0, a1
        
   end:
       addi sp, sp, 8
       ret
