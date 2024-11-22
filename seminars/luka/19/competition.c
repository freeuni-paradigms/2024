#include "competition.h"

#include <stdlib.h>

#include "robot.h"

void CompetitionInit(Competition* comp) {
  comp->num_total_robots = 0;
  comp->robots_left = 0;
  comp->competition_ended = false;
  comp->rptr = comp->last_robot = comp->robots;
  memset(comp->robots, 0, sizeof(comp->robots));
  pthread_mutex_init(&comp->lk, 0);
  sem_init(&comp->all_fights_finished, 0, 0);
  pthread_cond_init(&comp->cnd, 0);
}

typedef struct {
  Competition *comp;
  Robot *robot_x;
  Robot *robot_y;
} RobotFightArgs;

void *RobotFight(void *args) {
  RobotFightArgs *fight = (RobotFightArgs *) args;

  Robot *winner = fight->robot_y;

  if (RobotFightWith(fight->robot_x, fight->robot_y)) {
    winner = fight->robot_x;
  }

  pthread_mutex_lock(&fight->comp->lk);
  *fight->comp->last_robot = winner;
  fight->comp->last_robot++;
  fight->comp->num_total_robots--;
  pthread_cond_signal(&fight->comp->cnd);
  pthread_mutex_unlock(&fight->comp->lk);
  free(fight);
}

void *ManagerThread(void *args) {
  Competition *comp = (Competition *) args;
  while (true) {
    pthread_mutex_lock(&comp->lk);

    // აქ ამათ შორის || მეწერა, && უნდა ყოფილიყო
    while (!(comp->competition_ended && comp->num_total_robots <= 1) && comp->last_robot - comp->rptr < 2) {
      pthread_cond_wait(&comp->cnd, &comp->lk);
    }

    if (comp->competition_ended && comp->num_total_robots <= 1) {
      comp->winner = *comp->rptr;
      pthread_mutex_unlock(&comp->lk);
      sem_post(&comp->all_fights_finished);
      return 0;
    }

    RobotFightArgs *args = malloc(sizeof(RobotFightArgs));
    args->comp = comp;    
    args->robot_x = *comp->rptr;
    comp->rptr++;
    args->robot_y = *comp->rptr;
    comp->rptr++;
    pthread_t thread;
    pthread_create(&thread, 0, RobotFight, args);
    pthread_detach(thread);
    pthread_mutex_unlock(&comp->lk);
  }
}

void CompetitionStart(Competition* comp) {
  pthread_t thread;
  pthread_create(&thread, 0, ManagerThread, comp);  
  pthread_detach(thread);
}

const Robot* CompetitionStop(Competition* comp) {
  pthread_mutex_lock(&comp->lk);
  comp->competition_ended = true;
  pthread_cond_signal(&comp->cnd);
  pthread_mutex_unlock(&comp->lk);

  sem_wait(&comp->all_fights_finished);
  return comp->winner;
}

bool CompetitionAddParticipant(Competition* comp, const Robot* robot) {
  pthread_mutex_lock(&comp->lk);

  if (comp->competition_ended) {
    pthread_mutex_unlock(&comp->lk);
    return false;
  }

  comp->num_total_robots++;
  *comp->last_robot = (Robot *) robot;
  comp->last_robot++;
  pthread_mutex_unlock(&comp->lk);
  pthread_cond_signal(&comp->cnd);
  return true;
}
