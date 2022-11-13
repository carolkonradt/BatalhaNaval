#include<stdio.h>
#define MAXLIN 8
#define MAXCOL 8

void geraMatriz(char mat[][MAXCOL], int *LinRand, int *ColRand){ /*Função pra chamar todas funções de gerar a matriz pra ficar menos coisas*/
    preencheAgua(mat);
    submarino(mat, &LinRand, &ColRand);
    aviCac(mat,&LinRand, &ColRand);
    portaAvi(mat,&LinRand, &ColRand);
    navEsc(mat,&LinRand, &ColRand);
}
void geraMatX(char mat[][MAXCOL]){ /*Gera uma matriz de X para funcionar como máscara da matriz do computador*/
    int i, j;
    for(i=0; i<MAXLIN; i++){
        for(j=0; j<MAXCOL; j++){
            mat[i][j]='X';
        }}
}

void preencheAgua(char mat[][MAXCOL]){
    int i, j;
    for (i=0;i<MAXLIN; i++)
        for (j=0;j <MAXCOL;j++)
            mat[i][j] = '~';
}

void geraPosic(char mat[][MAXCOL], int tamanho, int ***LinRand, int ***ColRand){
    int aux, aux2, i, j, flag;

    do{
    flag = 0;
    aux2 = tamanho;
    ***LinRand = rand()%8; /*gera uma linha qualquer pra colocar a embarcação*/
    ***ColRand = rand()%(8-tamanho+1); /*gera um posição pra coluna levando em consideração o tamanho da embarcação pra n sair da matriz*/
    aux = ***ColRand;

    for (i=0;i<MAXLIN; i++)
        for (j=0;j <MAXCOL;j++)
            if(***LinRand == i && aux == j && aux2 > 0){
                aux2--;
                aux++;
                if(mat[i][j] != '~')
                    flag = 1; /*Verifica se não tem outra embarcação no lugar, se tiver gera outra posição*/
            }}
    while(flag == 1);
}

void imprimeMatriz(char mat[][MAXCOL]){
    printf("\n\n");
    int i,j;
    char vet[8] = "ABCDEFGH";
    printf("    1 2 3 4 5 6 7 8\n\n");
    for (i=0 ; i<MAXLIN; i++){
        printf("%c   ", vet[i]);
        for (j=0 ; j<MAXCOL; j++)
            printf("%c " , mat[i][j]);
    printf("\n");}}

void submarino(char mat[][MAXCOL], int **LinRand, int **ColRand){
    int i, j, tamanho, aux;
    tamanho = 2;
    geraPosic(mat, tamanho,  &LinRand, &ColRand); /* chama a função pra gerar a posição*/
    aux = **ColRand;

    for (i=0;i<MAXLIN; i++)
        for (j=0;j <MAXCOL;j++)
            if((**LinRand == i && aux == j) && tamanho > 0){
                tamanho--;
                mat[i][j] = 'S';
                aux++;} /*Aumenta a coluna pra ficar dentro do if até colocar todos os caracteres pelo tamanho da embarcação*/
}

void aviCac(char mat[][MAXCOL], int **LinRand, int **ColRand){
    int i, j, tamanho, aux;
    tamanho = 2;
    geraPosic(mat, tamanho,  &LinRand, &ColRand);
    aux = **ColRand;

    for (i=0;i<MAXLIN; i++)
        for (j=0;j <MAXCOL;j++)
            if((**LinRand == i && aux == j) && tamanho > 0){
                tamanho--;
                mat[i][j] = 'C';
                aux++;}
}

void portaAvi(char mat[][MAXCOL], int **LinRand, int **ColRand){
    int i, j, tamanho, aux;
    tamanho = 4;
    geraPosic(mat, tamanho,  &LinRand, &ColRand);
    aux = **ColRand;

    for (i=0;i<MAXLIN; i++)
        for (j=0;j <MAXCOL;j++)
            if((**LinRand == i && aux == j) && tamanho > 0){
                tamanho--;
                mat[i][j] = 'P';
                aux++;}
}

void navEsc(char mat[][MAXCOL], int **LinRand, int **ColRand){
    int i, j, tamanho, aux;
    tamanho = 3;
    geraPosic(mat, tamanho,  &LinRand, &ColRand);
    aux = **ColRand;

    for (i=0;i<MAXLIN; i++)
        for (j=0;j <MAXCOL;j++)
            if((**LinRand == i && aux == j) && tamanho > 0){
                tamanho--;
                mat[i][j] = 'N';
                aux++;}
}


void dispSub(char mat[][MAXCOL], char matX[][MAXCOL], int Col, char Lin, int *subFlag, int *portFlag, int *navFlag, int *cacaFlag){
    matX[Lin][Col]= mat[Lin][Col];
    compFlag(mat, &subFlag, &portFlag, &navFlag, &cacaFlag,  Lin, Col);
}

void dispPortAvi(char mat[][MAXCOL], char matX[][MAXCOL], int Col, char Lin, int *subFlag, int *portFlag, int *navFlag, int *cacaFlag){
    int i;

    for(i=0; i<=1; i++){
        if((Lin+i)<=(MAXLIN-1)){ /*não permite sair da matriz*/
            matX[Lin+i][Col]=mat[Lin+i][Col];
            compFlag(mat, &subFlag, &portFlag, &navFlag, &cacaFlag,  Lin+i, Col);}
    }
}

