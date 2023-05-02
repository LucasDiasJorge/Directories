#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>

int main() {
    char *directory_path = "/home/user/Documents/Projects/Back-end/retail-apiserver"; // Substitua pelo caminho do diretório desejado
    DIR *directory = opendir(directory_path);
    struct dirent *dir_entry;

    if (!directory) {
        printf("Erro ao abrir o diretório.\n");
        exit(1);
    }

    while ((dir_entry = readdir(directory)) != NULL) {
        if (dir_entry->d_type == DT_REG) { // Verifica se é um arquivo regular
            char *file_path = (char *) malloc(strlen(directory_path) + strlen(dir_entry->d_name) + 2); // +2 para o '/' e o '\0'
            sprintf(file_path, "%s/%s", directory_path, dir_entry->d_name);

            char *command = (char *) malloc(strlen(file_path) + 15);
            sprintf(command, "chmod 775 %s", file_path);
            printf("%s\n", file_path);

            system(command);

            free(file_path);
            free(command);
        }
    }

    closedir(directory);
    printf("Permissões definidas com sucesso.\n");
    return 0;
}