#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

// wgrep
int main(int argc, char *argv[]) {
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    if (argc < 2) {
        printf("wgrep: searchterm [file ...]\n");
        exit(1);
    }

    char *searchterm = argv[1];

    if (argc == 2) {
        // read from stdin
        while ((read = getline(&line, &len, stdin)) != -1) {
            if (read == -1 && !feof(stdin)) {
                printf("wgrep: error reading from stdin\n");
                exit(1);
            }
            if (strstr(line, searchterm) != NULL) {
                printf("%s", line);
            }
        }
    } else {
        // read from files
        for (int i = 2; i < argc; i++) {
            fp = fopen(argv[i], "r");
            if (fp == NULL) {
                printf("wgrep: cannot open file %s\n", argv[i]);
                exit(1);
            }

            while ((read = getline(&line, &len, fp)) != -1) {
                if (read == -1 && !feof(fp)) {
                    printf("wgrep: error reading from file %s\n", argv[i]);
                    exit(1);
                }
                if (strstr(line, searchterm) != NULL) {
                    printf("%s", line);
                }
            }

            if (fclose(fp) != 0) {
                printf("wgrep: error closing file %s\n", argv[i]);
                exit(1);
            }
        }
    }

    free(line);

    return 0;
}
