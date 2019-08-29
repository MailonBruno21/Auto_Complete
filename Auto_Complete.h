#ifndef Structure_Auto_Complete_h
#define Structure_Auto_Complete_h
#include <stdio.h>
#include <string.h>

//DEFININDO VALORES PARA TRUE END FALSE
enum boolean{
    true = 1, false = 0
};

typedef enum boolean bool;

//ESTRUTURA DE ARMAZENAMENTO DE CADA LETRA
typedef struct Node{
    char data[2];
    struct Node *nextChar;
    struct Node *downWord;
}Node;

//ESTRUTURA PARA ARMAZENAR OS ELEMENTOS PARA IMPRESSÃO
typedef struct No{
    struct Node *no;
    struct No *nextNo;
    char WordNo[50];
}No;
//ESTRUTURA DO PRIMEIRO NÓ DA LISTA DE IMPRESSÃO
typedef struct noList{
    No *firstNo;
    int sizeNo;
}noList;
//ESTRUTURA DO PRIMEIRO NÓ DA LISTA DE ARMAZENAMENTO DAS LETRAS
typedef struct WordList{
    Node *first[25];
    int size[25];
}WordList;

void init(WordList *list);
void initNo(noList *lista);
void downList(noList *lista);
int enqueue(noList *lista, Node *aux, char *Word);
int add (WordList *list, char *Word);
void seek (Node *aux, char *Word);
int show(WordList *list, char *Word);
int imprime(Node *aux, char *Word);
bool isEmpty(noList *lista);


bool compare (char *letterOne, char *letterTwo);

//------------------------------------------------------------------------------------//

void initNo(noList *lista){
        lista->firstNo = NULL;
        lista->sizeNo = 0;
}

void init(WordList *list){
    for(int aux = 0; aux <= 25 ; aux++){
        Node *indice = (Node*)malloc(sizeof(Node));
        indice->data[0] = 65 + aux;
        indice->downWord = NULL;
        indice->nextChar = NULL;
        list->first[aux] = indice;
        list->size[aux]  = 0;
    }
}

bool isEmpty(noList *lista){
    return(lista->sizeNo == 0);
}

void downList(noList *lista){
    No *aux;
    int i = 0;
    aux = lista->firstNo;
    while(i < lista->sizeNo){
        seek(aux->no, aux->WordNo);
        aux = aux->nextNo;
        i++;
    }
}

int enqueue(noList *lista, Node *aux, char *Word){
    No *NodeNo = (No*)malloc(sizeof(No));

    NodeNo->nextNo = NULL;
    NodeNo->no = aux;
    strcpy(NodeNo->WordNo, Word);

    if(lista->sizeNo == 0){
        lista->firstNo = NodeNo;
    }else{
        No *aux2 = lista->firstNo;
        while(aux2->nextNo != NULL){
            aux2 = aux2->nextNo;
        }

        aux2->nextNo = NodeNo;

    }
    lista->sizeNo++;
    return -1;

}

