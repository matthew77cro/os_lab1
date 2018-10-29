#define _XOPEN_SOURCE 500
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

int pid = 0;
int sig[] = {SIGINT,SIGPROF,SIGTTIN,SIGTTOU,SIGSYS};

void prekidna_rutina(int sig){
   /* pošalji SIGKILL procesu 'pid'*/
   kill(pid, SIGKILL);
   exit(0);
}

int main(int argc, char *argv[]){
 
    int r;
    srand(time(NULL));   // Inicijalizacija
    
    if(argc==1) exit(1);
    pid = atoi(argv[1]);
    sigset(SIGINT, prekidna_rutina);
    
    while(1){
      /* odspavaj 3-8 sekundi */
      r = rand()%6+3;      // Vraća pseudo-random int između 3 i 8
      sleep(r);

      /* slučajno odaberi jedan signal (od 4) */
      r = rand()%4+1;      // Vraća pseudo-random int između 0 i 3
      
      /* pošalji odabrani signal procesu 'pid' funkcijom kill*/
      kill(pid,sig[r]);
      
      printf("kill -%d %d\tPrekid razine %d\n",sig[r],pid,5-r);
   }
    
    return 0;
    
}
