#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>

// Implementar um programa que execute o comando ls -l
int main() {
    int ret = execl("/bin/ls", "ls", "-l", NULL);
    if (ret == -1) perror("execl");
    printf("DEBUG: Depois de chamar exec\n"); // Só imprimirá se o exec correr mal
    _exit(-1);

    return 0;
}