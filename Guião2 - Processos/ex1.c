#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t meu_pid = getpid();
    pid_t ppid = getppid();
    printf("Meu pid: %d; Pid do pai: %d\n", (int)meu_pid, (int)ppid);
    return 0;
}