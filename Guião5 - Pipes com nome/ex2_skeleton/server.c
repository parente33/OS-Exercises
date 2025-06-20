#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include "defs.h"
#include "vector.h"

int main (int argc, char * argv[]){
	init_vector();
	print_vector();

	unlink(SERVER);
	if (mkfifo(SERVER, 0666) < 0) {
		perror("fifo");
		return 1;
	}
	printf("Servidor iniciado.\n");

    int f = open(SERVER, O_RDONLY);
	if (f < 0) {
		perror("server's fifo");
		return 1;
	}

	int dummy = open(SERVER, O_WRONLY); // evitar EOF

	Msg pedido;
	while (read(f,&pedido,sizeof(Msg)) > 0) {
		printf("Recebido pedido para número: %d (PID: %d)\n", pedido.needle, pedido.pid);

		pedido.occurrences = count_needle(pedido.needle);

		char client_fifo[50];
		snprintf(client_fifo, sizeof(client_fifo), "fifo_client_%d", pedido.pid);
		
		int client_fd = open(client_fifo, O_WRONLY);
		if (client_fd < 0) {
			perror("client's fifo");
			continue;
		}

		write(client_fd, &pedido, sizeof(Msg));
		close(client_fd);
		printf("Resposta enviada para %s: %d ocorrências\n", client_fifo, pedido.occurrences);
	}

	close(f);
	close(dummy);
	unlink(SERVER);

	return 0;
}