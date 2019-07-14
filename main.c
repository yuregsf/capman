#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "termip.h"
#include <time.h>

typedef struct{
    int playerCol, playerRow, ghostCol, ghostRow, mapCol, mapRow, pontMax;
}configMapa;

typedef struct{
    int playerX, playerY;
    int pontos;
    char iniciais[10];
}player;

typedef struct{
    int ghostX, ghostY;
    int behaviour;
    int mov;
}ghost;
void genMap(char c[128]);
char **allocMatrix(int row, int col);
void freeMatrix(char **matrix, int size);
int movimentopacman(char **M, player *p, int acao, configMapa config);
void movimentoGhost(char **M, ghost *g, int acao, configMapa config, char *aux);
void printMatrix(char **M, int row, int col);
void menuPrincipal(void);
void menuMapas(void);
unsigned long int randMove(void);
void game(char **M, configMapa config);


int main(){
    menuPrincipal();
    return 0;
}



//Gera mapa baseado nos parâmetros do arquivo mapa
void genMap(char c[128]){
    FILE * mapaSelecionado;
    configMapa config;
    char line[256];
    int key;
    mapaSelecionado = fopen(c, "r");
    while(fgets(line, sizeof(line), mapaSelecionado)){
        if(strstr(line, "playerPos") != NULL){
            fscanf(mapaSelecionado, "%d", &config.playerCol);
            fscanf(mapaSelecionado, "%d", &config.playerRow);
        }
        if(strstr(line, "ghostPos") != NULL){
            fscanf(mapaSelecionado, "%d", &config.ghostCol);
            fscanf(mapaSelecionado, "%d", &config.ghostRow);
        }
        if(strstr(line, "map") != NULL){
            fscanf(mapaSelecionado, "%d", &config.mapCol);
            fscanf(mapaSelecionado, "%d", &config.mapRow);
            break;
        }
    }
    char **map = allocMatrix(config.mapRow, config.mapCol);
    for (int i = 0; i < config.mapRow; i++){
        fscanf(mapaSelecionado, "%s", line);
        for (int j = 0; j < config.mapCol; j++){
            map[i][j] = line[j];
        }            
    }

    // //Posição do jogador
    // map[config.playerRow][config.playerCol] = 'P';
    // //Spawn dos fantasmas
    // map[config.ghostRow][config.ghostCol] = 'G';

    game(map, config);
    
    freeMatrix(map, config.mapRow);
    fclose(mapaSelecionado);
} 

void game(char **M, configMapa config){
    int botao = 23363,auxmov = 23363;
    player p;
    ghost g1,g2,g3,g4;
    char auxG1, auxG2, auxG3, auxG4;
    auxG1 = auxG2 = auxG3 = auxG4 = '.';
    g1.ghostX = g2.ghostX = g3.ghostX = g4.ghostX = config.ghostCol;
    g1.ghostY = g2.ghostY = g3.ghostY = g4.ghostY = config.ghostRow;
    p.playerX = config.playerCol;
    p.playerY = config.playerRow;
    p.pontos = 0;
    while(1){
        clear();
        gotoxy(1,1);
        printf("Score: %d", p.pontos);
        gotoxy(2,1);
        printMatrix(M, config.mapRow, config.mapCol);
        botao = getch_timeout(0,150000);
        if(botao==-1){
            botao=auxmov;
        }
        auxmov = movimentopacman(M, &p, botao, config);
        movimentoGhost(M, &g1, randMove(), config, &auxG1);
        movimentoGhost(M, &g2, randMove(), config, &auxG2);
        movimentoGhost(M, &g3, randMove(), config, &auxG3);
        movimentoGhost(M, &g4, randMove(), config, &auxG4);
        if(botao == 'q'){
            break;
        }
        //Colisão
        if(p.playerX == g1.ghostX && p.playerY == g1.ghostY){
            menuPrincipal();
        }
        if(p.playerX == g2.ghostX && p.playerY == g2.ghostY){
            menuPrincipal();
        }
        if(p.playerX == g3.ghostX && p.playerY == g3.ghostY){
            menuPrincipal();
        }
        if(p.playerX == g4.ghostX && p.playerY == g4.ghostY){
            menuPrincipal();
        }
    }
}

