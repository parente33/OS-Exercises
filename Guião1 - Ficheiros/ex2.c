#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {
    int buffer_size = 1024;
    char *buff = (char *)malloc(sizeof(char)*buffer_size);

    int fd_in = open(argv[1], O_RDONLY);
    if (fd_in == -1) {
        perror("open");
        return -1;
    }
    int fd_out = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC);
    if (fd_out == -1) {
        perror("open");
        return -1;
    }

    int bytes_read = 0;

    while ((bytes_read = read(fd_in, buff, sizeof(buff))) > 0) {
        write(fd_out, buff, bytes_read);
    }

    free(buff);
    close(fd_in);
    close(fd_out);

    return 0;
}