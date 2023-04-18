#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>

int num;

void send_number(int signum) {
    if(num % 2 == 1) {
        printf("[B] Sent signal SIGUSR1 with number %d\n", num);
        kill(getppid(), SIGUSR1);
    }
    else {
        printf("[B] Sent signal SIGUSR2 with number %d\n", num);
        kill(getppid(), SIGUSR2);
    }
}

void check_number(int signum) {
    if(signum == SIGUSR1) {
        printf("[A] Received signal SIGUSR1 with number %d\n", num);
        printf("[A] SUCCESS!\n");
        exit(0);
    }
    else if(signum == SIGUSR2) {
        printf("[A] Received signal SIGUSR2 with number %d\n", num);
        printf("[A] SUCCESS!\n");
        exit(0);
    }
}

int main() {
    struct sigaction pact;
    pact.sa_handler = check_number;
    sigaction(SIGUSR1, &pact, NULL); // TODO
    sigaction(SIGUSR2, &pact, NULL); // TODO

    srand(time(NULL));
    num = rand() % 10 + 1;
    printf("[A] Selected random number: %d\n", num);

    pid_t pid = fork(); // TODO

    if(pid == -1) {
        printf("[A] Failed to create process B\n");
        exit(1);
    }
    else if(pid == 0) { // TODO
        struct sigaction cact;
        cact.sa_handler = send_number;
        sigaction(SIGINT, &cact, NULL); // TODO
        printf("[B] Started\n");
        while(1) {
            sleep(1);
        }
    }
    else {
        sleep(1);
        kill(pid, SIGINT); // TODO
        pause();
    }

    return 0;
}

