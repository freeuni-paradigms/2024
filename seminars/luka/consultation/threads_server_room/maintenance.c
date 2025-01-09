#include "maintenance.h"

#include "supervisor.h"

#include <pthread.h>
#include <semaphore.h>
#include <stdbool.h>
#include <string.h>

typedef struct s_HardwareCommonArgs {
  int             total_number_of_tables;
  int             workers_in_room;
  bool           *table_busy;
  pthread_mutex_t lock;
} HardwareCommonArgs;

typedef struct s_HardwareArgs {
  int                 hardware_member_id;
  HardwareCommonArgs *commonArgs;
  SoftwareCommonArgs *sw_args;
} HardwareArgs;

void* HardwareWorker(void *args) {
  HardwareArgs *hw_args = (HardwareArgs *) args;

  HardwareWorkerEnterRoom(hw_args->hardware_member_id);

  while (0xDEADBEEF) {
    pthread_mutex_lock(&hw_args->commonArgs->lock);
    int i;
    
    for (i = 0; i < hw_args->commonArgs->total_number_of_tables; i++) {
      if (!hw_args->commonArgs->table_busy[i]) {
        hw_args->commonArgs->table_busy[i] = true;
        pthread_mutex_unlock(&hw_args->commonArgs->lock);
        break;
      }
    }

    if (i >= hw_args->commonArgs->total_number_of_tables) {
      hw_args->commonArgs->workers_in_room--;
      
      if (hw_args->commonArgs->workers_in_room == 0) {
        AllComputerHardwareIsSetUp(hw_args->hardware_member_id);
      }

      HardwareWorkerLeaveRoom(hw_args->hardware_member_id);
      pthread_mutex_unlock(&hw_args->commonArgs->lock);
      // kill myself
      return NULL;
    }

    // mushaoba
    HardwareWorkerStartSettingUpComputer(hw_args->hardware_member_id, i);
    HardwareWorkerFinishedSettingUpComputer(hw_args->hardware_member_id, i);

    pthread_mutex_lock(&hw_args->sw_args->lock);
    hw_args->sw_args->tables_ready[i] = true;
    pthread_mutex_unlock(&hw_args->sw_args->lock);
    sem_post(&hw_args->sw_args->hw_ready_computers);
    // signal software to table i
  }
}

void *SoftwareWorker(void *args) {
  SoftwareArgs *sw_args = (SoftwareArgs *) args;

  SoftwareWorkerEnterRoom(sw_args->id);

  while (0xDEADBEEF) {
    sem_wait(&sw_args->commonArgs->hw_ready_computers);
    pthread_mutex_lock(&sw_args->commonArgs->lock);
    
    int i;
    for (i = 0; i < sw_args->commonArgs->total_number_of_tables; i++) {
      if (sw_args->commonArgs->tables_ready[i]) {
        sw_args->commonArgs->tables_ready[i] = false;
        pthread_mutex_unlock(&sw_args->commonArgs->lock);

        SoftwareWorkerStartInstallingSoftware(sw_args->id, i);
        SoftwareWorkerFinishedInstallingSoftware(sw_args->id, i);
        
        pthread_mutex_lock(&sw_args->commonArgs->lock);
        sw_args->commonArgs->computers_ready++;
        break;
      }
    }

    if (sw_args->commonArgs->computers_ready == sw_args->commonArgs->total_number_of_tables) {
      sw_args->commonArgs->workers_in_room--;
      
      if (sw_args->commonArgs->workers_in_room == 0) {
        AllComputerSoftwareIsInstalled(sw_args->id);
      }
      SoftwareWorkerLeaveRoom(sw_args->id);
      
      sem_post(&sw_args->commonArgs->hw_ready_computers);
      pthread_mutex_unlock(&sw_args->commonArgs->lock);
      return NULL;  
    }

    pthread_mutex_unlock(&sw_args->commonArgs->lock);
  }
}

typedef struct s_SoftwareCommonArgs {
  int             total_number_of_tables;
  int             computers_ready;
  int             workers_in_room;
  bool           *tables_ready;
  pthread_mutex_t lock;
  sem_t           hw_ready_computers;
} SoftwareCommonArgs;

typedef struct s_SoftwareArgs {
  int                 id;
  SoftwareCommonArgs *commonArgs;
} SoftwareArgs;
 
void SetUpServerRoom(int num_tables, int hardware_team_size,
		     int software_team_size) {
  
  /* HW INIT */
  pthread_t    *hardware_threads = malloc(hardware_team_size * sizeof(pthread_t));
  HardwareArgs *hardware_args    = malloc(hardware_team_size * sizeof(HardwareArgs));

  HardwareCommonArgs common_hw_args = {
    .total_number_of_tables = num_tables,
    .workers_in_room        = hardware_team_size,
  };

  pthread_mutex_init(&common_hw_args.lock, NULL);

  common_hw_args.table_busy = malloc(sizeof(bool) * num_tables);
  memset(common_hw_args.table_busy, 0, sizeof(bool) * num_tables);

  /* SW INIT */

  pthread_t    *software_threads = malloc(software_team_size * sizeof(pthread_t));
  SoftwareArgs *software_args    = malloc(software_team_size * sizeof(SoftwareArgs));

  SoftwareCommonArgs common_sw_args = {
    .hw_ready_computers = 0,
    .workers_in_room    = software_team_size,
  };

  common_sw_args.tables_ready = malloc(num_tables * sizeof(bool));
  memset(common_sw_args.tables_ready, 0, sizeof(bool) * num_tables);

  pthread_mutex_init(&common_sw_args.lock, NULL);
  sem_init(&common_sw_args.hw_ready_computers, 0, 0);

  /* START HW TEAM */
  for (int i = 0; i < hardware_team_size; i++) {
    hardware_args[i].hardware_member_id = i;
    hardware_args[i].commonArgs = &common_hw_args;
    hardware_args[i].sw_args = &common_sw_args;
    pthread_create(&hardware_threads[i], NULL, HardwareWorker, &hardware_args[i]);
  }

  for (int i = 0; i < software_team_size; i++) {
    software_args[i].id = i;
    software_args[i].commonArgs = &common_sw_args;

    pthread_create(&hardware_threads[i], NULL, SoftwareWorker, &software_args[i]);
  }

  free(hardware_threads);
  free(hardware_args);
  free(common_hw_args.table_busy);

  pthread_mutex_destroy(&common_hw_args.lock);
}
