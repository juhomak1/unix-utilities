#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void grep_stream(FILE *stream, const char *searchterm) {
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;
	
	while ((nread = getline(&line, &len, stream)) != -1) {
		if (strstr(line, searchterm) != NULL) {
			printf("%s", line);
		};
	};
	free(line);
};

int main(int argc, char *argv[]) {
	if (argc < 2) {
		printf("my-grep: searchterm [file ...]\n");
		exit(1);
	};
	
	char *searchterm = argv[1];
	
	if (argc == 2) {
		grep_stream(stdin, searchterm);
	}
	else {
		for (int i = 2; i<argc; i++) {
			FILE *fp = fopen(argv[i], "r");
			if (fp == NULL) {
				printf("my-grep: cannot open file");
				exit(1);
			}
			grep_stream(fp, searchterm);
			fclose(fp);
		}
	}
	
	return 0;
}