char** allocMatrix(int row, int col){
    char **matrix = malloc(row*sizeof(char*));
    for(int i = 0; i < row; i++){
        matrix[i] = malloc(col*sizeof(char));
    }
    return matrix;
}

void freeMatrix(char **matrix, int row){
    for(int i = 0; i < row; i++){
        free(matrix[i]);
    }
    free(matrix);
}
int movimentopacman(char **M, player *p, int acao, configMapa config){
    if(acao == 23361){ //pra cima
        if((p->playerY)-1 < 0){     
            M[(p->playerY)][(p->playerX)] = ' '; 
            p->playerY = config.mapRow-1;
            M[(p->playerY)][(p->playerX)] = 'v'; 
        }
        if(M[(p->playerY)-1][(p->playerX)] == 'H'){     //Verificando se a posição a cima do Pac-Man é uma parede
        /*Nao altera mapa*/                      //Caso seja, não Efetue nenhuma ação
        }else{
            if(M[(p->playerY)-1][(p->playerX)] == '.'){
                p->pontos=p->pontos+10;
            }
            if(M[(p->playerY)-1][(p->playerX)] == '*'){
                p->pontos=p->pontos+50; 
            }
            if(M[(p->playerY)-1][(p->playerX)] == 'F'){
                p->pontos=p->pontos+100; 
            }
            M[(p->playerY)][(p->playerX)] = ' ';           //Deixando vazio por onde Pac_man passar
            (p->playerY) = (p->playerY) - 1;               //Atribuindo a nova posição à nosso personagem
            M[(p->playerY)][(p->playerX)] = 'v'; 
        }
    }
    if(acao == 23362){ //pra baixo
        if((p->playerY)+1 >= config.mapRow){     
            M[(p->playerY)][(p->playerX)] = ' '; 
            p->playerY = 0;
            M[(p->playerY)][(p->playerX)] = '^'; 
        }
        if(M[(p->playerY)+1][(p->playerX)] == 'H')     //Verificando se a posição a baixo do Pac-Man é uma parede
        {
        /*Nao altera mapa*/                      //Caso seja, não Efetue nenhuma ação
        }
    else{
        if(M[(p->playerY)+1][(p->playerX)] == '.'){
            p->pontos=p->pontos+10;
        }
        if(M[(p->playerY)+1][(p->playerX)] == '*'){
            p->pontos=p->pontos+50; 
        }
        if(M[(p->playerY)+1][(p->playerX)] == 'F'){
            p->pontos=p->pontos+100; 
        }
        M[(p->playerY)][(p->playerX)] = ' ';           //Deixando vazio por onde Pac_man passar
        (p->playerY) = (p->playerY) + 1;               //Atribuindo a nova posição à nosso personagem
        M[(p->playerY)][(p->playerX)] = '^'; 
    }
    }
    if(acao == 23363){ //pra direita
        if((p->playerX)+1 >= config.mapCol){     
            M[(p->playerY)][(p->playerX)] = ' '; 
            p->playerX = 0;
            M[(p->playerY)][(p->playerX)] = '<'; 
        }
        if(M[(p->playerY)][(p->playerX)+1] == 'H')     //Verificando se a posição a direita do Pac-Man é uma parede
            {
            /*Nao altera mapa*/                      //Caso seja, não Efetue nenhuma ação
            }
        else{
            if(M[(p->playerY)][(p->playerX)+1] == '.'){
                p->pontos=p->pontos+10;
            }
            if(M[(p->playerY)][(p->playerX)+1] == '*'){
                p->pontos=p->pontos+50; 
            }
            if(M[(p->playerY)][(p->playerX)+1] == 'F'){
                p->pontos=p->pontos+100; 
            }
            M[(p->playerY)][(p->playerX)] = ' ';           //Deixando vazio por onde Pac_man passar
            (p->playerX) = (p->playerX) +1;               //Atribuindo a nova posição à nosso personagem
            M[(p->playerY)][(p->playerX)] = '<'; 
        }
    }
    if(acao == 23364){ //pra esquerda
        if((p->playerX)-1 < 0){     
            M[(p->playerY)][(p->playerX)] = ' '; 
            p->playerX = config.mapCol-1;
            M[(p->playerY)][(p->playerX)] = '>'; 
        }
        if(M[(p->playerY)][(p->playerX)-1] == 'H')     //Verificando se a posição a esquerda do Pac-Man é uma parede
        {
        /*Nao altera mapa*/                      //Caso seja, não Efetue nenhuma ação
        }
        else{
            if(M[(p->playerY)][(p->playerX)-1] == '.'){
                p->pontos=p->pontos+10;
            }
            if(M[(p->playerY)][(p->playerX)-1] == '*'){
                p->pontos=p->pontos+50; 
            }
            if(M[(p->playerY)][(p->playerX)-1] == 'F'){
                p->pontos=p->pontos+100; 
            }
            M[(p->playerY)][(p->playerX)] = ' ';           //Deixando vazio por onde Pac_man passar
            (p->playerX) = (p->playerX) - 1;               //Atribuindo a nova posição à nosso personagem
            M[(p->playerY)][(p->playerX)] = '>'; 
        }
    }
    return acao;
}

