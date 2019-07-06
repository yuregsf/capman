#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    int playerCol, playerRow, ghostCol, ghostRow, mapCol, mapRow;
    char **mapa;
}configMapa;

void genMap();
char **allocMatrix(int row, int col);
void freeMatrix(char **matrix, int size);

int main(){
    genMap();
    return 0;
}

//Gera mapa baseado nos parâmetros do arquivo .pacmap
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