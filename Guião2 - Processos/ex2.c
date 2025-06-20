#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();
    if (!pid) {
        printf("Filho => O meu pid é: %d; O pid do meu pai é %d\n", (int)getpid(), (int)getppid());
    } else {
        printf("Pai => O meu pid é: %d; O pid do meu pai é: %d; O pid do meu filho é: %d\n", (int)getpid(), (int)getppid(), (int)pid);
    }
    return 0;
}