unsigned long int randMove(void){
    switch(rand()%4){
        case 0:
            return 23361;
        case 1:
            return 23362;
        case 2: 
            return 23363;
        case 3:
            return 23364;
    }
}

void movimentoGhost(char **M, ghost *g, int acao, configMapa config, char *aux){
    if(acao == 23361){ //pra cima
        if((g->ghostY)-1 < 0){     
            M[(g->ghostY)][(g->ghostX)] = *aux; 
            g->ghostY = config.mapRow-1;
            *aux = M[(g->ghostY)][(g->ghostX)];
            M[(g->ghostY)][(g->ghostX)] = 'G'; 
        }
        else if(M[(g->ghostY)-1][(g->ghostX)] == 'H' || M[(g->ghostY)-1][(g->ghostX)] == 'G'){}
        else{
            M[(g->ghostY)][(g->ghostX)] = *aux;           
            (g->ghostY) = (g->ghostY) - 1;               
            *aux = M[(g->ghostY)][(g->ghostX)]; 
            M[(g->ghostY)][(g->ghostX)] = 'G'; 
        }
    }
    else if(acao == 23362){ //pra baixo
        if((g->ghostY)+1 >= config.mapRow){     
            M[(g->ghostY)][(g->ghostX)] = *aux; 
            g->ghostY = 0;
            *aux = M[(g->ghostY)][(g->ghostX)]; 
            M[(g->ghostY)][(g->ghostX)] = 'G'; 
        }
        else if(M[(g->ghostY)+1][(g->ghostX)] == 'H' || M[(g->ghostY)+1][(g->ghostX)] == 'G'){}
        else{
            M[(g->ghostY)][(g->ghostX)] = *aux;
            (g->ghostY) = (g->ghostY) + 1;
            *aux = M[(g->ghostY)][(g->ghostX)]; 
            M[(g->ghostY)][(g->ghostX)] = 'G'; 
        }
    }
    else if(acao == 23363){ //pra direita
        if((g->ghostX)+1 >= config.mapCol){     
            M[(g->ghostY)][(g->ghostX)] = *aux; 
            g->ghostX = 0;
            *aux = M[(g->ghostY)][(g->ghostX)]; 
            M[(g->ghostY)][(g->ghostX)] = 'G'; 
        }
        else if(M[(g->ghostY)][(g->ghostX)+1] == 'H' || M[(g->ghostY)][(g->ghostX)+1] == 'G'){}
        else{
            M[(g->ghostY)][(g->ghostX)] = *aux;
            (g->ghostX) = (g->ghostX) +1;
            *aux = M[(g->ghostY)][(g->ghostX)]; 
            M[(g->ghostY)][(g->ghostX)] = 'G'; 
        }
    }
    else if(acao == 23364){ //pra esquerda
        if((g->ghostX)-1 < 0){     
            M[(g->ghostY)][(g->ghostX)] = *aux; 
            g->ghostX = config.mapCol-1;
            *aux = M[(g->ghostY)][(g->ghostX)]; 
            M[(g->ghostY)][(g->ghostX)] = 'G'; 
        }
        else if(M[(g->ghostY)][(g->ghostX)-1] == 'H' || M[(g->ghostY)][(g->ghostX)-1] == 'G'){}
        else{
            M[(g->ghostY)][(g->ghostX)] = *aux;
            (g->ghostX) = (g->ghostX) - 1;
            *aux = M[(g->ghostY)][(g->ghostX)]; 
            M[(g->ghostY)][(g->ghostX)] = 'G'; 
        }
    }
}

