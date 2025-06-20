#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#define MAX_COMMANDS 10

// parse the argument and execvp
// returns the result of exec
int exec_command(char* arg){
	char *exec_args[10];
	int args_count = 0;
	int exec_ret = 0;

	char *token, *string, *tofree;

	tofree = string = strdup(arg);
	assert(string != NULL);

	while ((token = strsep(&string, " ")) != NULL) {
		exec_args[args_count]=token;
		args_count++;
	}
	exec_args[args_count]=NULL;

	exec_ret = execvp(exec_args[0],exec_args);

	perror("Exec error");

    free(tofree);

	return exec_ret;
}

int main(int argc, char** argv){
	int number_of_commands = 4;
	char * commands[] = {
		"grep -v ^# /etc/passwd",
		"cut -f7 -d:",
		"uniq",
		"wc -l"
	};

	int fd[2];
	
	for (int i = 0; i < number_of_commands; i++) {
		if (i < number_of_commands - 1) {
			int pp = pipe(fd);
			if (pp < 0) {
				perror("pipe failed");
				exit(1);
			}
		}

		pid_t f = fork();
		if (f < 0) {
			perror("fork failed");
			exit(1);
		}
		if (!f) {
			if (i < number_of_commands - 1) {
				close(fd[0]);
				dup2(fd[1],1);
				close(fd[1]);
			}

			if (i > 0) {
				close(fd[1]);
				dup2(fd[0],0);
				close(fd[0]);
			}

			exec_command(commands[i]);
			exit(1);
		}

		if (i < number_of_commands - 1) {
			close(fd[1]);
			close(fd[0]);
		}
	}

	for (int i = 0; i < number_of_commands; i++) wait(NULL);

	return 0;
}