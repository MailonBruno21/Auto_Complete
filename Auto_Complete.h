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

//ESTRUTURA PARA ARMAZENAR OS ELEMENTOS PARA IMPRESS�O
typedef struct No{
    struct Node *no;
    struct No *nextNo;
    char WordNo[50];
}No;
//ESTRUTURA DO PRIMEIRO N� DA LISTA DE IMPRESS�O
typedef struct noList{
    No *firstNo;
    int sizeNo;
}noList;
//ESTRUTURA DO PRIMEIRO N� DA LISTA DE ARMAZENAMENTO DAS LETRAS
typedef struct WordList{
    Node *first[25];
    int size[25];
}WordList;

void init(WordList *list);// FUN��O QUE INICIA A LISTA QUE ARMAZENA AS LETRAS
void initNo(noList *lista);// FUN��O QUE INICIA A LISTA DA IMPRESS�O
void downList(noList *lista);//FUN��O QUE IMPRIME AS OP��ES DE PONTEIRO DOWNWORD
int enqueue(noList *lista, Node *aux, char *Word);//FUN��O QUE GUARDA OS PONTEIROS DOWNWORD EM UMA LINKEDLIST
int add (WordList *list, char *Word);//ADICIONA AS PALAVRAS
void seek (Node *aux, char *Word);//FUN��O AUXILIAR QUE IMPRIME AS PALAVRAS
int show(WordList *list, char *Word);//FUN��O QUE GERENCIA A IMPRESS�O DAS PALAVRAS
bool isEmpty(noList *lista);//VERIFICA SE A LISTA EST� VAZIA

//------------------------------------------------------------------------------------//

void init(WordList *list){
    //CRIANDO INDICES DE A AT� Z DO TIPO NODE
    for(int aux = 0; aux <= 25 ; aux++){
        Node *indice = (Node*)malloc(sizeof(Node));
        indice->data[0] = 65 + aux;
        indice->downWord = NULL;    //ANULANDO O DOWNWORD DO INDICE
        indice->nextChar = NULL;    //DEIXANDO VAZIO O NEXTCHAR
        list->first[aux] = indice;
        list->size[aux]  = 0;       //CONTADOR DE PALAVRAS EM CADA INDICE
    }
}

