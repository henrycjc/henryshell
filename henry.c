#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "henry.h"

void error(int code) {

	switch (code) {
		case CTRLD:
			fprintf(stderr, "Unexpected end of input.");
			break;
		case MEM:
			fprintf(stderr, "Program out of memory.");
			break;
		case CWD:
			fprintf(stderr, "Could not read current working directory.");
			break;
		default:
			break;
	}
	exit(code);
}


char* copy_string(const char* str) {
	char* tmp = malloc(strlen(str) + 1);
	if (tmp == NULL) {
		error(MEM);
		return NULL;
	} else {
		return strcpy(tmp, str);
	}
}


char* handle_cwd(void) {

	char cwd[1024];
	if (getcwd(cwd, sizeof(cwd)) != NULL) {
		return copy_string(cwd);
	} else {
		error(CWD);
		return NULL;
	}
}

void parse_command(char* line) {

	printf("%s\n", line);
}

int main(int argc, char** argv) {

	char line[255];
	int c;
	while (1) {
		printf("%s$ ", handle_cwd());
		if (fgets(line, sizeof(line), stdin) == NULL) {
			error(CTRLD);
		} else {
			if (line[strlen(line)-1] != '\n') {
				while ((c = getchar() != '\n') && (c != EOF)) {
					// Expunge any remaining characters on stdin
				}
			} else {
				line[strlen(line)-1] = '\0';
			}
			parse_command(copy_string(line));
			//printf("%s\n", line);
		}
	}
}