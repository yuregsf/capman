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
}playercordenadas;

void genMap();
char **allocMatrix(int row, int col);
void freeMatrix(char **matrix, int size);
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

    //Posição do jogador
    map[config.playerRow][config.playerCol] = 'P';
    //Spawn dos fantasmas
    map[config.ghostRow][config.ghostCol] = 'G';
        
    while(1){
        eval( BG_DEFAULT FG_DEFAULT CURSOR_INVISIBLE );
        clear();
        for (int i = 0; i < config.mapRow; i++){
            gotoxy(i+1, 1);
            for (int j = 0; j < config.mapCol; j++){
                printf("%c", map[i][j]);
            }
            printf("\n");
        }
        fflush(stdout);
        key = getch();

    }
    
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