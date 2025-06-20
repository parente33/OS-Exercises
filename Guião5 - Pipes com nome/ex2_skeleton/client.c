#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include "defs.h"

int main (int argc, char * argv[]){
	if (argc < 2) {
		printf("Missing argument.\n");
		_exit(1);
	}

	int num = atoi(argv[1]);
	int pid = getpid();
	char client_fifo[50];
	snprintf(client_fifo, sizeof(client_fifo), "fifo_client_%d", pid);
	unlink(client_fifo);

	if (mkfifo(client_fifo, 0666) < 0) {
		perror("client's fifo");
		return 1;
	}

	int f = open(SERVER, O_WRONLY);
	if (f < 0) {
		perror("fifo");
		return 1;
	}

	Msg pedido = {num, pid, 0};
	write(f,&pedido,sizeof(Msg));
	close(f);

	int fd = open(client_fifo, O_RDONLY);
	if (fd < 0) {
		perror("fifo_resp");
		return 1;
	}

	Msg resposta;
	read(fd,&resposta,sizeof(Msg));
	close(fd);
	unlink(client_fifo);

	printf("Número %d tem %d ocurrências no vetor\n", num, resposta.occurrences);
	
	return 0;
}