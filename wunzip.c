#include <stdio.h>
#include <stdlib.h>

// wunzip
int main(int argc, char *argv[]) {
    FILE *fp;
    int count;
    char ch;
    size_t readSize;

    if (argc < 2) {
        printf("wunzip: file1 [file2 ...]\n");
        exit(1);
    }

    for (int i = 1; i < argc; i++) {
        fp = fopen(argv[i], "r");
        if (fp == NULL) {
            printf("wunzip: cannot open file %s\n", argv[i]);
            exit(1);
        }

        while ((readSize = fread(&count, 4, 1, fp)) == 1) {
            readSize = fread(&ch, 1, 1, fp);
            if (readSize != 1) {
                printf("wunzip: error reading from file %s\n", argv[i]);
                exit(1);
            }
            for (int j = 0; j < count; j++) {
                printf("%c", ch);
            }
        }
        if (readSize != 0) {
            printf("wunzip: error reading from file %s\n", argv[i]);
            exit(1);
        }
        fclose(fp);
    }

    return 0;
}
