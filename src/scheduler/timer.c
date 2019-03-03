#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <signal.h>
#include "timer.h"

void setupTimer(void(*handler)(int)) {
    struct sigaction action;
    action.sa_handler = handler;
    sigemptyset(&action.sa_mask);
    action.sa_flags = 0;
    if (sigaction(SIGALRM, &action, NULL) == -1) {
        printf("Error setting up Timer");
         exit(1);
    }
}

/*
 * The timer decrements from it_value to zero, sends SIGALRM after the specified
 * quantum has elapsed, resets to it_interval (0) and then stops.
 */
void setTimerAlarm(int quantum) {
    struct itimerval timer;
    timer.it_interval.tv_usec = 0;
    timer.it_interval.tv_sec = 0;
    timer.it_value.tv_usec = (quantum % 1000) * 1000;
    timer.it_value.tv_sec = quantum / 1000;
    if (setitimer (ITIMER_REAL, &timer, NULL) == -1) {
         printf("Error calling setTimerAlarm");
         exit(1);
    }
}

