#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        exit(0); // Se nenhum arquivo foi especificado, apenas saia com status 0
    }

    for (int i = 1; i < argc; i++) {
        FILE *fp = fopen(argv[i], "r");
        if (fp == NULL) {
            printf("wcat: cannot open file\n");
            exit(1); // Se falhar ao abrir um arquivo, imprima a mensagem de erro e saia com status 1
        }

        char buffer[512];
        while (fgets(buffer, sizeof(buffer), fp) != NULL) {
            printf("%s", buffer);
        }

        fclose(fp);
    }

    return 0; // Saia com status 0 se todos os arquivos forem processados com sucesso
}