void dispNavEsc(char mat[][MAXCOL], char matX[][MAXCOL], int Col, char Lin, int *subFlag, int *portFlag, int *navFlag, int *cacaFlag){
 int i;

    for(i=0; i<=1; i++){
        if((Col+i)<=(MAXCOL-1)){ /*não permite sair da matriz*/
            matX[Lin][Col+i]=mat[Lin][Col+i];
            compFlag(mat, &subFlag, &portFlag, &navFlag, &cacaFlag,  Lin, Col+i);}
    }
}

void dispCac(char mat[][MAXCOL], char matX[][MAXCOL], int Col, char Lin, int *subFlag, int *portFlag, int *navFlag, int *cacaFlag){
    int i;

    for(i=-1; i<=1; i++){
        if(i==0){
            matX[Lin][Col]=mat[Lin][Col];
            compFlag(mat, &subFlag, &portFlag, &navFlag, &cacaFlag,  Lin, Col);}
            else{
            if((Lin+i)<=(MAXLIN-1)&&(Lin+i)>=0){ /*não permite sair da matriz*/
                matX[Lin+i][Col]=mat[Lin+i][Col];
                compFlag(mat, &subFlag, &portFlag, &navFlag, &cacaFlag,  Lin+i, Col);
                }

            if((Col+i)<=(MAXCOL-1)&&(Col+i)>=0){ /*não permite sair da matriz*/
                matX[Lin][Col+i]=mat[Lin][Col+i];
                compFlag(mat, &subFlag, &portFlag, &navFlag, &cacaFlag,  Lin, Col+i);}
            }
        }
}

void compDisp(char matUser[][MAXCOL], int *subFlag, int *portFlag, int *navFlag, int *cacaFlag, int *meuSubFlag, int *meuPortFlag, int *meuNavFlag, int *meuCacaFlag){
    int i, tipoDisp, Col, Lin, flag;

    do{
        tipoDisp=rand()%4; /*gera um tipo de disparo(0-sub;1-caça;2-navio;3-porta-avião*/
        switch(tipoDisp){ /*checa se a embarcação do computador já afundou. se sim, gera uma nova para disparar*/
            case 0:
                if(*subFlag>=2)
                    flag=1;
                else
                    flag=0;
            break;
            case 1:
                if(*cacaFlag>=2)
                    flag=1;
                else
                    flag=0;
            break;
            case 2:
                if(*navFlag>=3)
                    flag=1;
                else
                    flag=0;
            break;
            case 3:
                if(*portFlag>=4)
                    flag=1;
                else
                    flag=0;
            break;
        }
    }while(flag==1);

    do{
    Lin=rand()%8;
    Col=rand()%8;}
    while(matUser[Lin][Col] == '*' || matUser[Lin][Col] == 'X' ); /*Pra n disparar onde já foi disparado*/

    switch(tipoDisp){
    case 0:
        userFlag(matUser, &meuSubFlag, &meuPortFlag, &meuNavFlag, &meuCacaFlag, Lin, Col);
        preencheDispNoUser(matUser, Lin , Col);
        break;
    case 1:
        for(i=-1; i<=1; i++){
            if(i==0){
                userFlag(matUser, &meuSubFlag, &meuPortFlag, &meuNavFlag, &meuCacaFlag, Lin, Col);
                preencheDispNoUser(matUser, Lin, Col);
            }else{
                if((Lin+i)<=(MAXLIN-1)&&(Lin+i)>=0){ /*não permite sair da matriz*/
                    userFlag(matUser, &meuSubFlag, &meuPortFlag, &meuNavFlag, &meuCacaFlag, Lin+i, Col);
                    preencheDispNoUser(matUser, Lin +i, Col);
                    }

                if((Col+i)<=(MAXCOL-1)&&(Col+i)>=0){ /*não permite sair da matriz*/
                    userFlag(matUser, &meuSubFlag, &meuPortFlag, &meuNavFlag, &meuCacaFlag, Lin, Col+i);
                    preencheDispNoUser(matUser, Lin, Col +i);}}}
    break;
    case 2:
        for(i=0; i<=1; i++){
            if((Col+i)<=(MAXCOL-1)){ /*não permite sair da matriz*/
                userFlag(matUser, &meuSubFlag, &meuPortFlag, &meuNavFlag, &meuCacaFlag, Lin, Col+i);
                preencheDispNoUser(matUser, Lin , Col+i);}}
    break;
    case 3:
        for(i=0; i<=1; i++){
            if((Lin+i)<=(MAXLIN-1)){ /*não permite sair da matriz*/
                userFlag(matUser, &meuSubFlag, &meuPortFlag, &meuNavFlag, &meuCacaFlag, Lin+i, Col);
                preencheDispNoUser(matUser, Lin +i, Col);}}
    break;}
}

