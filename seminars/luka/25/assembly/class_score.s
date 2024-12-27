.text
# CALLS MAIN FUNCTION; DO NOT REMOVE
call main


#####      SOLUTION         ######
# int ClassScore(Submission *s, int n)
ClassScore:
##### YOUR CODE STARTS HERE ######

#  int total_class_score = 0;
        addi sp, sp, -8
        sw x0, 4(sp)
        sw x0, 0(sp)
     
#  for (int i = 0; i < n; i++) {
LOOP_START:
        lw x10, 12(sp) # n
        lw x11, 0(sp) # i
        bge x11, x10, END
#    if (s[i].late_by_hours < 5) {

        lw x12, 8(sp) # Submission* s
        addi x13, x0, 7
        mul x13, x11, x13 # x13 = i * sizeof(Submission)
        add x12, x12, x13 # x12 = &s[i]
        # addi x13, x12, 1  # x13 = &s[i].late_by_hours
        lh x14, 1(x12) # x14 = s[i].late_by_hours

        lw x16, 4(sp)  # total_class_score
        lw x15, 3(x12) # s[i].score
        addi x18, x0, 5
        blt x14, x18, FULL_SCORE
#      total_class_score += (s[i].score + 1) / 2;
        addi x15, x15, 1
        addi x17, x0, 2
        div x15, x15, x17
FULL_SCORE:
#      total_class_score += s[i].score;
        add x16, x16, x15
        sw x16, 4(sp) 

addi x11, x11, 1 # i++
sw x11, 0(sp)
j LOOP_START
END:
lw x10, 4(sp)
addi sp, sp, 8
ret
#  return total_class_score;

#######  YOUR CODE ENDS HERE  ######





### TEST CODE BELOW ###
### TEST CODE BELOW ###
### gcc generated test code. not meant to be read: ###


call_ClassScore:
        addi    sp,sp,-32
        sw      ra,28(sp)
        sw      s0,24(sp)
        addi    s0,sp,32
        sw      a0,-20(s0)
        sw      a1,-24(s0)
        lw      a1,-24(s0)
        lw      a0,-20(s0)
        addi    sp,sp,-32
        sw      a0,0(sp)
        sw      a1,4(sp)
        call    ClassScore
        addi    sp,sp,32
        mv      a5,a0
        mv      a0,a5
        lw      ra,28(sp)
        lw      s0,24(sp)
        addi    sp,sp,32
        jr      ra
ecall:
        addi    sp,sp,-32
        sw      ra,28(sp)
        sw      s0,24(sp)
        addi    s0,sp,32
        sw      a0,-20(s0)
        sw      a1,-24(s0)
        lw      a5,-20(s0)
        mv      a0,a5
        lw      a5,-24(s0)
        mv      a1,a5
        ecall
        nop
        lw      ra,28(sp)
        lw      s0,24(sp)
        addi    sp,sp,32
        jr      ra
.data
in0:
        .byte   1
        .byte   1,0
        .byte   57,48,0,0
in1:
        .byte   1
        .byte   100,0
        .byte   57,48,0,0
in2:
        .byte   1
        .byte   0,0
        .byte   1,0,0,0
        .byte   2
        .byte   1,0
        .byte   2,0,0,0
        .byte   3
        .byte   2,0
        .byte   3,0,0,0
        .byte   3
        .byte   4,0
        .byte   0,0,0,0
in3:
        .byte   1
        .byte   5,0
        .byte   10,0,0,0
        .byte   2
        .byte   5,0
        .byte   21,0,0,0
        .byte   3
        .byte   5,0
        .byte   30,0,0,0
        .byte   6
        .byte   5,0
        .byte   40,0,0,0
in4:
        .byte   1
        .byte   1,0
        .byte   5,0,0,0
        .byte   2
        .byte   2,0
        .byte   8,0,0,0
        .byte   3
        .byte   4,0
        .byte   12,0,0,0
        .byte   6
        .byte   5,0
        .byte   232,3,0,0
        .byte   5
        .byte   6,0
        .byte   249,1,0,0
        .byte   4
        .byte   7,0
        .byte   123,0,0,0
        .byte   4
        .byte   8,0
        .byte   0,0,0,0
in5:
        .byte   1
        .byte   1,0
        .byte   242,3,0,0
        .byte   2
        .byte   8,0
        .byte   250,1,0,0
        .byte   3
        .byte   4,0
        .byte   13,0,0,0
        .byte   6
        .byte   5,0
        .byte   232,3,0,0
        .byte   5
        .byte   2,0
        .byte   0,0,0,0
        .byte   4
        .byte   1,0
        .byte   1,0,0,0
