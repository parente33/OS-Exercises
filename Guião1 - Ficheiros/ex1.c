#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    char *buff = (char *)malloc(5 * sizeof(char));

    ssize_t tam = 0;
    while ((tam = read(0, buff, sizeof(buff))) > 0) {
        write(1, buff, tam);
    }
    free(buff);
    return tam;
}