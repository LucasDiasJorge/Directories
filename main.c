#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <signal.h>

volatile sig_atomic_t keep_running = 1;

void sigint_handler(int signum) {
    // Manipulador de sinal para SIGINT (Ctrl+C)
    printf("\nRecebido sinal SIGINT (Ctrl+C). Saindo...\n");
    keep_running = 0;
}

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
    signal(SIGINT, sigint_handler);  // Configura o handler para SIGINT (Ctrl+C)

    while (keep_running) {
        char path[100];  // Supõe que o caminho do diretório não excederá 100 caracteres

        // Solicita ao usuário o caminho do diretório desejado
        printf("Digite o caminho do diretório desejado (ou !exit para sair): ");
        scanf("%s", path);

        if (strcmp(path, "!exit") == 0) {
            keep_running = 0;
            break;
        }

        // Chama a função para listar os arquivos no diretório fornecido pelo usuário
        printf("Listando arquivos em %s:\n", path);
        listFiles(path);
    }

    printf("Encerrando o programa.\n");

    return 0;
}