in6:
        .byte   1
        .byte   4,0
        .byte   242,3,0,0
        .byte   2
        .byte   4,0
        .byte   250,1,0,0
        .byte   3
        .byte   4,0
        .byte   13,0,0,0
        .byte   4
        .byte   5,0
        .byte   232,3,0,0
        .byte   5
        .byte   5,0
        .byte   11,0,0,0
        .byte   6
        .byte   5,0
        .byte   21,0,0,0
        .byte   7
        .byte   16,0
        .byte   20,0,0,0
        .byte   8
        .byte   5,0
        .byte   12,0,0,0
        .byte   9
        .byte   5,0
        .byte   210,4,0,0
.LC0:
        .byte   91,84,69,83,84,32,35,49,93,32,114,101,115,117,108,116,61,0
        .byte   0
.LC1:
        .byte   91,84,69,83,84,32,35,50,93,32,114,101,115,117,108,116,61,0
        .byte   0
.LC2:
        .byte   91,84,69,83,84,32,35,51,93,32,114,101,115,117,108,116,61,0
        .byte   0
.LC3:
        .byte   91,84,69,83,84,32,35,52,93,32,114,101,115,117,108,116,61,0
        .byte   0
.LC4:
        .byte   91,84,69,83,84,32,35,53,93,32,114,101,115,117,108,116,61,0
        .byte   0
.LC5:
        .byte   91,84,69,83,84,32,35,54,93,32,114,101,115,117,108,116,61,0
        .byte   0
.LC6:
        .byte   91,84,69,83,84,32,35,55,93,32,114,101,115,117,108,116,61,0
        .byte   0
.text
main:
        addi    sp,sp,-32
        sw      ra,28(sp)
        sw      s0,24(sp)
        addi    s0,sp,32
        sw      a0,-20(s0)
        sw      a1,-24(s0)
        la      a5,.LC0
        mv      a1,a5
        li      a0,4
        call    ecall
        li      a1,1
        la      a0,in0
        call    call_ClassScore
        mv      a4,a0
        li      a5,-12288
        addi    a5,a5,-57
        add     a5,a4,a5
        seqz    a5,a5
        andi    a5,a5,0xff
        mv      a1,a5
        li      a0,1
        call    ecall
        li      a1,10
        li      a0,11
        call    ecall
        la      a5,.LC1
        mv      a1,a5
        li      a0,4
        call    ecall
        li      a1,1
        la      a0,in1
        call    call_ClassScore
        mv      a4,a0
        li      a5,-8192
        addi    a5,a5,2019
        add     a5,a4,a5
        seqz    a5,a5
        andi    a5,a5,0xff
        mv      a1,a5
        li      a0,1
        call    ecall
        li      a1,10
        li      a0,11
        call    ecall
        la      a5,.LC2
        mv      a1,a5
        li      a0,4
        call    ecall
        li      a1,4
        la      a0,in2
        call    call_ClassScore
        mv      a5,a0
        addi    a5,a5,-6
        seqz    a5,a5
        andi    a5,a5,0xff
        mv      a1,a5
        li      a0,1
        call    ecall
        li      a1,10
        li      a0,11
        call    ecall
        la      a5,.LC3
        mv      a1,a5
        li      a0,4
        call    ecall
        li      a1,4
        la      a0,in3
        call    call_ClassScore
        mv      a5,a0
        addi    a5,a5,-51
        seqz    a5,a5
        andi    a5,a5,0xff
        mv      a1,a5
        li      a0,1
        call    ecall
        li      a1,10
        li      a0,11
        call    ecall
        la      a5,.LC4
        mv      a1,a5
        li      a0,4
        call    ecall
        li      a1,7
        la      a0,in4
        call    call_ClassScore
        mv      a5,a0
        addi    a5,a5,-840
        seqz    a5,a5
        andi    a5,a5,0xff
        mv      a1,a5
        li      a0,1
        call    ecall
        li      a1,10
        li      a0,11
        call    ecall
        la      a5,.LC5
        mv      a1,a5
        li      a0,4
        call    ecall
        li      a1,6
        la      a0,in5
        call    call_ClassScore
        mv      a5,a0
        addi    a5,a5,-1777
        seqz    a5,a5
        andi    a5,a5,0xff
        mv      a1,a5
        li      a0,1
        call    ecall
        li      a1,10
        li      a0,11
        call    ecall
        la      a5,.LC6
        mv      a1,a5
        li      a0,4
        call    ecall
        li      a1,9
        la      a0,in6
        call    call_ClassScore
        mv      a4,a0
        li      a5,-4096
        addi    a5,a5,1417
        add     a5,a4,a5
        seqz    a5,a5
        andi    a5,a5,0xff
        mv      a1,a5
        li      a0,1
        call    ecall
        li      a1,10
        li      a0,11
        call    ecall
        li      a1,0
        li      a0,10
        call    ecall
        li      a5,0
        mv      a0,a5
        lw      ra,28(sp)
        lw      s0,24(sp)
        addi    sp,sp,32
        jr      ra

