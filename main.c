#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "termip.h"

typedef struct{
    int playerCol, playerRow, ghostCol, ghostRow, mapCol, mapRow;
}configMapa;

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
        
    for (int i = 0; i < config.mapRow; i++){
        for (int j = 0; j < config.mapCol; j++){
            printf("%c", map[i][j]);
        }
        printf("\n");
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
        //eval( BG_DEFAULT FG_DEFAULT CURSOR_INVISIBLE );
        clear();
        nrows = get_terminal_nrows();
        ncols = get_terminal_ncols();
        draw_window_border(1, 1, ncols, nrows, "");
        gotoxy(nrows/2-2, 2);
        printf(" _____        _____ __  __          _   _  ____  \n");
        gotoxy(nrows/2-1, 2);
        printf("|  __ \\ /\\   / ____|  \\/  |   /\\   | \\ | |/ __ \\ \n");
        gotoxy(nrows/2, 2);
        printf("| |__) /  \\ | |    | \\  / |  /  \\  |  \\| | |  | |\n");
        gotoxy(nrows/2+1, 2);
        printf("|  ___/ /\\ \\| |    | |\\/| | / /\\ \\ | . ` | |  | |\n");
        gotoxy(nrows/2+2, 2);
        printf("| |  / ____ \\ |____| |  | |/ ____ \\| |\\  | |__| |\n");
        gotoxy(nrows/2+3, 2);
        printf("|_| /_/    \\_\\_____|_|  |_/_/    \\_\\_| \\_|\\____/ \n");

        gotoxy(n)

        fflush(stdout);
		
		// Espera uma tecla ser pressionada em um intervalo de 200ms
        key = getch();
		if( key != -1 ) c= key;
		count += 2;

        if(key == 'q') break;
        if( key == 23361 ) { // UP
			R--;
		} else if( key == 23362 ) {	// DOWN
			R++;
		}

    }
    eval( ATTR_RESET_ALL CURSOR_VISIBLE );
    gotoxy(nrows,1);
	eval("\n");
}