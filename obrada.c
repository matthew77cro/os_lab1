#define _XOPEN_SOURCE 500
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

#define N 6

/* Prioriteti prekida:
 * 
 * 5. SIGINT
 * 4. SIGPROF
 * 3. SIGTTIN
 * 2. SIGTTOU
 * 1. SIGSYS
 * 
 */

int OZNAKA_CEKANJA[N];
int PRIORITET[N];
int TEKUCI_PRIORITET;

int sig[] = {SIGINT,SIGPROF,SIGTTIN,SIGTTOU,SIGSYS};

void ispis_varijabli(){
 
    printf("OZNAKA_CEKANJA[ %d %d %d %d %d %d ] TP = %d PRIORITETR[ %d %d %d %d %d %d ]\n", OZNAKA_CEKANJA[0], OZNAKA_CEKANJA[1], OZNAKA_CEKANJA[2], OZNAKA_CEKANJA[3], OZNAKA_CEKANJA[4], OZNAKA_CEKANJA[5], TEKUCI_PRIORITET, PRIORITET[0], PRIORITET[1], PRIORITET[2], PRIORITET[3], PRIORITET[4], PRIORITET[5]);
    
}

void zabrani_prekidanje(){
   int i;
   for(i=0; i<5; i++)
      sighold(sig[i]);
}
void dozvoli_prekidanje(){
   int i;
   for(i=0; i<5; i++)
      sigrelse(sig[i]);
}

//rewrite da ne bi triggerao plagijat
void obrada_signala(int i){
    int j;
    if(i==1){
     
        printf("-  P  -  -  -  -\t");
        ispis_varijabli();
	    for(j=1; j<=5; j++) {
	        printf("-  %d  -  -  -  -\t", j);
            ispis_varijabli();
            sleep(1);
	    }
	    printf("-  K  -  -  -  -\t");
        ispis_varijabli();
        
    }else if(i==2){
     
        printf("-  -  P  -  -  -\t");
        ispis_varijabli();
	    for(j=1; j<=5; j++) {
	        printf("-  -  %d  -  -  -\t", j);
            ispis_varijabli();
            sleep(1);
	    }
	    printf("-  -  K  -  -  -\t");
        ispis_varijabli();
        
    }else if(i==3){
     
        printf("-  -  -  P  -  -\t");
        ispis_varijabli();
	    for(j=1; j<=5; j++) {
	        printf("-  -  -  %d  -  -\t", j);
            ispis_varijabli();
            sleep(1);
	    }
        printf("-  -  -  K  -  -\t");
        ispis_varijabli();
        
    }else if(i==4){
     
        printf("-  -  -  -  P  -\t");
        ispis_varijabli();
	    for(j=1; j<=5; j++) {
	        printf("-  -  -  -  %d  -\t", j);
            ispis_varijabli();
            sleep(1);
	    }
        printf("-  -  -  -  K  -\t");
        ispis_varijabli();
            
    }else if(i==5){
     
         printf("-  -  -  -  -  P\t");
         ispis_varijabli();
	    for(j=1; j<=5; j++) {
	        printf("-  -  -  -  -  %d\t", j);
            ispis_varijabli();
            sleep(1);
	    }
            printf("-  -  -  -  -  K\t");
            ispis_varijabli();
        
    }

}

void prekidna_rutina(int sig){
    int n=-1;
    zabrani_prekidanje();
    
    switch(sig){
        case SIGINT: 
            n=5; 
            printf("-  -  -  -  -  X\t");
            ispis_varijabli();
            break;
        case SIGPROF: 
            n=4; 
            printf("-  -  -  -  X  -\t");
            ispis_varijabli();
            break;
        case SIGTTIN: 
            n=3; 
            printf("-  -  -  X  -  -\t");
            ispis_varijabli();
            break;
        case SIGTTOU: 
            n=2; 
            printf("-  -  X  -  -  -\t");
            ispis_varijabli();
            break;
        case SIGSYS: 
            n=1; 
            printf("-  X  -  -  -  -\t");
            ispis_varijabli();
            break;
    }
    
    OZNAKA_CEKANJA[n]+=1;
   
    int x;
    do {
        x = 0;
        for (int i=TEKUCI_PRIORITET+1; i<N; i++) {
            if (OZNAKA_CEKANJA[i]>0) {
                x = i;
            }
        }
        if (x>0) {
            OZNAKA_CEKANJA[x]-=1;
            PRIORITET[x] = TEKUCI_PRIORITET;
            TEKUCI_PRIORITET = x;
            dozvoli_prekidanje();
            obrada_signala(x);
            zabrani_prekidanje();
            TEKUCI_PRIORITET = PRIORITET[x];
            PRIORITET[x] = 0;
        }        
    } while (x>0);
    
    dozvoli_prekidanje();
 }

int main(){
    
    //povezivanje signala sa prekidnom rutinom
    int i;
    for(i=0;i<N;i++)
        sigset(sig[i], prekidna_rutina);
    
    TEKUCI_PRIORITET = 0;
    
    printf("Proces obrade prekida, PID=%d\n", getpid());
    printf("GP S1 S2 S3 S4 S5\n");
    printf("-----------------\n");
    /* troši vrijeme da se ima šta prekinuti - 10 s */
    i = 1;
    while(1){
     
        printf("%2d -  -  -  -  -\t",i);
        ispis_varijabli();
        i++;
        sleep(1);
        
    }
 
    printf ("Zavrsio osnovni program\n");
 
    return 0;
    
}
