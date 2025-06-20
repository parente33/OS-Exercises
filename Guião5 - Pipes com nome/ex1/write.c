#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
    char buffer[2048];
    int fifo = open("fifo", O_WRONLY);
    if (fifo < 0) perror("open");

    int byt;

    while ((byt = read(0,buffer,2048)) > 0) {
        write(fifo,buffer,byt);
    }

    close(fifo);

    return 0;
}