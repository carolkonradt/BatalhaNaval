/*#include <stdio_ext.h>*/
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>
#include "functions.h"

int main(){
int op, menuJogo=0, ColRand, LinRand, Lin, Col, countDica, conttestearq, flagganhaperde;
int subFlag=0, navFlag=0, cacaFlag=0, portFlag=0, meuSubFlag=0, meuNavFlag=0, meuCacaFlag=0, meuPortFlag=0;
char matUser[MAXLIN][MAXCOL], matComp[MAXLIN][MAXCOL], matX[MAXLIN][MAXCOL], posicDisp[3], escolha, testearq;

FILE *f;

setlocale(LC_ALL, "Portuguese");
srand(time(NULL));

printf("\t*** Bem-vindo ao jogo Batalha Naval! ***\nOpções:\n1. Jogo aleatório.\n2. Carregar jogo.\n3. Sobre o jogo.\n4. Sair.\n");
do{
    printf("Digite uma opção válida (1 a 4): ");
    scanf("%d", &op);}
while(op < 1 || op > 4);

while(op != 4){
    switch (op)
    {
    case 1:
    subFlag=0; navFlag=0; cacaFlag=0; portFlag=0; meuSubFlag=0; meuNavFlag=0; meuCacaFlag=0; meuPortFlag=0, countDica=0;
    geraMatriz(matUser, &LinRand, &ColRand);
    printf("\nUsuário:");
    imprimeMatriz(matUser);
    geraMatriz(matComp, &LinRand, &ColRand);
    geraMatX(matX);
    printf("\nComputador:");
    imprimeMatriz(matX);

    do{
        printf("\nOpções de Jogo:\n1.Disparar\n2.Dica\n3.Salvar\n4.Sobre o jogo\n5.Sair\n");
        do{
            printf("Digite uma opção válida (1 a 5):");
            scanf("%d", &menuJogo);}
        while(menuJogo < 1 || menuJogo > 5);


        switch(menuJogo){
        case 1:
            do{
                printf("\n");
                if(meuSubFlag<2)
                    printf("S. Submarino.\n");
                if(meuPortFlag<4)
                    printf("P. Porta Avião.\n");
                if(meuNavFlag<3)
                    printf("N. Navio de Escolta.\n");
                if(meuCacaFlag<2)
                    printf("C. Caça.\n");
                printf("Digite uma letra válida para a embarcação disponível: ");
                scanf("\n%c", &escolha);}
            while(escolha != 'S' && escolha != 'P' && escolha != 'N' && escolha != 'C');

            if((escolha == 'S' && meuSubFlag < 2) || (escolha == 'P' && meuPortFlag < 4 ) || (escolha == 'N' && meuNavFlag < 3) || (escolha == 'C' && meuCacaFlag <2)){
                do{
                    printf("Insira uma posição válida para atirar. Ex.(A3): ");
                    scanf("%s", &posicDisp);

                    Lin=posicDisp[0]-65;
                    Col=posicDisp[1]-49;

                    if(Lin<0 || Lin>=MAXLIN || Col<0 || Col>=MAXCOL)
                        printf("Posição inválida!\n");
                }while(Lin<0 || Lin>=MAXLIN || Col<0 || Col>=MAXCOL);

                switch(escolha){
                    case 'S':
                        dispSub(matComp, matX, Col, Lin, &subFlag, &portFlag, &navFlag, &cacaFlag);
                    break;
                    case 'P':
                        dispPortAvi(matComp, matX, Col, Lin, &subFlag, &portFlag, &navFlag, &cacaFlag);
                    break;
                    case 'N':
                        dispNavEsc(matComp, matX, Col, Lin, &subFlag, &portFlag, &navFlag, &cacaFlag);
                    break;
                    case 'C':
                        dispCac(matComp, matX, Col, Lin, &subFlag, &portFlag, &navFlag, &cacaFlag);
                    break;}

                if(verificaVenceu(&subFlag, &portFlag, &navFlag, &cacaFlag) == 1){
                    flagganhaperde=1;/*1=ganha 2=perde*/}
                else
                    compDisp(matUser, &subFlag, &portFlag, &navFlag, &cacaFlag, &meuSubFlag, &meuPortFlag, &meuNavFlag, &meuCacaFlag);
               /* __fpurge(stdin);*/
                fflush(stdin);
                printf("\nUsuário:");
                imprimeMatriz(matUser);
                printf("\nComputador:");
                imprimeMatriz(matX);

                if(verificaPerdeu(&meuSubFlag, &meuPortFlag, &meuNavFlag, &meuCacaFlag) == 1)
                    flagganhaperde=2; /*1= ganhou 2=perdeu*/}
            else
                printf("Embarcação inválida! Já está afundada.\n");
        break;

        case 2:
            if(countDica > 2)
                printf("Quantidade máxima de dicas atingida!\n");
            else{
                do{
                    printf("Insira uma posição válida. Ex.(A3):");
                    scanf("%s", &posicDisp);

                    Lin=posicDisp[0]-65;
                    Col=posicDisp[1]-49;

                if(Lin<0 || Lin>=MAXLIN || Col<0 || Col>=MAXCOL){
                    printf("Posição inválida!\n");}
                }while(Lin<0 || Lin>=MAXLIN || Col<0 || Col>=MAXCOL);
                dica(matComp, Lin, Col);
                countDica++;}
            break;

        case 3:
            f=fopen("jogosalvo.txt", "w");
            if(f==NULL)
                perror("jogosalvo.txt");

            else{
                salvaMatriz(matUser, f);
                salvaMatriz(matComp, f);
                salvaMatriz(matX, f);
                fprintf(f, "%d", subFlag);
                fprintf(f, "%d", portFlag);
                fprintf(f, "%d", navFlag);
                fprintf(f, "%d", cacaFlag);
                fprintf(f, "%d", meuSubFlag);
                fprintf(f, "%d", meuPortFlag);
                fprintf(f, "%d", meuNavFlag);
                fprintf(f, "%d", meuCacaFlag);
                fprintf(f, "%d", countDica);
                fclose(f);
                printf("Jogo salvo com sucesso!\n");
            }

            break;

        case 4:
            printf("Jogo Batalha Naval, desenvolvido por Ana Carolina Konradt e Vanessa Aldrighi\n como trabalho final da disciplina de Programação de Computadores, semestre 2021/2.\n\nInstruções:\nJogo Aleatório: Gera um novo jogo.\n Carregar: Carrega um jogo salvo anteriormente.\nSair: Sai do jogo.\nComo jogar:\nNa tabela do jogador há a representação de cada embarcação através da sua respectiva letra inicial (Caça, Submarino, Navio de escolta e Porta-avião). A água é representada pelo caractere “~”. Se algum tiro acertar sua frota, o caractere será substituído por “X”, se for tiro na água será “*”.\nCaso acerte um disparo na frota do computador, será revelado qual foi atingida pelo seu respectivo caractere,caso for tiro na água, será revelado sua representação: “~”.\nSeu objetivo é destruir todas as frotas existentes de seu adversário!\nDisparo: Mostra as embarcações disponíveis para realizar o disparo de escolha no local desejado.\nCaça: Disparo em estrela.\n Porta-avião: Disparo cascata vertical.\nSubmarino: Disparo comum.\nNavio de escolta: Disparo cascata horizontal.\nDica: Fornece uma dica sobre a existência de frota na linha ou coluna da posição indicada (máximo 3 dicas por jogo).\nSalvar: Salva o jogo no estado atual para futuro carregamento.\nBom jogo!\n");
            break;

        case 5:
            op=4;
            printf("Saindo do jogo!\n");
            break;

        default:
            printf("Digite uma opção válida!\n ");
            break;}
    }while(menuJogo!=5 && verificaPerdeu(&meuSubFlag, &meuPortFlag, &meuNavFlag, &meuCacaFlag) == 0 && verificaVenceu(&subFlag, &portFlag, &navFlag, &cacaFlag) == 0);
    break;


    case 2:
        conttestearq=0;
        f=fopen("jogosalvo.txt", "r");
        if(f==NULL){
            printf("\nNão há jogo salvo!\n");
            perror("jogosalvo.txt");
            printf("\n");}
        else{
           while (fscanf(f, "%c", &testearq) != EOF){
                conttestearq++;
            }
            if(conttestearq==0){
               printf("Não há jogo salvo!\n\n");
               fclose(f);
            }
            else{
                fclose(f);
                f=fopen("jogosalvo.txt", "r");
                carregaMatrizes(f, matUser, matComp, matX);
                fclose(f);
                f=fopen("jogosalvo.txt", "r");
                carregaconts(f, &subFlag, &portFlag, &navFlag, &cacaFlag, &meuSubFlag, &meuPortFlag, &meuNavFlag, &meuCacaFlag, &countDica);

                    do{
                    printf("\nOpções de Jogo:\n1.Disparar\n2.Dica\n3.Salvar\n4.Sobre o jogo\n5.Sair\n");
                    printf("Digite uma opção válida (1 a 5): ");
                    scanf("%d", &menuJogo);
                    switch(menuJogo){
                    case 1:
                        do{
                             printf("\n");
                            if(meuSubFlag<2)
                                printf("S. Submarino.\n");
                            if(meuPortFlag<4)
                                printf("P. Porta Avião.\n");
                            if(meuNavFlag<3)
                                printf("N. Navio de Escolta.\n");
                            if(meuCacaFlag<2)
                                printf("C. Caça.\n");
                            printf("Digite uma letra válida para a embarcação disponível: ");
                            scanf("\n%c", &escolha);}
                        while(escolha != 'S' && escolha != 'P' && escolha != 'N' && escolha != 'C');

                        if((escolha == 'S' && meuSubFlag < 2) || (escolha == 'P' && meuPortFlag < 4 ) || (escolha == 'N' && meuNavFlag < 3) || (escolha == 'C' && meuCacaFlag <2)){
                            do{
                                printf("Insira uma posição válida para atirar. Ex.(A3): ");
                                scanf("%s", &posicDisp);

                                Lin=posicDisp[0]-65;
                                Col=posicDisp[1]-49;

                                if(Lin<0 || Lin>=MAXLIN || Col<0 || Col>=MAXCOL){
                                    printf("Posição inválida!\n");
                                }
                            }while(Lin<0 || Lin>=MAXLIN || Col<0 || Col>=MAXCOL);


                            switch(escolha){
                                case 'S':
                                    dispSub(matComp, matX, Col, Lin, &subFlag, &portFlag, &navFlag, &cacaFlag);
                                break;
                                case 'P':
                                    dispPortAvi(matComp, matX, Col, Lin, &subFlag, &portFlag, &navFlag, &cacaFlag);
                                break;
                                case 'N':
                                    dispNavEsc(matComp, matX, Col, Lin, &subFlag, &portFlag, &navFlag, &cacaFlag);
                                break;
                                case 'C':
                                    dispCac(matComp, matX, Col, Lin, &subFlag, &portFlag, &navFlag, &cacaFlag);
                                break;}

                            if(verificaVenceu(&subFlag, &portFlag, &navFlag, &cacaFlag) == 1){
                                flagganhaperde=1;/*1=ganha 2=perde*/}
                            else
                                compDisp(matUser, &subFlag, &portFlag, &navFlag, &cacaFlag, &meuSubFlag, &meuPortFlag, &meuNavFlag, &meuCacaFlag);

                            fflush(stdin);
                            printf("\nUsuário:");
                            imprimeMatriz(matUser);
                            printf("\nComputador:");
                            imprimeMatriz(matX);

                            if(verificaPerdeu(&meuSubFlag, &meuPortFlag, &meuNavFlag, &meuCacaFlag) == 1)
                                flagganhaperde=2; /*1= ganhou 2=perdeu*/
                        }
                        else
                            printf("Embarcação inválida! Já está afundada.\n");
                    break;

                    case 2:
                        if(countDica > 2)
                            printf("Quantidade máxima de dicas atingida!\n");
                        else{
                            do{
                                printf("Insira uma posição válida. Ex.(A3):");
                                scanf("%s", &posicDisp);

                                Lin=posicDisp[0]-65;
                                Col=posicDisp[1]-49;

                            if(Lin<0 || Lin>=MAXLIN || Col<0 || Col>=MAXCOL){
                                printf("Posição inválida!\n");}
                            }while(Lin<0 || Lin>=MAXLIN || Col<0 || Col>=MAXCOL);
                            dica(matComp, Lin, Col);
                            countDica++;}
                        break;

                    case 3:
                        f=fopen("jogosalvo.txt", "w");
                        if(f==NULL){
                            printf("Não há jogo salvo!\n");
                            perror("jogosalvo.txt");
                            }
                        else{
                            salvaMatriz(matUser, f);
                            salvaMatriz(matComp, f);
                            salvaMatriz(matX, f);
                            fprintf(f, "%d", subFlag);
                            fprintf(f, "%d", portFlag);
                            fprintf(f, "%d", navFlag);
                            fprintf(f, "%d", cacaFlag);
                            fprintf(f, "%d", meuSubFlag);
                            fprintf(f, "%d", meuPortFlag);
                            fprintf(f, "%d", meuNavFlag);
                            fprintf(f, "%d", meuCacaFlag);
                            fprintf(f, "%d", countDica);
                            fclose(f);
                            printf("Jogo salvo com sucesso!\n");
                        }
                       /* f=fopen("contsedicassalvas.txt", "w");
                        if(f==NULL)
                            perror("contsedicassalvas.txt");
                        else{

                            fclose(f);
                        }*/

                        break;

                    case 4:
                        printf("\nJogo Batalha Naval, desenvolvido por Ana Carolina Konradt e Vanessa Aldrighi como trabalho final da disciplina de Programação de Computadores, semestre 2021/2.\n\nInstruções:\nJogo Aleatório: Gera um novo jogo.\nCarregar: Carrega um jogo salvo anteriormente.\nSair: Sai do jogo.\nDisparo: Mostra as embarcações disponíveis para realizar o disparo de escolha no local desejado.\nCaça: Disparo em estrela.\nPorta-avião: Disparo cascata vertical.\nSubmarino: Disparo comum.\nNavio de escolta: Disparo cascata horizontal.\nDica: Fornece uma dica sobre a existência de frota na linha ou coluna da posição indicada (máximo 3 dicas por jogo).\nSalvar: Salva o jogo no estado atual para futuro carregamento.\n\nComo jogar:\nSeu objetivo é destruir todas as frotas do adversário.O tiro revelará o que foi atingido:\nPara matriz do computador:\n ~ : aguá\nS ou C ou N ou P: nome da frota correspondente a letra inicial.\nPara matriz do usuário:\n* : tiro na água.\nX : Tiro na frota.\n\nBom jogo!\n");
                        break;

                    case 5:
                        op=4;
                        break;

                    default:
                        printf("Digite uma opção válida!\n ");
                        break;}
                }while(menuJogo!=5 && verificaPerdeu(&meuSubFlag, &meuPortFlag, &meuNavFlag, &meuCacaFlag) == 0 && verificaVenceu(&subFlag, &portFlag, &navFlag, &cacaFlag) == 0);
            }
                        fclose(f);
                    }

        break;

    case 3:
        printf("\nJogo Batalha Naval, desenvolvido por Ana Carolina Konradt e Vanessa Aldrighi como trabalho final da disciplina de Programação de Computadores, semestre 2021/2.\n\nInstruções:\nJogo Aleatório: Gera um novo jogo.\nCarregar: Carrega um jogo salvo anteriormente.\nSair: Sai do jogo.\nDisparo: Mostra as embarcações disponíveis para realizar o disparo de escolha no local desejado.\nCaça: Disparo em estrela.\nPorta-avião: Disparo cascata vertical.\nSubmarino: Disparo comum.\nNavio de escolta: Disparo cascata horizontal.\nDica: Fornece uma dica sobre a existência de frota na linha ou coluna da posição indicada (máximo 3 dicas por jogo).\nSalvar: Salva o jogo no estado atual para futuro carregamento.\n\nComo jogar:\nSeu objetivo é destruir todas as frotas do adversário.O tiro revelará o que foi atingido:\nPara matriz do computador:\n ~ : aguá\nS ou C ou N ou P: nome da frota correspondente a letra inicial.\nPara matriz do usuário:\n* : tiro na água.\nX : Tiro na frota.\n\nBom jogo!\n");
    break;
    case 4:
        printf("Saindo do jogo!\n");
    break;
}

    if(menuJogo!=5 || verificaPerdeu(&meuSubFlag, &meuPortFlag, &meuNavFlag, &meuCacaFlag) == 1 || verificaVenceu(&subFlag, &portFlag, &navFlag, &cacaFlag) == 1){
        countDica = 0;/*Resetando os contadores*/
        subFlag=0;
        navFlag=0;
        portFlag=0;
        cacaFlag=0;
        meuSubFlag=0;
        meuNavFlag=0;
        meuCacaFlag=0;
        meuPortFlag=0;
        if(flagganhaperde==1)
            printf("\nParabéns, você ganhou!\n");
        else
            if(flagganhaperde==2)
                printf("\nQue pena, você perdeu!\n");

        flagganhaperde=0;
        printf("1.Ir para o menu.\n2.Sair.\n");
        do{
            printf("Digite uma opção válida:");
            scanf("%d", &op);}
        while(op < 1 || op > 2);

        if(op==1){
        printf("\n\nOpções:\n1. Jogo aleatório.\n2. Carregar jogo.\n3. Sobre o jogo.\n4. Sair.\n");
        do{
            printf("Digite uma opção válida (1 a 4): ");
            scanf("%d", &op);}
        while(op < 1 || op > 4);
        }else
            op=4;
        }
}
return 0;
}
