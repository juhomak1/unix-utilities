#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	if (argc < 2) {
		printf("my-zip: file1 [file2 ...]\n");
		exit(1);
	};
	
	int current;
	int previous = EOF;
	int count = 0;
	
	for (int i=1; i < argc; i++) {
		FILE *fp = fopen(argv[i], "r");
		if (fp == NULL) {
			printf("my-zip: cannot open file\n");
			exit(1);
		}
		
		while ((current = fgetc(fp)) != EOF) {
			if (previous == EOF) {
				previous = current;
				count = 1;
			}
			else if (current == previous) {
				count++;
			}
			else {
				fwrite(&count, sizeof(int), 1, stdout);
				fputc(previous, stdout);
				previous = current;
				count = 1;
			}
		}
		fclose(fp);
	}
	
	if (count > 0) {
		fwrite(&count, sizeof(int), 1, stdout);
		fputc(previous, stdout);
	}
	return 0;
}