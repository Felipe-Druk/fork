#include <stdio.h>
#include <time.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <signal.h>

#define ERROR -1
#define SUCES 0

const int ARG = 3;
const int PROS_ARG = 2;
const int TIME_ARG = 1;

pid_t pid_kill = 0;

void pros_dad(pid_t pid_son, int time_wait);

int
main(int argc, char *argv[]){
    if(argc < ARG){
        return ERROR;
    }
    int pid;
    if ((pid = fork()) == ERROR)    {
        return ERROR;
    } else if(!pid){
        //hijo
        execvp(argv[PROS_ARG], argv + (PROS_ARG ));
        perror("no exec arg");
        exit(ERROR);
    }
    else {
        //papa     
        pros_dad(pid, atoi(argv[TIME_ARG]));
    }

    return ERROR;
}



void tieme_handler(union sigval value) {
    if(pid_kill){
        kill(pid_kill, SIGTERM);
        printf("Time out ");
    }
}

void pros_dad(pid_t pid_son, int time_wait){
    pid_kill = pid_son;

    timer_t timer;
    struct sigevent sig_event;
    struct itimerspec reques_time;

    sig_event.sigev_notify = SIGEV_SIGNAL;
    sig_event.sigev_signo = SIGRTMIN;


    if (timer_create(CLOCK_REALTIME, &sig_event, &timer) == ERROR) {
        perror("timer no create");
        exit(ERROR);
    }


    reques_time.it_value.tv_sec = time_wait; 
    reques_time.it_value.tv_nsec = 0;
    reques_time.it_interval.tv_sec = 0; 
    reques_time.it_interval.tv_nsec = 0;


    if (timer_settime(timer, 0, &reques_time, NULL) == -1) {
        perror("timer no settime");
        exit(ERROR);
    }

    signal(SIGRTMIN, tieme_handler);

    wait(NULL);
    exit(SUCES);
}
