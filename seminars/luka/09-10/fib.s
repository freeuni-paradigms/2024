.text


# int fib(int n)
# {
#     if (n <= 1) {
#         return n;
#     }
#     int y = fib(n - 1);
#     int z = fib(n - 2);
#     return y + z;
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
    li x10, 5
    sw  x10, 4(sp)
    sw ra, 0(sp)
    
    call fib
    
    lw ra, 0(sp)
    addi sp, sp, 8
    sw a0, 0(sp)
    
    li x10, 1
    lw x11, 0(sp)
    ecall
    
    li x10, 10
    ecall
    
    
    fib:
        addi sp, sp, -8
        lw x10, 12(sp)
        li x11, 1
        BGT x10, x11, rec
        mv a0, x10
        j end
        
   rec:
        
    
   end:
       addi sp, sp, 8
       ret
   
    
   