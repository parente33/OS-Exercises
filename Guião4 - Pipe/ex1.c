#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

int main () {
    int fddesc[2];
    int number = 54;
    int received;
    int pp = pipe(fddesc);
    if (pp < 0) {
        perror("Pipe failed");
        exit(EXIT_FAILURE);
    }
    pid_t f = fork();
    if (f == -1) {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    }
    if (!f) {
        close(fddesc[1]);
        printf("Filho: à espera de receber...\n");
        read(fddesc[0],&received,sizeof(int));
        printf("Filho: recebeu o número %d\n", number);
        close(fddesc[0]);
        _exit(0);
    } else {
        close(fddesc[0]);
        write(fddesc[1],&number,sizeof(int));
        printf("Pai: enviou o número: %d\n", number);
        close(fddesc[1]);
        wait(NULL);
    }

    return 0;
}