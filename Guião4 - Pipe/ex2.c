#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    int fddesc[2];
    int pp = pipe(fddesc);
    int num = 33;
    int received;

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
        close(fddesc[0]);
        write(fddesc[1],&num,sizeof(num));
        printf("Filho: enviou número: %d\n", num);
        close(fddesc[1]);
        wait(NULL);
    } else {
        close(fddesc[1]);
        printf("Pai: à espera de receber...\n");
        ssize_t bytes;
        while ((bytes = read(fddesc[0],&received,sizeof(received))) > 0) {
            printf("Pai: recebeu o inteiro: %d\n", received);
        }
        if (!bytes) {
            printf("Pai: EOF detetado no pipe.\n");
        } else {
            perror("Erro na leitura");
        }

        close(fddesc[0]);
        _exit(0);
    }

    return 0;
}