#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>

void chmod_recursive(const char *directory_path) {
    DIR *directory = opendir(directory_path);
    struct dirent *dir_entry;

    if (!directory) {
        printf("Erro ao abrir o diretório %s.\n", directory_path);
        exit(1);
    }

    while ((dir_entry = readdir(directory)) != NULL) {
        if (strcmp(dir_entry->d_name, ".") == 0 || strcmp(dir_entry->d_name, "..") == 0) {
            // Ignora os diretórios "." e ".."
            continue;
        }

        char *entry_path = (char *) malloc(strlen(directory_path) + strlen(dir_entry->d_name) + 2); // +2 para o '/' e o '\0'
        sprintf(entry_path, "%s/%s", directory_path, dir_entry->d_name);

        if (dir_entry->d_type == DT_DIR) {
            // Se for um diretório, chama a função recursivamente para alterar as permissões em seus subdiretórios
            chmod_recursive(entry_path);
        } else if (dir_entry->d_type == DT_REG) {
            // Se for um arquivo regular, altera as permissões
            char *command = (char *) malloc(strlen(entry_path) + 15);
            sprintf(command, "chmod 777 %s", entry_path);

            system(command);
            free(command);
        }

        free(entry_path);
    }

    closedir(directory);
}

int main(int argc, char *argv[]) {

    // Tratamento de erros aqui

    chmod_recursive(argv[1]);

    printf("Permissões definidas com sucesso.\n");
    return 0;
}
