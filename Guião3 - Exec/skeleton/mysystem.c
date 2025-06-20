#include "mysystem.h"


// recebe um comando por argumento
// returna -1 se o fork falhar
// caso contrario retorna o valor do comando executado
int mysystem (const char* command) {
	char *dc = strdup(command);
	char *token, *aux[100];
	int res, i = 0;
	if (command == NULL) return -1;

	while ((token = strsep(&dc, " ")) != NULL) {
		aux[i++] = token;
	}
	aux[i] = NULL;

	pid_t pid = fork();
	if (pid == -1) {
		perror("fork");
		return -1;
	}
	if (pid == 0) {
		int r = execvp(aux[0],aux);
		if (r == -1) {
			perror("File error");
			_exit(EXIT_FAILURE);
		}
	}
	else {
		wait(&res);
		printf("Processo filho termina com valor: %d\n", WEXITSTATUS(res));
	}

	free(dc);
	return res;
}