#include <stdlib.h>
#include "Auto_Complete.h"

int main(){
    char latter[50];
    char *WordMa;
    int op = 0;

    WordList list;

    init(&list);

    FILE *Arquivo;

    Arquivo = fopen("DicionarioBR.txt","r");

    if(Arquivo == NULL){
        printf("ERRO\n");
        return 1;
    }
    while(!feof(Arquivo)){
        WordMa = fgets(latter, 50, Arquivo);
        if(WordMa != NULL){
            add(&list, latter);
        }
    }

    while(op !=3 ){
    system("cls");
    printf("\n----------------- MENU -----------------");
    printf("\n---> 1  ADICIONAR PALAVRA ");
    printf("\n---> 2  BUSCAR PALAVRA ");
    printf("\n---> 3  SAIR ");
    printf("\n-----------------------------------------\n\n");
    scanf("%d", &op);

    switch(op){
        case 1:
            system("cls");
            printf("\nDIGITE UMA PARALVRA: ");
            scanf("%s", latter);
            printf("\n%s\n\n",latter);

            add(&list, latter);
            op=0;
            break;
        case 2:
            system("cls");
            printf("\nDIGITE UMA PARALVRA: ");
            scanf("%s", latter);

            show(&list, latter);
            system("pause");

            op=0;
            break;

        case 3:

            break;

        default:
            op = 0;
    }
}
return EXIT_SUCCESS;
}
