#include<stdio.h>
#include<string.h>

#define MAX_LENGTH 1024

int main () {

    char input[MAX_LENGTH];

    printf("Digite as equacoes do sistema e aperte Enter 2x para enviar.\n");

    for(int i = 0; i < MAX_LENGTH; i++) {
        scanf("%c", &input[i]);

        if (input[i] == '\n') {
            if(i > 0 && input[i - 1] == '\n') {
                input[i] = '\0';
                input[i - 1] = '\0';
                break;
            }
        }
    }

    int len = strlen(input);

    for (int i = 0; i < len; i++){
        printf("%c", input[i]);
    }

    printf("\n");

    return 0;
}