void printMatrix(char **M, int row, int col){
    for (int i = 0; i < row; i++){
        for (int j = 0; j < col; j++){
            if(M[i][j] == 'v' || M[i][j] == '>' || M[i][j] == '<' || M[i][j] == '^')
                printf(FG_YELLOW BG_DEFAULT"%c", M[i][j]);
            else if(M[i][j] == '.')
                printf(FG_WHITE BG_DEFAULT"%c", M[i][j]);
            else if(M[i][j] == '*')
                printf(FG_BLUE BG_DEFAULT"%c", M[i][j]);
            else if(M[i][j] == 'G')
                printf(FG_RED BG_DEFAULT"%c", M[i][j]);
            else if(M[i][j] == 'H')
                printf(BG_GREEN " ", M[i][j]);
            else{
                printf(FG_DEFAULT BG_DEFAULT " ");
            }
            printf(" ");
        }
        printf("\n");
    }
}
void menuPrincipal(void){
    int ncols, nrows, key, c= ' ', count=0, selected = 0;
    eval( BG_DEFAULT FG_DEFAULT CURSOR_INVISIBLE );
    //clear();
    while(1){
        eval( BG_DEFAULT FG_DEFAULT CURSOR_INVISIBLE );
        clear();
        nrows = get_terminal_nrows();
        ncols = get_terminal_ncols();
        draw_window_border(1, 1, ncols/2, nrows, "");
        gotoxy(2, 10);
        printf(" _____        _____ __  __          _   _  ____  \n");
        gotoxy(2+1, 10);
        printf("|  __ \\ /\\   / ____|  \\/  |   /\\   | \\ | |/ __ \\ \n");
        gotoxy(2+2, 10);
        printf("| |__) /  \\ | |    | \\  / |  /  \\  |  \\| | |  | |\n");
        gotoxy(2+3, 10);
        printf("|  ___/ /\\ \\| |    | |\\/| | / /\\ \\ | . ` | |  | |\n");
        gotoxy(2+4, 10);
        printf("| |  / ____ \\ |____| |  | |/ ____ \\| |\\  | |__| |\n");
        gotoxy(2+5, 10);
        printf("|_| /_/    \\_\\_____|_|  |_/_/    \\_\\_| \\_|\\____/ \n");

        if(selected%3 == 0){
            gotoxy(nrows/2, 2);
            printf(FG_RED "Jogar\n");
            gotoxy(nrows/2+1, 2);
            printf(FG_GREEN "Selecionar Mapa\n");
            gotoxy(nrows/2+2, 2);
            printf(FG_GREEN "Sair");

        }
        if(selected%3 == 1 || selected%3 == -2){
            gotoxy(nrows/2, 2);
            printf(FG_GREEN "Jogar\n");
            gotoxy(nrows/2+1, 2);
            printf(FG_RED "Selecionar Mapa\n");
            gotoxy(nrows/2+2, 2);
            printf(FG_GREEN "Sair");

        }
        if(selected%3 == 2 || selected%3 == -1){
            gotoxy(nrows/2, 2);
            printf(FG_GREEN "Jogar\n");
            gotoxy(nrows/2+1, 2);
            printf(FG_GREEN "Selecionar Mapa\n");
            gotoxy(nrows/2+2, 2);
            printf(FG_RED "Sair");

        }

        fflush(stdout);
		
        key = getch();

        if(key == 'q' || key == '\n') break;
        if( key == 23361 ) { // UP
			selected--;
		} else if( key == 23362 ) {	// DOWN
			selected++;
		}


    }
    if(key == '\n'){
        switch(selected%3){
            case 0:
                genMap("default");
                break;
            case 1:
            case -2:
                menuMapas();
                break;
            case 2:
            case -1:
                break;
        }
    }
    eval( ATTR_RESET_ALL CURSOR_VISIBLE );
    gotoxy(nrows,1);
	eval("\n");
}

