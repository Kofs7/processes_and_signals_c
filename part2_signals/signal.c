/* hello_signal.c */
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int trigger = 0;

void handler(int signum)
{ //signal handler
  printf("Hello World!\n");
  sleep(1);
  trigger = 1;
  alarm(5);
  // exit(1); //exit after printing
}

int main(int argc, char * argv[])
{
  signal(SIGALRM,handler); //register handler to handle SIGALRM
  alarm(5); //Schedule a SIGALRM for 1 second
  
  while(1) {
    while(!trigger);
    
    printf("Turing was right!\n"); 
    sleep(1);
    trigger = 0; 
  }
  return 0; //never reached
}

