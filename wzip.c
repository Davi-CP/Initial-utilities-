#include <stdio.h>
#include <stdlib.h>

// wzip
int main(int argc, char *argv[]) {
    FILE *fp;
    char curr, prev;
    int count = 1;
    size_t writeSize;

    if (argc < 2) {
        printf("wzip: file1 [file2 ...]\n");
        exit(1);
    }

    for (int i = 1; i < argc; i++) {
        fp = fopen(argv[i], "r");
        if (fp == NULL) {
            printf("wzip: cannot open file %s\n", argv[i]);
            exit(1);
        }

        while ((curr = fgetc(fp)) != EOF) {
            if (prev == curr) {
                count++;
            } else {
                if (prev != '\0') {
                    writeSize = fwrite(&count, 4, 1, stdout);
                    if (writeSize != 1) {
                        printf("wzip: error writing to stdout\n");
                        exit(1);
                    }
                    writeSize = fwrite(&prev, 1, 1, stdout);
                    if (writeSize != 1) {
                        printf("wzip: error writing to stdout\n");
                        exit(1);
                    }
                }
                count = 1;
            }
            prev = curr;
        }
        if (ferror(fp)) {
            printf("wzip: error reading file %s\n", argv[i]);
            exit(1);
        }
        fclose(fp);
    }

    writeSize = fwrite(&count, 4, 1, stdout);
    if (writeSize != 1) {
        printf("wzip: error writing to stdout\n");
        exit(1);
    }
    writeSize = fwrite(&prev, 1, 1, stdout);
    if (writeSize != 1) {
        printf("wzip: error writing to stdout\n");
        exit(1);
    }

    return 0;
}
