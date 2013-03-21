#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
	char *input;
	input = (char *)calloc(246, 1);
	while (strcmp(input, "exit")) {
		printf("prompt=> ");
		gets(input);

		if (strcmp(input, "exit") != 0){
			
			// split by spaces
			char *command;
			command = strtok(input, " ");
			char **args;
			char * arg;
			args = (char **)calloc(32, sizeof(char *));
			args[0] = command;

			int i;
			i = 1;
			do {
				arg = strtok(NULL, " ");
				args[i] = (char *)calloc(32, sizeof(char));

				if (arg != (char *)NULL) {
					strcpy(args[i], arg);
					i++;
				} else {
					args[i] = NULL;
				}
			} while (arg != (char*)NULL);

			switch(fork()) {
				case 0:
					// EXECUTE
					execvp(command, args);
					break;
				default:
					wait(0);
			}
		}
	}
}
