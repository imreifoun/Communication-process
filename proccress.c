//Communication between two processes using signals involves the exchange of signals to notify and handle events or data transfer between the processes

#include <stdio.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

void sighub()
{
    signal(SIGHUP, sighub);
    printf("[CHILD RECIVE SEGHUB] !\n");
}

void sigint()
{
    signal(SIGINT, sigint);
    printf("[CHILD RECIVE SEGINT] !\n");
}

void sigquit()
{
    signal(SIGQUIT, sigint);
    printf("[CHILD RECIVE SEGQUIT] - [Die] !\n");
}

void main() {
    
    pid_t child;
    
    child = fork();
    if (child == -1)
    {
        printf("[Error] Fork !");
        exit(0);
    }
    if (child == 0)
    {
        signal(SIGHUP, sighub);
        signal(SIGINT, sigint);
        signal(SIGQUIT, sigquit);
        while (1);
    }
    else
    {
        printf("[SIGHUB SENDING FROM PARENT] !\n");
        kill(child, SIGHUP);
        sleep(3);
        printf("[SIGINT SENDING FROM PARENT] !\n");
        kill(child, SIGINT);
        sleep(3);
        printf("[SIGQUIT SENDING FROM PARENT] !\n");
        kill(child, SIGQUIT);
        sleep(3);
        exit(0);
    }
    return 0;
}