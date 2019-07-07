#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "termip.h"
#include <time.h>

typedef struct{
    int playerCol, playerRow, ghostCol, ghostRow, mapCol, mapRow;
}configMapa;

typedef struct{
    int playerX, playerY;
    int pontos;
}player;

typedef struct{
    int ghostX, ghostY;
    int behaviour;
    int mov;
}ghost;

void genMap(char c[128]);
char **allocMatrix(int row, int col);
void freeMatrix(char **matrix, int size);
void movimentopacman(char **M, int x, int y, configMapa config);
void printMatrix(char **M, int row, int col);
void menuPrincipal(void);
void menuMapas(void);
unsigned long int randMove(void);


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

    //movimentopacman(map, config.playerCol, config.playerRow, config);
    printf("%u", randMove());
    
    freeMatrix(map, config.mapRow);
    fclose(mapaSelecionado);
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
void movimentopacman(char **M, int x, int y, configMapa config){
    player p;
    p.playerX = x;
    p.playerY = y;
    int botao,auxmov;
    auxmov=23364;
    while(1){
        clear();
        gotoxy(1,1);
        printMatrix(M, config.mapCol, config.mapRow);
        botao = getch_timeout(0,300000);
        if(botao==-1){
            botao=auxmov;
        }
        if(botao == 23361){ //pra cima
            auxmov=botao;
            if((p.playerY)-1 < 0){     
                M[(p.playerY)][(p.playerX)] = ' '; 
                p.playerY = config.mapRow-1;
                M[(p.playerY)][(p.playerX)] = 'v'; 
            }
            if(M[(p.playerY)-1][(p.playerX)] == 'H'){     //Verificando se a posição a cima do Pac-Man é uma parede
            /*Nao altera mapa*/                      //Caso seja, não Efetue nenhuma ação
            }else{
                if(M[(p.playerY)-1][(p.playerX)] == '.'){
                    p.pontos=p.pontos+10;
                }
                if(M[(p.playerY)-1][(p.playerX)] == '*'){
                    p.pontos=p.pontos+50; 
                }
                if(M[(p.playerY)-1][(p.playerX)] == 'F'){
                    p.pontos=p.pontos+100; 
                }
                M[(p.playerY)][(p.playerX)] = ' ';           //Deixando vazio por onde Pac_man passar
                (p.playerY) = (p.playerY) - 1;               //Atribuindo a nova posição à nosso personagem
                M[(p.playerY)][(p.playerX)] = 'v'; 
            }
        }
        if(botao == 23362){ //pra baixo
            auxmov=botao;
            if((p.playerY)+1 >= config.mapRow){     
                M[(p.playerY)][(p.playerX)] = ' '; 
                p.playerY = 0;
                M[(p.playerY)][(p.playerX)] = '^'; 
            }
            if(M[(p.playerY)+1][(p.playerX)] == 'H')     //Verificando se a posição a baixo do Pac-Man é uma parede
            {
            /*Nao altera mapa*/                      //Caso seja, não Efetue nenhuma ação
            }
        else{
            if(M[(p.playerY)+1][(p.playerX)] == '.'){
                p.pontos=p.pontos+10;
            }
            if(M[(p.playerY)+1][(p.playerX)] == '*'){
                p.pontos=p.pontos+50; 
            }
            if(M[(p.playerY)+1][(p.playerX)] == 'F'){
                p.pontos=p.pontos+100; 
            }
            M[(p.playerY)][(p.playerX)] = ' ';           //Deixando vazio por onde Pac_man passar
            (p.playerY) = (p.playerY) + 1;               //Atribuindo a nova posição à nosso personagem
            M[(p.playerY)][(p.playerX)] = '^'; 
        }
        }
        if(botao == 23363){ //pra direita
            auxmov=botao;
            if((p.playerX)+1 >= config.mapCol){     
                M[(p.playerY)][(p.playerX)] = ' '; 
                p.playerX = 0;
                M[(p.playerY)][(p.playerX)] = '<'; 
            }
            if(M[(p.playerY)][(p.playerX)+1] == 'H')     //Verificando se a posição a direita do Pac-Man é uma parede
                {
                /*Nao altera mapa*/                      //Caso seja, não Efetue nenhuma ação
                }
            else{
                if(M[(p.playerY)][(p.playerX)+1] == '.'){
                    p.pontos=p.pontos+10;
                }
                if(M[(p.playerY)][(p.playerX)+1] == '*'){
                    p.pontos=p.pontos+50; 
                }
                if(M[(p.playerY)][(p.playerX)+1] == 'F'){
                    p.pontos=p.pontos+100; 
                }
                M[(p.playerY)][(p.playerX)] = ' ';           //Deixando vazio por onde Pac_man passar
                (p.playerX) = (p.playerX) +1;               //Atribuindo a nova posição à nosso personagem
                M[(p.playerY)][(p.playerX)] = '<'; 
            }
        }
        if(botao == 23364){ //pra esquerda
            auxmov=botao;
            if((p.playerX)-1 < 0){     
                M[(p.playerY)][(p.playerX)] = ' '; 
                p.playerX = config.mapCol-1;
                M[(p.playerY)][(p.playerX)] = '>'; 
            }
            if(M[(p.playerY)][(p.playerX)-1] == 'H')     //Verificando se a posição a esquerda do Pac-Man é uma parede
            {
            /*Nao altera mapa*/                      //Caso seja, não Efetue nenhuma ação
            }
            else{
                if(M[(p.playerY)][(p.playerX)-1] == '.'){
                    p.pontos=p.pontos+10;
                }
                if(M[(p.playerY)][(p.playerX)-1] == '*'){
                    p.pontos=p.pontos+50; 
                }
                if(M[(p.playerY)][(p.playerX)-1] == 'F'){
                    p.pontos=p.pontos+100; 
                }
                M[(p.playerY)][(p.playerX)] = ' ';           //Deixando vazio por onde Pac_man passar
                (p.playerX) = (p.playerX) - 1;               //Atribuindo a nova posição à nosso personagem
                M[(p.playerY)][(p.playerX)] = '>'; 
            }
        }
    }

}

