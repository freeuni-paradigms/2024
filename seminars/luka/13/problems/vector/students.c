#include "students.h"

#include <stdlib.h>
#include <string.h>

#include "vector.h"

void StudentFree(void* elem) {
    Student *s = elem;
    if (s->name) {
        free(s->name) ;
    }
}

void StudentVectorInit(StudentVector* v) {
    VectorInit(v, sizeof(Student), StudentFree);
}

void StudentVectorDestroy(StudentVector* v) {
    VectorDestroy(v);
}

void StudentVectorAppend(StudentVector* v, Student* elem) {
    VectorAppend(v, elem);
}

void StudentVectorInsert(StudentVector* v, int index, Student* elem) {
    VectorInsert(v, index, elem);
}

void StudentVectorOverwrite(StudentVector* v, int index, Student* elem) {
    VectorOverwrite(v, index, elem);
}

Student* StudentVectorGet(StudentVector* v, int index) {
    return VectorGet(v, index);
}

void StudentVectorRemove(StudentVector* v, int index, Student* elem) {
    VectorRemove(v, index, elem);
}

int StudentVectorSize(StudentVector* v) {
    return VectorSize(v);
}

StudentVector StudentVectorCloneRange(StudentVector* v, int start, int end) {
    StudentVector mv;

    StudentVectorInit(&mv);

    for (int i = start; i <= end; i++) {
        Student st = *(Student *)VectorGet(v, i);
        st.name = strdup(st.name);

        VectorAppend(&mv, &st);
    }

    return mv;
}