int add (WordList *list, char *Word){

    Node *aux;  //USADO PARA AUXILIAR AS OPERA��ES
    int tamanho = strlen(Word); //RECEBE A QUATIDADE DE LETRAS QUE CONT�M A PALAVRA A SER ADICIONADA

    //INICIO - VERIFICA QUAL O INDICE DA PALAVRA
    for(int j = 0; j <= 25; j++){
        if(list->first[j]->data[0] == Word[0] ){
            aux = list->first[j];
    //FIM
            for(int i = 0; i <= tamanho; i++){                          //FAZ A CONTAGEM DA QUANTIDADE DE CHAR QUE SER� ADD

                if(aux == list->first[j] && aux->nextChar == NULL){    //VERIFICA SE O INDICE N�O APONTA PARA ALGUMA LETRA
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
                if(Word[i] == aux->nextChar->data[0]){      //VERIFICA SE A LETRA J� SE ENCONTRA NA LISTA OU SE � UM N� NULO
                    aux = aux->nextChar;
                }else if(aux->nextChar->data[0] == '\0' && aux->nextChar->nextChar == NULL){    //ADD OS CARACTERES DA PALAVRA NA FRENTE DA LISTA
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
                }else if(aux->nextChar->data[0] == '\0' && aux->nextChar->nextChar->data[0] == Word[i]){ //ELE VERIFICA SE O VALOR COMPARADO � UM NO NULO E SE O N� SEGUINTE � IGUAL AO QUE SER� ADD
                    aux = aux->nextChar->nextChar;
                }else if (aux->downWord == aux && aux->data[0] != '\0'){//VERIFICA SE N�O H� LETRAS NO N� QUE APONTA PARA BAIXO
                    int q = i;
                    //NESSE PONTO ELE CRIA O N� NULO DE BAIXO QUE IDICA QUE CONT�M LETRAS EM BAIXO
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
                }else if(aux->downWord == aux && aux->data[0] == '\0'){//ADICIONA A PALAVRA EM BAIXO DE TUDO CASO JA TENHA UMA PALAVRA ESCRITA EM BAIXO
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
                    //PULA PARA A LINHA DE BAIXO E REFAZ O CICLO COMPARANDO AS LETRAS
                    aux = aux->downWord;
                    i--;
                }
            }
        }
    }
    return 0;
}

int show(WordList *list, char *Word){

    char palavra[50] = "";          //ONDE SER� CONCATENADO AS PALAVRAS
    int tamanho = strlen(Word), i;  // TAMANHO RECEBE A QUATIDADE DE CARACTERS DA PALAVRA E I � UMA VARIAVEL DE CONTROLE
    Node *aux;                      //NODE AUXILIAR PARA AS OPERA��ES
    //PROCURA EM QUAL LISTA EST� A PALAVRA
    for(int j = 0; j <= 25; j++){
        if(Word[0] == list->first[j]->data[0]){//COMPARANDO AS INICIAIS COM O INDICE
            aux = list->first[j];
            for(i = 0; i<tamanho; i++){ //RODA AT� O TAMANHO DA PALAVRA
                if(aux->nextChar == NULL){ //VERIFICA SE A LISTA TEM O PRIMEIRO N�
                    printf("No Word");
                    return 0;
                }
                if(aux->nextChar->data[0] == Word[i]){ //COMPARA O CARACTER DA BUSCA COM OS DOS NOS
                    strncat(palavra, aux->nextChar->data, 1);//CONCATENA CADA CARACTER  IGUAL
                    aux = aux->nextChar;  //AVAN�A PARA PROXIMO N�
                }else if(aux->downWord != aux){//VERIFICA SE ALGUM N� EM BAIXO
                    aux = aux->downWord;  //ATRIBUI AUX PARA LINHA DA BAIXO
                    i--; //SUBTRAI O I PARA COMPARAR A O MESMO CARACTER
                }else if(aux->nextChar->data[0] == '\0' && aux->nextChar->nextChar != NULL){//VERIFICA SE EST� COMPARANDO COM UM N� NULO
                    aux = aux->nextChar;
                    i--;
                }
            }
            if(Word[tamanho] != aux->nextChar->data[0] && i != 1){//FAZ O CONTROLE DE BUSCA CASO A PALAVRA BUSCADA N�O CONTENHA NA LISTA
                printf("PALAVRA NAO ENCONTRADA\n");
                return 0;
            }else{
                seek(aux, palavra); //CHAMA FU��O QUE ANALIZA E IMPRIME A LINHA
            }
        }
    }
    system("pause");
    return 0;
}

void seek(Node *aux, char *Word){

    noList listNo; //CRIA A LISTA QUE VAI ARMAZENAR OS VALORES DOS DOWNWORD

    initNo(&listNo); //INICIA A LISTA

    while(aux->nextChar != NULL){ //WHILE RODA ATE O ULTIMO CARACTER DA LINHA

        if(aux->nextChar->data[0] == '\0'){//VERIFICA SE TERMINHA UMA PALAVRA PARA PODER IMPRIMIR
            printf("%s", Word);
        }
        if(aux->downWord != aux && aux->downWord != NULL){//VERIFICA SE TEM UMA PALAVRAS EM BAIXO
            enqueue(&listNo, aux->downWord, Word);  //FUN��O QUE ADD UM DOWNWORD NA LISTA E PASSA O QUE JA FOI CONCATENADO EM WORD
        }
        if(aux->data != '\0'){//CONCATENA A LETRA CASO SEJA UMA LETRA VALIDA
        strncat(Word, aux->nextChar->data, 1);
        }
        aux = aux->nextChar;
    }
    if(isEmpty(&listNo) == 0){ //SE A LISTA N�O FOR NULA CHAMAR A FUN��O
    downList(&listNo);// FUN��O QUE CHAMA A ANALISE DA LISTA COM OS DOWNWORD
    }
}

void initNo(noList *lista){ //INICIA A LISTA DE DOWNWORD COM TUDO ZERADO
        lista->firstNo = NULL;
        lista->sizeNo = 0;
}

bool isEmpty(noList *lista){ //VERIFICA SE A LISTA � VAZIA
    return(lista->sizeNo == 0);
}

void downList(noList *lista){ //
    No *aux; //NO AUXILIAR QUE AJUDA NA OPERA��O
    int i = 0;
    aux = lista->firstNo;//AUX � O PRIMEIRO NO DA LISTA DE DOWNWORD
    while(i < lista->sizeNo){// RODA AT� O ULTIMO N� DA LISTA
        seek(aux->no, aux->WordNo); //CHAMA PARA ANALIZAR E IMPRIMIR A LINHA DO DOWNWORD GUARDADO
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

#endif // Structure_Auto_Complete_h

