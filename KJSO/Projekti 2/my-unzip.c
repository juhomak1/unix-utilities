#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	if (argc < 2) {
		printf("my-unzip: file1 [file2 ...]\n");
		exit(1);
	}
	
	for (int i = 1; i < argc; i++) {
		FILE *fp = fopen(argv[i], "rb");
		if (fp == NULL) {
			printf("my-unzip: cannot open file\n");
			exit(1);
		}
		
		int count;
		while (fread(&count, sizeof(int), 1, fp) == 1) {
			int c = fgetc(fp);
			if (c == EOF) {
				break;
			}
			for (int j = 0; j < count; j++) {
				putchar(c);
			}
		}
		fclose(fp);
	}
	return 0;
}