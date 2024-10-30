#ifndef PARADIGMS_STUDENTS_
#define PARADIGMS_STUDENTS_

#include "vector.h"

typedef struct {
  int year;
  char* name; // dynamically allocated
} Student;

typedef Vector StudentVector;

void StudentVectorInit(StudentVector* v);
void StudentVectorDestroy(StudentVector* v);
void StudentVectorAppend(StudentVector* v, Student* elem);
void StudentVectorInsert(StudentVector* v, int index, Student* elem);
void StudentVectorOverwrite(StudentVector* v, int index, Student* elem);
Student* StudentVectorGet(StudentVector* v, int index);
void StudentVectorRemove(StudentVector* v, int index, Student* elem);
int StudentVectorSize(StudentVector* v);
// New Method to implement
StudentVector StudentVectorCloneRange(StudentVector* v, int start, int end);


#endif // PARADIGMS_STUDENTS_