int add (WordList *list, char *Word){

    char teste[1] = "", comparar;
    Node *aux;
    int tamanho = strlen(Word);

    //INICIO - VERIFICA QUAL O INDICE DA PALAVRA
    for(int j = 0; j <= 25; j++){

        comparar = list->first[j]->data[0];

        if(comparar == Word[0] ){
            aux = list->first[j];
    //FIM
            for(int i = 0; i <= tamanho; i++){                          //FAZ A CONTAGEM DA QUANTIDADE DE CHAR QUE SERÁ ADD
                //INICIO - ADD A PRIMEIRA PALAVRA NO INDICE
                if(aux == list->first[j] && aux->nextChar == NULL){    //VERIFICA SE O INDICE APONTA PARA ALGUMA LETRA

                    //VERIFICA SE A PALAVRA SÓ TEM UMA LETRA
                    if(strcmp(&Word[i+1], teste) == 0){

                        Node *Nulo = (Node*)malloc(sizeof(Node));
                        Nulo->data[0] = '\0';
                        Nulo->downWord = NULL;
                        Nulo->nextChar = NULL;


                        Node *NewNode = (Node*)malloc(sizeof(Node));
                        aux->nextChar = NewNode;
                        NewNode->data[0] = Word[i];
                        NewNode->downWord = NewNode;
                        NewNode->nextChar = Nulo;

                    printf("\nADICIONOU A PALAVRA: %c ", NewNode->data[0]);


                    list->size[j]++;
                    return 0;
                    //CASO A PALAVRA TENHA MAIS DE UMA LETRA
                    }else{

                        int q = i;
                        while(Word[q] != '\0'){

                            Node *NewNode = (Node*)malloc(sizeof(Node));
                            aux->nextChar = NewNode;
                            NewNode->data[0] = Word[q];
                            NewNode->downWord = NewNode;
                            NewNode->nextChar = NULL;

                            aux = NewNode;
                            q++;



                        }

                        Node *Nulo = (Node*)malloc(sizeof(Node));
                        Nulo->data[0] = '\0';
                        Nulo->downWord = NULL;
                        Nulo->nextChar = NULL;

                        aux->nextChar = Nulo;
                        list->size[j]++;
                        return 0;
                    }
                }
                //FIM



                //VERIFICA SE A LETRA JÁ SE ENCONTRA NA LISTA OU SE É UM NÓ NULO
                if(Word[i] == aux->nextChar->data[0]){

                    aux = aux->nextChar;

                //ADD A PALAVRA PARA FRENTE CASO NÃO AJA UM NÓ VALIDO NA FRENTE
                }else if(aux->nextChar->data[0] == '\0' && aux->nextChar->nextChar == NULL){
                    aux = aux->nextChar;
                    int q = i;
                        while(Word[q] != '\0'){


                            Node *NewNode = (Node*)malloc(sizeof(Node));
                            aux->nextChar = NewNode;
                            NewNode->data[0] = Word[q];
                            NewNode->downWord = NewNode;
                            NewNode->nextChar = NULL;

                            aux = NewNode;
                            q++;
                        }

                        Node *Nulo = (Node*)malloc(sizeof(Node));
                        Nulo->data[0] = '\0';
                        Nulo->downWord = NULL;
                        Nulo->nextChar = NULL;

                        aux->nextChar = Nulo;
                        list->size[j]++;
                        return 0;
                //CASO AJA UM VALIDO ELE FAZ TESTES PARA SABER ONDE ADD
                }else if(aux->nextChar->data[0] == '\0' && aux->nextChar->nextChar->data[0] == Word[i]) {
                    aux = aux->nextChar->nextChar;
                }else if (aux->downWord == aux && aux->data[0] != '\0'){

                        int q = i;

                            Node *Nulo = (Node*)malloc(sizeof(Node));
                            Nulo->data[0] = '\0';
                            Nulo->downWord = Nulo;
                            Nulo->nextChar = NULL;

                            aux->downWord = Nulo;

                            aux = Nulo;

                        while(Word[q] != '\0'){


                            Node *NewNode = (Node*)malloc(sizeof(Node));
                            aux->nextChar = NewNode;
                            NewNode->data[0] = Word[q];
                            NewNode->downWord = NewNode;
                            NewNode->nextChar = NULL;

                            aux = NewNode;
                            q++;
                        }

                        Node *NuloD = (Node*)malloc(sizeof(Node));
                        NuloD->data[0] = '\0';
                        NuloD->downWord = NULL;
                        NuloD->nextChar = NULL;

                        aux->nextChar = NuloD;
                        list->size[j]++;
                        return 0;

                }else if(aux->downWord == aux && aux->data[0] == '\0'){

                    int q = i;

                            Node *Nulo = (Node*)malloc(sizeof(Node));
                            Nulo->data[0] = '\0';
                            Nulo->downWord = Nulo;
                            Nulo->nextChar = NULL;

                            aux->downWord = Nulo;

                            aux = Nulo;

                        while(Word[q] != '\0'){



                            Node *NewNode = (Node*)malloc(sizeof(Node));
                            aux->nextChar = NewNode;
                            NewNode->data[0] = Word[q];
                            NewNode->downWord = NewNode;
                            NewNode->nextChar = NULL;

                            aux = NewNode;
                            q++;
                        }

                        Node *NuloD = (Node*)malloc(sizeof(Node));
                        NuloD->data[0] = '\0';
                        NuloD->downWord = NULL;
                        NuloD->nextChar = NULL;

                        aux->nextChar = NuloD;
                        list->size[j]++;
                        return 0;

                }else{
                    aux = aux->downWord;
                    i--;
                }

            }
        }
    }
    return 0;
}

int show(WordList *list, char *Word){

    char palavra[50] = "";
    int tamanho = strlen(Word);

    Node *aux;
    for(int j = 0; j <= 25; j++){

        if(Word[0] == list->first[j]->data[0]){
            aux = list->first[j];

            for(int i = 0; i<tamanho; i++){

                if(aux->nextChar == NULL){
                    printf("No Word");
                    return 0;
                }

                if(aux->nextChar->data[0] == Word[i]){
                    strncat(palavra, aux->nextChar->data, 1);
                    aux = aux->nextChar;
                }else if(aux->downWord != aux){
                    aux = aux->downWord;
                    i--;
                }else if(aux->nextChar->data[0] == '\0' && aux->nextChar->nextChar != NULL){
                    aux = aux->nextChar;
                    i--;
                }
            }
            seek(aux, palavra);
        }
    }
    return 0;
}

void seek(Node *aux, char *Word){

    noList listNo;

    initNo(&listNo);

    while(aux->nextChar != NULL){

        if(aux->nextChar->data[0] == '\0'){
            printf("%s", Word);
        }
        if(aux->downWord != aux && aux->downWord != NULL){
            enqueue(&listNo, aux->downWord, Word);
        }
        if(aux->data != '\0'){
        strncat(Word, aux->nextChar->data, 1);
        }
        aux = aux->nextChar;
    }
    if(isEmpty(&listNo) == 0){
    downList(&listNo);
    }
}

#endif // Structure_Auto_Complete_h

