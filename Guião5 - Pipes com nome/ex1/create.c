#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>

int main() {
    int fifo = mkfifo("fifo", 0666);
    if (fifo < 0) perror("fifo");

    return 0;
}