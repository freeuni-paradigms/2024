#include "helper.h"

#include <stdbool.h>
#include <pthread.h>
#include <semaphore.h>

#define MAX_NUM_TEACHERS 10
#define MAX_NUM_STUDENTS 100

sem_t teachers_done;
sem_t students_done;
int teacher_count;
bool all_students_done;

struct {
  sem_t teacher_signal;
  sem_t student_signal;
  int  student_id;
  bool set_score;
  bool available;
  pthread_mutex_t lock;
} TeacherArgs[MAX_NUM_TEACHERS];

void* Teacher(void* args) {
  int id = *(int*)args;
  // IMPLEMENT
  while (true) {
    sem_wait(&TeacherArgs[id].teacher_signal);
    if (all_students_done) {
      break;
    }
    TeacherArgs[id].set_score = TeacherEvaluateStudent(id, TeacherArgs[id].student_id);
    sem_post(&TeacherArgs[id].student_signal);
  }
  TeacherDone(id);
  sem_post(&teachers_done);
  return NULL;
}

void* Student(void* args) {
  int id = *(int*)args;

  while (true) {
    // record set
    StudentRecordSet(id);

    int i;
    for (i = 0;; i = (i + 1 ) % teacher_count) {
      pthread_mutex_lock(&TeacherArgs[i].lock);
      if (TeacherArgs[i].available) {
        break;
      }
      pthread_mutex_unlock(&TeacherArgs[i].lock);
    }

    TeacherArgs[i].available = false;
    TeacherArgs[i].student_id = id;
    pthread_mutex_unlock(&TeacherArgs[i].lock);
    sem_post(&TeacherArgs[i].teacher_signal);
    sem_wait(&TeacherArgs[i].student_signal);

    bool score = TeacherArgs[i].set_score;
    StudentWasEvaluatedByTeacher(id, i, score);
    pthread_mutex_lock(&TeacherArgs[i].lock);
    TeacherArgs[i].available = true;
    pthread_mutex_unlock(&TeacherArgs[i].lock);

    if (score) {
      break;
    }
  }

  StudentDone(id);
  sem_post(&students_done);  
  return NULL;
}

void StartSchool(int num_students, int num_teachers) {
  // IMPLEMENT: Initialize semaphores and mutexes if needed.
  int teacher_id[MAX_NUM_TEACHERS];
  int student_id[MAX_NUM_STUDENTS];
  teacher_count = num_teachers;
  all_students_done = false;
  sem_init(&teachers_done, 0, 0);
  sem_init(&students_done, 0, 0);

  for (int i = 0; i < num_teachers; ++i) {
    teacher_id[i] = i;
    TeacherArgs[i].available = true;
    sem_init(&TeacherArgs[i].student_signal, 0, 0);
    sem_init(&TeacherArgs[i].teacher_signal, 0, 0);
    pthread_mutex_init(&TeacherArgs[i].lock, 0);
    pthread_t tid;
    pthread_create(&tid, NULL, Teacher, &teacher_id[i]);
    pthread_detach(tid);
  }
  for (int i = 0; i < num_students; ++i) {
    student_id[i] = i;
    pthread_t tid;
    pthread_create(&tid, NULL, Student, &student_id[i]);
    pthread_detach(tid);
  }

  for (int i = 0; i < num_students; i++) {
    sem_wait(&students_done);
  }

  all_students_done = true;

  for (int i = 0; i < num_teachers; i++) {
    sem_post(&TeacherArgs[i].teacher_signal);
  }
  
  for (int i = 0; i < num_teachers; i++) {
    sem_wait(&teachers_done);
  }

  for (int i = 0; i < num_teachers; i++) {
    sem_destroy(&TeacherArgs[i].student_signal);
    sem_destroy(&TeacherArgs[i].teacher_signal);
    pthread_mutex_destroy(&TeacherArgs[i].lock);
  }
  
  sem_destroy(&students_done);
  sem_destroy(&teachers_done);

  // IMPLEMENT: Wait for the all students and teachers to finish.
  SchoolEnd();
}
