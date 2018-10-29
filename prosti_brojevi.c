#define _XOPEN_SOURCE 500
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <math.h>

int pauza = 0;
int broj = 1000000001;
int zadnji = 1000000001;

void periodicki_posao(){
    printf("%d\n", zadnji);
}

void postavi_pazu(){
    pauza = 1 - pauza;
    printf("toggled pause\n last prime %d\n", zadnji);
}

void kraj(){
    printf("terminated\n last prime %d\n",zadnji);
    exit(0);
}

int prost ( unsigned long n ) {
    unsigned long i, max;

    if ( ( n & 1 ) == 0 ) /* je li paran? */
        return 0;

    max = sqrt ( n );
    for ( i = 3; i <= max; i += 2 )
        if ( ( n % i ) == 0 )
            return 0;

    return 1; /* broj je prost! */
}

int main(){
    
    sigset(SIGINT, postavi_pazu);
    sigset(SIGTERM, kraj);
    
    struct itimerval t;

	/* povezivanje obrade signala SIGALRM sa funkcijom "periodicki_posao" */
	sigset ( SIGALRM, periodicki_posao );

	/* definiranje periodičkog slanja signala */
	/* prvi puta nakon: */
	t.it_value.tv_sec = 0;
	t.it_value.tv_usec = 500000;
	/* nakon prvog puta, periodicki sa periodom: */
	t.it_interval.tv_sec = 0;
	t.it_interval.tv_usec = 500000;

	/* pokretanje sata s pridruženim slanjem signala prema "t" */
	setitimer ( ITIMER_REAL, &t, NULL );

    printf("PID: %d\n", getpid());
    
    while(1){
        
        if(prost(broj)) zadnji = broj;
        broj++;
        
        if(pauza){
            sighold(SIGALRM);
            pause();
        }
        sigrelse(SIGALRM);

    }

    return 0;
    
}
