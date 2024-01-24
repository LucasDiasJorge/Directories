#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

void listFiles(const char *path) {
    DIR *dir;
    struct dirent *entry;

    // Abre o diretório
    dir = opendir(path);

    // Verifica se o diretório foi aberto com sucesso
    if (dir == NULL) {
        perror("Erro ao abrir diretório");
        exit(EXIT_FAILURE);
    }

    // Lê cada entrada do diretório
    while ((entry = readdir(dir)) != NULL) {
        printf("%s\n", entry->d_name);
    }

    // Fecha o diretório
    closedir(dir);
}

int main() {
    const char *path = "."; // Altere "." para o caminho do diretório desejado

    printf("Listando arquivos em %s:\n", path);
    listFiles(path);

    return 0;
}
