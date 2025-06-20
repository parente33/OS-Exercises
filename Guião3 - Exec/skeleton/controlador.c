#include <stdio.h>
#include "mysystem.h"

void controller(int N, char** commands) {
	int executionCounts[N];
	for (int i = 0; i < N; i++) executionCounts[i] = 0;

	for (int i = 0; i < N; i++) {
		while (1) {
			pid_t pid = fork();
			if (pid == -1) {
				perror("Fork failed");
				error(EXIT_FAILURE);
			}
			if (!pid) {
				execlp(commands[i],commands[i],NULL);
				perror("Execution failed");
				exit(EXIT_FAILURE);
			}
			int status;
			waitpid(pid,&status,0);
			executionCounts[i]++;
			if (WIFEXITED(status) && WEXITSTATUS(status) == 0) {
				break;
			}
		}
	}
	printf("Execution summary:\n");
	for (int i = 0; i < N; i++) {
		printf("%s executed %d times\n",commands[i],executionCounts[i]);
	}
}

int main(int argc, char* argv[]) {
	if (argc < 2) {
		fprintf(stderr, "Usage: %s <program1> <program2> ...\n", argv[0]);
		return EXIT_FAILURE;
	}

    char *commands[argc-1];
    int N = 0;
	for(int i = 1; i < argc; i++){
		commands[N] = strdup(argv[i]);
		printf("command[%d] = %s\n", N, commands[N]);
        N++;
	}

    controller(N, commands);

	for (int i = 0; i < N; i++) {
		free(commands[i]);
	}

	return 0;
}