unsigned long int randMove(void){
    time_t t;
    srand((unsigned) time(&t));
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

void movimentoGhost(char **M, int x, int y, configMapa config){
    ghost stuart, gasparzinho, zezinho, chico;
    stuart.ghostX = x;
    stuart.ghostY = y;
    gasparzinho.ghostX = x;
    gasparzinho.ghostY = y;
    zezinho.ghostX = x;
    zezinho.ghostY = y;
    chico.ghostX = x;
    chico.ghostY = y;

    printf("%u", randMove());
    while(1){
        clear();
        gotoxy(1,1);
        printMatrix(M, config.mapCol, config.mapRow);        
        if(botao == 23361){ //pra cima
            auxmov=botao;
            if((p.playerY)-1 < 0){     
                M[(p.playerY)][(p.playerX)] = ' '; 
                p.playerY = config.mapRow-1;
                M[(p.playerY)][(p.playerX)] = 'v'; 
            }
            if(M[(p.playerY)-1][(p.playerX)] == 'H'){     //Verificando se a posição a cima do Pac-Man é uma parede
            /*Nao altera mapa*/                      //Caso seja, não Efetue nenhuma ação
            }else{
                if(M[(p.playerY)-1][(p.playerX)] == '.'){
                    p.pontos=p.pontos+10;
                }
                if(M[(p.playerY)-1][(p.playerX)] == '*'){
                    p.pontos=p.pontos+50; 
                }
                if(M[(p.playerY)-1][(p.playerX)] == 'F'){
                    p.pontos=p.pontos+100; 
                }
                M[(p.playerY)][(p.playerX)] = ' ';           //Deixando vazio por onde Pac_man passar
                (p.playerY) = (p.playerY) - 1;               //Atribuindo a nova posição à nosso personagem
                M[(p.playerY)][(p.playerX)] = 'v'; 
            }
        }
        if(botao == 23362){ //pra baixo
            auxmov=botao;
            if((p.playerY)+1 >= config.mapRow){     
                M[(p.playerY)][(p.playerX)] = ' '; 
                p.playerY = 0;
                M[(p.playerY)][(p.playerX)] = '^'; 
            }
            if(M[(p.playerY)+1][(p.playerX)] == 'H')     //Verificando se a posição a baixo do Pac-Man é uma parede
            {
            /*Nao altera mapa*/                      //Caso seja, não Efetue nenhuma ação
            }
        else{
            if(M[(p.playerY)+1][(p.playerX)] == '.'){
                p.pontos=p.pontos+10;
            }
            if(M[(p.playerY)+1][(p.playerX)] == '*'){
                p.pontos=p.pontos+50; 
            }
            if(M[(p.playerY)+1][(p.playerX)] == 'F'){
                p.pontos=p.pontos+100; 
            }
            M[(p.playerY)][(p.playerX)] = ' ';           //Deixando vazio por onde Pac_man passar
            (p.playerY) = (p.playerY) + 1;               //Atribuindo a nova posição à nosso personagem
            M[(p.playerY)][(p.playerX)] = '^'; 
        }
        }
        if(botao == 23363){ //pra direita
            auxmov=botao;
            if((p.playerX)+1 >= config.mapCol){     
                M[(p.playerY)][(p.playerX)] = ' '; 
                p.playerX = 0;
                M[(p.playerY)][(p.playerX)] = '<'; 
            }
            if(M[(p.playerY)][(p.playerX)+1] == 'H')     //Verificando se a posição a direita do Pac-Man é uma parede
                {
                /*Nao altera mapa*/                      //Caso seja, não Efetue nenhuma ação
                }
            else{
                if(M[(p.playerY)][(p.playerX)+1] == '.'){
                    p.pontos=p.pontos+10;
                }
                if(M[(p.playerY)][(p.playerX)+1] == '*'){
                    p.pontos=p.pontos+50; 
                }
                if(M[(p.playerY)][(p.playerX)+1] == 'F'){
                    p.pontos=p.pontos+100; 
                }
                M[(p.playerY)][(p.playerX)] = ' ';           //Deixando vazio por onde Pac_man passar
                (p.playerX) = (p.playerX) +1;               //Atribuindo a nova posição à nosso personagem
                M[(p.playerY)][(p.playerX)] = '<'; 
            }
        }
        if(botao == 23364){ //pra esquerda
            auxmov=botao;
            if((p.playerX)-1 < 0){     
                M[(p.playerY)][(p.playerX)] = ' '; 
                p.playerX = config.mapCol-1;
                M[(p.playerY)][(p.playerX)] = '>'; 
            }
            if(M[(p.playerY)][(p.playerX)-1] == 'H')     //Verificando se a posição a esquerda do Pac-Man é uma parede
            {
            /*Nao altera mapa*/                      //Caso seja, não Efetue nenhuma ação
            }
            else{
                if(M[(p.playerY)][(p.playerX)-1] == '.'){
                    p.pontos=p.pontos+10;
                }
                if(M[(p.playerY)][(p.playerX)-1] == '*'){
                    p.pontos=p.pontos+50; 
                }
                if(M[(p.playerY)][(p.playerX)-1] == 'F'){
                    p.pontos=p.pontos+100; 
                }
                M[(p.playerY)][(p.playerX)] = ' ';           //Deixando vazio por onde Pac_man passar
                (p.playerX) = (p.playerX) - 1;               //Atribuindo a nova posição à nosso personagem
                M[(p.playerY)][(p.playerX)] = '>'; 
            }
        }
    }

}

void printMatrix(char **M, int row, int col){
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            printf("%c", M[i][j]);
        }
        printf("\n");
    }
}
void menuPrincipal(void){
    int ncols, nrows, key, c= ' ', count=0, selected = 0;
    eval( BG_DEFAULT FG_DEFAULT CURSOR_INVISIBLE );
    clear();
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