#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#define MAX_LINE_LENGTH 1024

int main() {
    int pipe_fd[2];
    char buffer[MAX_LINE_LENGTH];

    int pp = pipe(pipe_fd);
    if (pp < 0) {
        perror("pipe failed");
        exit(1);
    }
    pid_t f = fork();
    if (f < 0) {
        perror("fork failed");
        exit(1);
    }
    if (!f) {
        close(pipe_fd[1]);
        dup2(pipe_fd[0],0);
        execlp("wc","wc",NULL);
        perror("execlp failed");
        exit(1);
    } else {
        close(pipe_fd[0]);
        printf("Introduza linhas de texto (Ctrl+D para terminar):\n");
        while (fgets(buffer, MAX_LINE_LENGTH, stdin) != NULL) {
            write(pipe_fd[1], buffer, strlen(buffer));
        }

        close(pipe_fd[1]);
        wait(NULL);
        printf("Filho terminou\n");
    }

    return 0;
}