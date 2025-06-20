#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>

// Implementar um programa semelhante ao do ex1 mas agora no contexto de um processo filho
int main() {
    int ret = fork();
    if (ret == -1) {
        perror("fork");
        return -1;
    } else if (ret == 0) {
        printf("[FILHO] DEBUG: Antes de chamar exec\n");

        ret = execl("/bin/ls", "ls", "-l", NULL);
        if (ret == -1) perror("execl");
        printf("[FILHO] DEBBUG: Depois de chamar exec\n");
        _exit(-1);
    } else {
        wait(NULL);
        printf("[PAI] DEBBUG: Depois de filho terminar\n");
    }

    //pid_t pid = fork();
    //if(!pid){
    //    printf("[FILHO] DEBUG: Antes de chamar exec\n");
    //    execl("/bin/ls", "ls", "-l", NULL);
    //    printf("[FILHO] DEBBUG: Depois de chamar exec\n");
    //    _exit(1);
    //}
    //int status;
    //wait(&status);
    //if(!WIFEXITED(status) || WEXITSTATUS(status) == 1){
    //    printf("fatal: couldn't execute command\n");
    //    _exit(-1);
    //}

    return 0;
}