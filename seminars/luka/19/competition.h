#ifndef PARADIGMS_ROBOTS_COMPETITION_H_
#define PARADIGMS_ROBOTS_COMPETITION_H_

#include <stdbool.h>
#include <pthread.h>
#include <semaphore.h>
#include <string.h>
#include "robot.h"

typedef struct {
  int num_total_robots;
  int robots_left;
  bool competition_ended;
  Robot *robots[2005];
  Robot **rptr;
  Robot **last_robot;


  pthread_mutex_t lk;
  pthread_cond_t cnd;
  Robot *winner;
  sem_t all_fights_finished;
} Competition;

// უკეთებს შეჯიბრს ინიციალიზაციას.
void CompetitionInit(Competition* comp);
// უნდა გაუშვას შეჯიბრის მენეჯმენტისთვის მთავარი ნაკადი.
void CompetitionStart(Competition* comp);
// უნდა აკრძალოს შეჯიბრში ახალი მონაწილეების დამატება,
// დაელოდოს უკვე დამატებულ მონაწილეებს შორის გამარჯვებულს,
// და დააბრუნოს იგი.
const Robot* CompetitionStop(Competition* comp);
// აბრუნებს true თუ რობოტი წარმატებით დაემატა შეჯიბრში,
// და false წინააღმდეგ შემთხვევაში.
bool CompetitionAddParticipant(Competition* comp, const Robot* robot);

#endif // PARADIGMS_ROBOTS_COMPETITION_H_
