#include <stdbool.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

typedef struct {
  int num_clients;
  int line_num;
  sem_t* line_lock;
  sem_t* line[10];
  sem_t* pay;
  sem_t* change;
} CashierArgs;

typedef struct {
  int num_total;
  bool approved;
  sem_t* lock;
  sem_t* request;
  sem_t* ready;
} ManagerArgs;

bool Inspect() {
  // sleep(rand() % 3);
  return rand() % 3 == 0;
}

void* Manager(void* args) {
  ManagerArgs* a = args;
  int num_approved = 0;
  int num_inspected = 0;
  while (num_approved <= a->num_total) {
	sem_wait(a->request);
	a->approved = Inspect();
	if (a->approved) {
	  num_approved++;
	}
	sem_post(a->ready);
	num_inspected++;
  }
  printf("MANAGER num_approved=%d num_inspected=%d\n", num_approved, num_inspected);
  return NULL;
}

typedef struct {
  int id;
  ManagerArgs* mgr;
  sem_t* done;
} WorkerArgs;

void Make(int id) {
  printf("WORKER %d: making ice cream\n", id);
  // sleep(rand() % 3);
  printf("WORKER %d: DONE making ice cream\n", id);
}

void* Worker(void* args) {
  WorkerArgs* a = args;
  while (true) {
	Make(a->id);
	sem_wait(a->mgr->lock);
	sem_post(a->mgr->request);
	sem_wait(a->mgr->ready);
	bool ok = a->mgr->approved;
	sem_post(a->mgr->lock);
	if (ok) {
	  break;
	}
  }
  sem_post(a->done);
  printf("WORKER %d: done\n", a->id);
  return NULL;
}

typedef struct {
  int id;
  int num_cones;
  sem_t* done;
  CashierArgs* cashier;
} ClientArgs;

void Pay(int id) {
  printf("CLIENT %d: paying\n", id);
  // sleep(rand() % 2);
  printf("CLIENT %d: paid\n", id);
}

void* Client(void* args) {
  ClientArgs* a = args;
  printf("CLIENT %d: num_cones %d\n", a->id, a->num_cones);
  for (int i = 0; i < a->num_cones; i++) {
	sem_wait(a->done);
  }
  // Cashier
  sem_wait(a->cashier->line_lock);
  int n = a->cashier->line_num;
  a->cashier->line_num++;
  sem_post(a->cashier->line_lock);
  printf("CLIENT %d: line number %d\n", a->id, n);
  sem_wait(a->cashier->line[n]);
  sem_post(a->cashier->pay);
  Pay(a->id);
  sem_wait(a->cashier->change);
  printf("CLIENT %d: done\n", a->id);
  return NULL;
}

void Change() {
  // sleep(rand() % 4);
}

void* Cashier(void* args) {
  CashierArgs* a = args;
  for (int i = 0; i < a->num_clients; i++) {
	sem_post(a->line[i]);
	printf("CASHIER: serving %d\n", i);
	sem_wait(a->pay);
	Change();
	sem_post(a->change);
  }
  printf("CASHIER: done\n");
  return NULL;
}

sem_t* SemInit(char* name, int val) {
  sem_unlink(name);
  sem_t* ret = sem_open(name, O_CREAT | O_EXCL, 0, val);
  if (ret == SEM_FAILED) {
	exit(1);
	return NULL;
  }
  return ret;
}

void SemDestroy(sem_t* s, char* name) {
  printf("CLOSING %s\n", name);
  // sem_close(s);
  printf("%s\n", name);
  sem_unlink(name);
  printf("UNLINKED\n");
}

int main(int argc, char** argv) {
  pthread_t manager;
  pthread_t cashier;
  pthread_t clients[10];
  pthread_t workers[40];
  ClientArgs client_args[10];
  int num_total = 0;
  CashierArgs cashier_args;
  WorkerArgs worker_args[40];
  int worker_count = 0;
  ManagerArgs manager_args;
  for (int i = 0; i < 10; i++) {
	client_args[i].num_cones = rand() % 4 + 1;
	num_total += client_args[i].num_cones;
	char sem_id[100];
	sprintf(sem_id, "/tmp/client/%d/done", i);
	client_args[i].id = i;
	client_args[i].done = SemInit(sem_id, 0);
	client_args[i].cashier = &cashier_args;
	pthread_create(&clients[i], NULL, Client, &client_args[i]);
	for (int j = 0; j < client_args[i].num_cones; j++) {
	  worker_args[worker_count].id = worker_count;
	  worker_args[worker_count].mgr = &manager_args;
	  worker_args[worker_count].done = client_args[i].done;
	  pthread_create(&workers[worker_count], NULL, Worker, &worker_args[worker_count]);
	  worker_count++;
	}
  }
  manager_args.num_total = num_total;
  manager_args.lock = SemInit("/tmp/manager/lock", 1);
  manager_args.request = SemInit("/tmp/manager/request", 0);
  manager_args.ready = SemInit("/tmp/manager/ready", 0);
  pthread_create(&manager, NULL, Manager, &manager_args);
  cashier_args.num_clients = 10;
  cashier_args.line_num = 0;
  cashier_args.line_lock = SemInit("/tmp/cashier/line_lock", 1);
  cashier_args.pay = SemInit("/tmp/cashier/pay", 0);
  cashier_args.change = SemInit("/tmp/cashier/change", 0);
  for (int i = 0; i < 0; i++) {
	char line_id[100];
	sprintf(line_id, "/tmp/cashier/line/%d", i);
	cashier_args.line[i] = SemInit(line_id, 0);
  }
  pthread_create(&cashier, NULL, Cashier, &cashier_args);
  pthread_join(cashier, NULL);
  printf("ALL DONE\n");
  SemDestroy(manager_args.lock, "/tmp/manager/lock");
  SemDestroy(manager_args.request, "/tmp/manager/request");
  SemDestroy(manager_args.ready, "/tmp/manager/ready");
    printf("YOOO\n");
  for (int i = 0; i < 10; i++) {
	char sem_id[100];
	sprintf(sem_id, "/tmp/client/%d/done", i);
	SemDestroy(client_args[i].done, sem_id);
  }
    printf("YOOO\n");
  SemDestroy(cashier_args.line_lock, "/tmp/cashier/line_lock");
  SemDestroy(cashier_args.pay, "/tmp/cashier/pay");
  SemDestroy(cashier_args.change, "/tmp/cashier/change");
    printf("YOOO\n");
  for (int i = 0; i < 0; i++) {
	char line_id[100];
	sprintf(line_id, "/tmp/cashier/line/%d", i);
	SemDestroy(cashier_args.line[i], line_id);
  }
  printf("YOOO\n");
  return 0;
}
