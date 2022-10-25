/* timer.c */
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>

int trigger = 0;
int numOfAlarms = 0;
clock_t tic, toc;

void handler1(int signum)
{ //signal handler
  printf("Hello World!\n");
  sleep(1);
  trigger = 1;
  alarm(5);
  // exit(1); //exit after printing
  numOfAlarms++;
}

void handler2(int signum)
{ //signal handler
  toc = clock();
  printf("\nElapsed time: %f seconds\nNumber of alarms: %d\n", (double)(toc - tic) / CLOCKS_PER_SEC, numOfAlarms);
  exit(0);
}

int main(int argc, char * argv[])
{
  signal(SIGALRM,handler1); //register handler to handle SIGALRM
  signal(SIGINT,handler2); //register handler to handle SIGINT
  alarm(5); //Schedule a SIGALRM for 1 second
  
  while(1) {
    tic = clock();
    while(!trigger);
    
    printf("Turing was right!\n"); 
    sleep(1);
    trigger = 0; 
  }
  return 0; //never reached
}