void menuMapas(void){
    int ncols, nrows, key, c= ' ', count=0, selected = 0;
    eval( BG_DEFAULT FG_DEFAULT CURSOR_INVISIBLE );
    clear();
    while(1){
        eval( BG_DEFAULT FG_DEFAULT CURSOR_INVISIBLE );
        clear();
        nrows = get_terminal_nrows();
        ncols = get_terminal_ncols();
        draw_window_border(1, 1, ncols/2, nrows, "");
        if(selected%3 == 0){
            gotoxy(nrows/2, 2);
            printf(FG_RED "INF\n");
            gotoxy(nrows/2+1, 2);
            printf(FG_GREEN "PAMONHARIA\n");
            gotoxy(nrows/2+2, 2);
            printf(FG_GREEN "BIBLIOTECA");

        }
        if(selected%3 == 1 || selected%3 == -2){
            gotoxy(nrows/2, 2);
            printf(FG_GREEN "INF\n");
            gotoxy(nrows/2+1, 2);
            printf(FG_RED "PAMONHARIA\n");
            gotoxy(nrows/2+2, 2);
            printf(FG_GREEN "BIBLIOTECA");

        }
        if(selected%3 == 2 || selected%3 == -1){
            gotoxy(nrows/2, 2);
            printf(FG_GREEN "INF\n");
            gotoxy(nrows/2+1, 2);
            printf(FG_GREEN "PAMONHARIA\n");
            gotoxy(nrows/2+2, 2);
            printf(FG_RED "BIBLIOTECA");

        }

        fflush(stdout);
		
        key = getch();

        if(key == 27) menuPrincipal();
        if(key == 'q' || key == '\n') break;
        if( key == 23361 ) { // UP
			selected--;
		} else if( key == 23362 ) {	// DOWN
			selected++;
		}


    }
    if(key == '\n'){
        switch(selected%3){
            case 0:
                genMap("default");
                break;
            case 1:
            case -2:
                genMap("pamonharia");
                break;
            case 2:
            case -1:
                genMap("biblioteca");
                break;
        }
    }
    eval( ATTR_RESET_ALL CURSOR_VISIBLE );
    gotoxy(nrows,1);
	eval("\n");
}
void ranking(int p){
    int j,k,i;
    FILE * rankingtest;
    rankingtest = fopen("ranking", "w");
    int *ranking;
    ranking = (int*) calloc(10,sizeof(int));
    if(p.pontos>ranking[9]){
        ranking[9]=p.pontos;
        for (k = 0; k < 10; k++) {
            for (j = 0; j < 10 - 1; j++) {
                if (ranking[j] > ranking[j + 1]) {
                    aux          = ranking[j];
                    ranking[j]     = ranking[j + 1];
                    ranking[j + 1] = aux;
                }
            }
        }
    }
    for(i=0;i<10;i++){
        fprintf(rankingtest, "%d\n",ranking[i]);
    }
    fclose(rankingtest);
}

void interfacegameover(int config,int p){
    int pressBB;
    clear();
    gotoxy(config.mapCol/2 - 5, config.mapRow/2);
    printf(FG_RED "GAME  OVER\n");
    gotoxy(config.mapCol/2 - 5, config.mapRow/2 + 1);
    printf(FG_YELLOW "SCORE: %d\n",p.pontos);
    pressBB = getch();
    if(pressBB == '\n' || pressBB == 'q'){
        menuPrincipal();
    }
}