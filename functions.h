#define MAXLIN 8
#define MAXCOL 8

void geraMatriz(char mat[][MAXCOL], int *LinRand, int *ColRand);
void preencheAgua(char mat[][MAXCOL]);
void geraPosic(char mat[][MAXCOL], int tamanho, int ***LinRand, int ***ColRand);
void submarino(char mat[][MAXCOL], int **LinRand, int **ColRand);
void aviCac(char mat[][MAXCOL], int **LinRand, int **ColRand);
void portaAvi(char mat[][MAXCOL], int **LinRand, int **ColRand);
void navEsc(char mat[][MAXCOL], int **LinRand, int **ColRand);
void imprimeMatriz(char mat[][MAXCOL]);
void geraMatX(char mat[][MAXCOL]);

void dispSub(char mat[][MAXCOL], char matX[][MAXCOL], int Col, char Lin, int *subFlag, int *portFlag, int *navFlag, int *cacaFlag);
void dispPortAvi(char mat[][MAXCOL], char matX[][MAXCOL], int Col, char Lin, int *subFlag, int *portFlag, int *navFlag, int *cacaFlag);
void dispNavEsc(char mat[][MAXCOL], char matX[][MAXCOL], int Col, char Lin, int *subFlag, int *portFlag, int *navFlag, int *cacaFlag);
void dispCac(char mat[][MAXCOL], char matX[][MAXCOL], int Col, char Lin, int *subFlag, int *portFlag, int *navFlag, int *cacaFlag);


void compDisp(char matUser[][MAXCOL], int *subFlag, int *portFlag, int *navFlag, int *cacaFlag, int *meuSubFlag, int *meuPortFlag, int *meuNavFlag, int *meuCacaFlag);
void userFlag(char matUser[][MAXCOL], int **meuSubFlag, int **meuPortFlag, int **meuNavFlag, int **meuCacaFlag, int Lin, int Col);
void compFlag(char mat[][MAXCOL], int **subFlag, int **portFlag, int **navFlag, int **cacaFlag, int Lin, int Col);
void preencheDispNoUser(char matUser[][MAXCOL], int Lin, int Col);

int verificaPerdeu(int *meuSubFlag, int *meuPortFlag, int *meuNavFlag, int *meuCacaFlag);
int verificaVenceu(int *subFlag, int *portFlag, int *navFlag, int *cacaFlag);

void dica(char mat[][MAXCOL], int Lin, int Col);

void salvaMatriz (char mat[][MAXCOL], FILE *f);

void carregaMatrizes (FILE *f, char matUser[][MAXCOL], char matComp[][MAXCOL], char matX[][MAXCOL]);
void carregaconts(FILE *f, int *subFlag, int *portFlag, int *navFlag, int *cacaFlag, int *meuSubFlag, int *meuPortFlag, int *meuNavFlag, int *meuCacaFlag, int *countdica);
void matCarregada(char vet[65], char mat[][MAXCOL]);

