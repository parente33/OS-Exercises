#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
    char buffer[2048];
    int fifo = open("fifo", O_RDONLY);
    if (fifo < 0) perror("open");

    int byt;

    while ((byt = read(fifo,buffer,2048)) > 0) {
        write(1,buffer,byt);
    }

    close(fifo);

    return 0;
}