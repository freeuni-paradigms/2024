#include "students.h"

#include <stdlib.h>
#include <string.h>

#include "vector.h"

void StudentFree(void* elem) {
}

void StudentVectorInit(StudentVector* v) {
}

void StudentVectorDestroy(StudentVector* v) {
}

void StudentVectorAppend(StudentVector* v, Student* elem) {
}

void StudentVectorInsert(StudentVector* v, int index, Student* elem) {
}

void StudentVectorOverwrite(StudentVector* v, int index, Student* elem) {
}

Student* StudentVectorGet(StudentVector* v, int index) {
}

void StudentVectorRemove(StudentVector* v, int index, Student* elem) {
}

int StudentVectorSize(StudentVector* v) {
}

StudentVector StudentVectorCloneRange(StudentVector* v, int start, int end) {
}
