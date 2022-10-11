#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

void ChildProcess(void);
void ParentProcess(void);
int random_num();

void main(void) {
  pid_t pid, pid_2;
  int status;

  pid = fork(); // fork for first CHildProcess
  if (pid < 0) {
    exit(1);
  }
  else if (pid == 0){
    ChildProcess();
  }

  pid_2 = fork(); // fork for second ChildProcess
  if (pid_2 < 0) {
    exit(1);
  }
  else if (pid == 0) {
    ChildProcess();
  }
  else {
    status = wait(NULL);
    ParentProcess();
    pid = wait(&status);
    exit(0);
  }
}

int x;

void ChildProcess(void) {  
  for(x = 0; x <= random_num(0, 31); x++) {
    printf("Child Pid: %d is going to sleep!\n", getpid());
    sleep(random_num(0, 11));

    printf("Child Pid: %d is awake!\nWhere is my Parent: %d?\n", getpid(), getppid());
  }
  exit(0);
}

void ParentProcess(void) {
  printf("Child Pid: %d has completed.\n", getpid());
}

  
int random_num(int lower, int upper)
{
  srand(time(0));

  int num = (rand() % (upper - lower + 1)) + lower;

  return num;
}