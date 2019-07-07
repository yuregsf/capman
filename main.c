#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "termip.h"

typedef struct{
    int playerCol, playerRow, ghostCol, ghostRow, mapCol, mapRow;
}configMapa;

typedef struct{
    int playerX, playerY;
    int pontos;
}player;

void genMap();
char **allocMatrix(int row, int col);
void freeMatrix(char **matrix, int size);
void movimentopacman(char **M, int x, int y);
void printMatrix(char **M, int row, int col);
void menuPrincipal(void);

int main(){
    //genMap();
    menuPrincipal();
    return 0;
}

//Gera mapa baseado nos parâmetros do arquivo mapa
void genMap(void){
    FILE * mapaSelecionado;
    configMapa config;
    char line[256];
    int key;
    mapaSelecionado = fopen("mapa", "r");
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

    movimentopacman(map, config.playerCol, config.playerRow);
    
    
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
void movimentopacman(char **M, int x, int y){
    player p;
    p.playerX = x;
    p.playerY = y;
    int botao;

    while(1){
        clear();
        gotoxy(1,1);
        printMatrix(M, 6, 23);
        botao = getch();
        if(botao == 23361){ //pra cima
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
                genMap();
                break;
            case 1:
            case -2:
                //menu do mapa
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