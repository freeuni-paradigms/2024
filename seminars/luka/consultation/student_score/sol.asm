# short studentScore(Course *course, int studentIndex, int defaultScore)

# course sp              | sp + 12
# studentIndex sp + 4    | sp + 16
# defaultScore sp + 8    | sp + 20

studentScore:
addi sp, sp, -12
# int result = 0; sp+8
sw x0, 8(sp)
# short scores[4];

# if ((Student*)(course->students[studentIndex]->name)->addScores((void*)scores, 4) >= 40) {

## course->students[studentIndex]->name

lw x11, 12(sp)   # x11 = course
addi x11, x11, 8 # &course->students
lw x12, (0x11) # course->students

addi x13, x0, 4 # sizeof(Student *)
lw x14, 16(sp) # studentIndex
mul x13, x13, x14 # sizeof(Student *) * studentIndex
add x14, x12, x13 # course->students + sizeof(Student *) * studentIndex = &course->students[studentIndex]
lw x15, 0(x14) # course->students[studentIndex] = &course->students[studentIndex]->name
lw x16, 0(x15) # course->students[studentIndex]->name | ((Student*)(course->students[studentIndex]->name)
lw x17, 10(x16) # (Student*)(course->students[studentIndex]->name)->addScores

# addScores((void *)scores, 4)
addi sp, sp, -12
sw ra, 8(sp) 
addi x18, x0, 4
sw x18, 4(sp)
addi x18, sp, 12 # scores
sw x18, 0(sp)
jalr x17
lw ra, 8(sp)
addi sp, sp, 12

addi x19, x0, 40
blt x10, x19, ELSE_BLOCK
# result += scores[0] * course->credits;
lh x11, 0(sp) # scores[0]
lw x12, 12(sp) # course
lh x13, 4(x12) # course->credits
mul x14, x11, x13
lw x15, 8(sp)
add x15, x15, x14
sw x15, 8(sp)
j RETURN_STATEMENT
# } else { result = defaultScore;}
ELSE_BLOCK:
lw x11, 20(sp) # defaultScore
sw x11, 8(sp)
# return result;
RETURN_STATEMENT:
lw x10, 8(sp)
addi sp, sp, 12
ret