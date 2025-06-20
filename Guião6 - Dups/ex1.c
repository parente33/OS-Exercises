#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>

int main() {
    int fdin = open("/etc/passwd", O_RDONLY);
    if (fdin < 0) {
        perror("open /etc/passwd");
        exit(1);
    }

    int fdout = open("saida.txt", O_WRONLY | O_CREAT | O_TRUNC, 0600);
    if (fdout < 0) {
        perror("open saida.txt");
        exit(1);
    }

    int fderr = open("erros.txt", O_WRONLY | O_CREAT | O_TRUNC, 0600);
    if (fderr < 0) {
        perror("open erros.txt");
        exit(1);
    }

    int orig_stdout = dup(1);

    if (dup2(fdin,0) == -1) {
        perror("dup2");
    }
    close(fdin);

    dup2(fdout,1);
    close(fdout);

    dup2(fderr,2);
    close(fderr);
    
    dup2(orig_stdout,1);
    close(orig_stdout);

    printf("terminei\n");

    return 0;
}