void userFlag(char matUser[][MAXCOL], int **meuSubFlag, int **meuPortFlag, int **meuNavFlag, int **meuCacaFlag, int Lin, int Col){
    switch(matUser[Lin][Col]){
        case 'S':
            (**meuSubFlag)++;
                break;
        case 'P':
            (**meuPortFlag)++;
            break;
        case 'N':
            (**meuNavFlag)++;
            break;
        case 'C':
            (**meuCacaFlag)++;
            break;}
}

void compFlag(char mat[][MAXCOL], int **subFlag, int **portFlag, int **navFlag, int **cacaFlag, int Lin, int Col){

    switch(mat[Lin][Col]){
        case 'S':
            (**subFlag)++;
            break;
        case 'P':
            (**portFlag)++;
             break;
        case 'N':
            (**navFlag)++;
            break;
        case 'C':
            (**cacaFlag)++;
            break;
            }
}

void preencheDispNoUser(char matUser[][MAXCOL], int Lin, int Col){

    if(matUser[Lin][Col] == '~' || matUser[Lin][Col] == '*')
        matUser[Lin][Col] = '*';
    else
        matUser[Lin][Col] = 'X';
}

int verificaPerdeu(int *meuSubFlag, int *meuPortFlag, int *meuNavFlag, int *meuCacaFlag){

    if(*meuSubFlag >= 2 && *meuPortFlag >= 4 && *meuNavFlag >= 3 && *meuCacaFlag >=2){
        return 1;
    }
    else return 0;
}

int verificaVenceu(int *subFlag, int *portFlag, int *navFlag, int *cacaFlag){

    if(*subFlag >= 2 && *portFlag >= 4 && *navFlag >= 3 && *cacaFlag >=2){
        return 1;
    }
    else return 0;
}

void dica(char mat[][MAXCOL], int Lin, int Col){
    int i, flagL =0, flagC =0;
    for(i = 0; i < MAXCOL; i++)
        if(mat[Lin][i] == 'C' ||mat[Lin][i] == 'S' ||mat[Lin][i] == 'P' ||mat[Lin][i] == 'N')
            flagL = 1;

    for(i = 0; i < MAXLIN; i++)
        if(mat[i][Col] == 'C' || mat[i][Col] == 'S' || mat[i][Col] == 'P' || mat[i][Col] == 'N')
            flagC = 1;

    if(flagL == 1)
        printf("Há embarcações nessa linha!\n");
    else
        printf("Não há embarcações nessa linha!\n");
    if(flagC == 1)
        printf("Há embarcações nessa coluna!\n");
    else
        printf("Não há embarcações nessa coluna!\n");
    printf("\n");
}

void salvaMatriz (char mat[][MAXCOL], FILE *f){
    int i, j;

    for(i=0; i<MAXLIN; i++)
        for(j=0; j<MAXCOL; j++)
            fprintf(f, "%c", mat[i][j]);
}

void carregaMatrizes(FILE *f, char matUser[][MAXCOL], char matComp[][MAXCOL], char matX[][MAXCOL]){
    int i=0, j=0, k=0, cont=0;
    char vetuser[65], vetcomp[65], vetx[65];
    char temparq;

     while (fscanf(f, "%c", &temparq) != EOF){
                if(cont>=0 && cont<=63){
                    vetuser[i]=temparq;
                    /*printf("%c", vetuser[i]);*/
                    i++;
                }
               if(cont>=64 && cont<=127){
                    vetcomp[j]=temparq;
                    j++;
                }
                if(cont>=128 && cont<=191){
                    vetx[k]=temparq;
                    k++;
                }

                cont++;
            }
        matCarregada(vetuser, matUser);
        printf("\nUsuário:");
        imprimeMatriz(matUser);
        matCarregada(vetcomp, matComp);
        matCarregada(vetx, matX);
        printf("\nComputador:");
        imprimeMatriz(matX);
}

void carregaconts(FILE *f, int *subFlag, int *portFlag, int *navFlag, int *cacaFlag, int *meuSubFlag, int *meuPortFlag, int *meuNavFlag, int *meuCacaFlag, int *countdica){
    /*dividi em duas funções porque em uma só estava apresentando bug*/
    int contador=0;
    char temparq;
            while (fscanf(f, "%c", &temparq) != EOF){

                switch(contador){
                    case 192:
                        *subFlag=temparq-48;
                        break;

                    case 193:
                        *portFlag=temparq-48;
                        break;

                    case 194:
                        *navFlag=temparq-48;
                        break;

                    case 195:
                        *cacaFlag=temparq-48;
                        break;

                    case 196:
                        *meuSubFlag=temparq-48;
                        break;

                    case 197:
                        *meuPortFlag=temparq-48;
                        break;

                    case 198:
                        *meuNavFlag=temparq-48;
                        break;

                    case 199:
                        *meuCacaFlag=temparq-48;
                        break;

                    case 200:
                        *countdica=temparq-48;
                }

                contador++;
                }

}

void matCarregada(char vet[65], char mat[][MAXCOL]){
    int i, j, k=0;

    for(i=0; i<MAXLIN; i++)
        for(j=0; j<MAXCOL; j++){
            mat[i][j]=vet[k];
            k++;
        }

}

