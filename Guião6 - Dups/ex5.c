#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

int main() {
    int pipe_fd[2];
    int pp = pipe(pipe_fd);
    if (pp < 0) {
        perror("pipe failed");
        exit(1);
    }

    pid_t f1 = fork();
    if (f1 < 0) {
        perror("fork failed");
        exit(1);
    }
    if (!f1) {
        close(pipe_fd[0]);
        dup2(pipe_fd[1],1);
        close(pipe_fd[1]);

        execlp("ls","ls","/etc",NULL);
        perror("execlp failed");
        exit(1);
    }

    pid_t f2 = fork();
    if (f2 < 0) {
        perror("fork failed");
        exit(1);
    }
    if (!f2) {
        close(pipe_fd[1]);
        dup2(pipe_fd[0],0);
        close(pipe_fd[0]);
        
        execlp("wc","wc","-l",NULL);
        perror("execlp failed");
        exit(1);
    }

    close(pipe_fd[0]);
    close(pipe_fd[1]);
    
    waitpid(f1,NULL,0);
    waitpid(f2,NULL,0);

    return 0;
}