#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    int playerX, playerY, ghostX, ghostY, mapX, mapY;
    char **mapa;
}configMapa;

void genMap();
void allocMatrix(char **matrix, int row);
void freeMatrix(char **matrix, int row);

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
            fscanf(mapaSelecionado, "%d", &config.playerX);
            fscanf(mapaSelecionado, "%d", &config.playerY);
        }
        if(strstr(line, "ghostPos") != NULL){
            fscanf(mapaSelecionado, "%d", &config.ghostX);
            fscanf(mapaSelecionado, "%d", &config.ghostY);
        }
        if(strstr(line, "map") != NULL){
            fscanf(mapaSelecionado, "%d", &config.mapX);
            fscanf(mapaSelecionado, "%d", &config.mapY);
            break;
        }
    }
    
    char **map = (char **)malloc(config.mapY*sizeof(char*));
    allocMatrix(map, config.mapX);
    for (int i = 0; i < config.mapY; i++){
        fscanf(mapaSelecionado, "%s", map[i]);
    }
        
    for (int i = 0; i < config.mapX; i++){
        for (int j = 0; j < config.mapY; j++){
            printf("%c", map[i][j]);
        }
        printf("\n");
    }
    
    freeMatrix(map, config.mapY);
    fclose(mapaSelecionado);
}

void allocMatrix(char **matrix, int size){
    for(int i = 0; i < size; i++){
        matrix[i] = (char *)malloc(size*sizeof(char));
    }
}

void freeMatrix(char **matrix, int size){
    for(int i = 0; i < size; i++){
        free(matrix[i]);
    }
    free(matrix);
}