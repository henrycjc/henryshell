#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "henry.h"

void error(int code) {

    switch (code) {
	case CTRLD:
	    fprintf(stderr, "Unexpected end of input.\n");
	    break;
	case MEM:
	    fprintf(stderr, "Program out of memory.\n");
	    break;
	case CWD:
	    fprintf(stderr, "Could not read current working directory.\n");
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

char** parse_command(char* line) {
    
    char* save;
    char* token;
    char* line2 = copy_string(line);
    int argc = 0;
    char** args;

    token = strtok_r(line, " ", &save);
    while (token) {
	argc++;
	printf("%s\n", token);
	token = strtok_r(NULL, " ", &save);
    }
    //printf("argc: %d\n", argc);
    if (argc > 0) {
	args = malloc(sizeof(char*) * argc);
	for (int i = 0; i < argc; i++) {
	    args[i] = malloc(sizeof(char) * 255);
	}
	return args;
    } else {
	return NULL;
    }
}

int main(int argc, char** argv) {

    char line[255];
    int c;
    char** args;

    while (1) {
	printf("%s$ ", handle_cwd());
	if (fgets(line, sizeof(line), stdin) == NULL) {
	    error(CTRLD);
	} else {
	    if (line[strlen(line)-1] != '\n') {
		while ((c = getchar() != '\n') && (c != EOF)) {
		    // Consume any remaining characters on stdin
		}
	    } else {
		line[strlen(line)-1] = '\0';
	    }
	    args = parse_command(copy_string(line));
	    if (args != NULL) {

	    }
	}
    }
}
