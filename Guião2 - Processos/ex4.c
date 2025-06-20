#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int main() {
    for (int i = 0; i < 10; i++) {
        pid_t pid = fork();
        if (pid == -1) {
            perror("Fork failed");
            exit(EXIT_FAILURE);
        }
        if (!pid) {
            printf("Filho: O meu PID é: %d;O do meu pai é: %d\n",(int)getpid(),(int)getppid());
            _exit(i+1);
        }
    }
    int status;
    for (int i = 0; i < 10; i++) {
        pid_t pid = wait(&status);
        if (pid != 1 && WIFEXITED(status)) {
            printf("Exit order: %d\n",WEXITSTATUS(status));
        }
    }

    return 0;
}