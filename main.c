#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    int playerCol, playerRow, ghostCol, ghostRow, mapCol, mapRow;
    char **mapa;
}configMapa;

typedef struct{
    int playerX, playerY;
    int pontos;
}playercordenadas;

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
void movimentopacman(){
    int botao;
    botao = getch();
    if(botao == 23361){ //pra cima
        if(M[(playercordenadas.playerY)-1][(playercordenadas.playerX)] == 'H')     //Verificando se a posição a cima do Pac-Man é uma parede
        {
          /*Nao altera mapa*/                      //Caso seja, não Efetue nenhuma ação
        }
      else{
        if(M[(playercordenadas.playerY)-1][(playercordenadas.playerX)] == '.'){
            playercordenadas.pontos=playercordenadas.pontos+10;
        }
        if(M[(playercordenadas.playerY)-1][(playercordenadas.playerX)] == '*'){
            playercordenadas.pontos=playercordenadas.pontos+50; 
        }
        if(M[(playercordenadas.playerY)-1][(playercordenadas.playerX)] == 'F'){
            playercordenadas.pontos=playercordenadas.pontos+100; 
        }
        M[(playercordenadas.playerY)][(playercordenadas.playerX)] = ' ';           //Deixando vazio por onde Pac_man passar
          (playercordenadas.playerY) = (playercordenadas.playerY) - 1;               //Atribuindo a nova posição à nosso personagem
          M[(playercordenadas.playerY)][(playercordenadas.playerX)] = 'v'; 
      }
    }
    if(botao == 23362){ //pra baixo
        if(M[(playercordenadas.playerY)+1][(playercordenadas.playerX)] == 'H')     //Verificando se a posição a baixo do Pac-Man é uma parede
        {
          /*Nao altera mapa*/                      //Caso seja, não Efetue nenhuma ação
        }
      else{
        if(M[(playercordenadas.playerY)+1][(playercordenadas.playerX)] == '.'){
            playercordenadas.pontos=playercordenadas.pontos+10;
        }
        if(M[(playercordenadas.playerY)+1][(playercordenadas.playerX)] == '*'){
            playercordenadas.pontos=playercordenadas.pontos+50; 
        }
        if(M[(playercordenadas.playerY)+1][(playercordenadas.playerX)] == 'F'){
            playercordenadas.pontos=playercordenadas.pontos+100; 
        }
        M[(playercordenadas.playerY)][(playercordenadas.playerX)] = ' ';           //Deixando vazio por onde Pac_man passar
          (playercordenadas.playerY) = (playercordenadas.playerY) + 1;               //Atribuindo a nova posição à nosso personagem
          M[(playercordenadas.playerY)][(playercordenadas.playerX)] = '^'; 
      }
    }
    if(botao == 23363){ //pra direita
        if(M[(playercordenadas.playerY)][(playercordenadas.playerX)+1] == 'H')     //Verificando se a posição a direita do Pac-Man é uma parede
        {
          /*Nao altera mapa*/                      //Caso seja, não Efetue nenhuma ação
        }
      else{
        if(M[(playercordenadas.playerY)][(playercordenadas.playerX)+1] == '.'){
            playercordenadas.pontos=playercordenadas.pontos+10;
        }
        if(M[(playercordenadas.playerY)][(playercordenadas.playerX)+1] == '*'){
            playercordenadas.pontos=playercordenadas.pontos+50; 
        }
        if(M[(playercordenadas.playerY)][(playercordenadas.playerX)+1] == 'F'){
            playercordenadas.pontos=playercordenadas.pontos+100; 
        }
        M[(playercordenadas.playerY)][(playercordenadas.playerX)] = ' ';           //Deixando vazio por onde Pac_man passar
          (playercordenadas.playerX) = (playercordenadas.playerX) +1;               //Atribuindo a nova posição à nosso personagem
          M[(playercordenadas.playerY)][(playercordenadas.playerX)] = '<'; 
      }
    }
    if(botao == 23361){ //pra esquerda
        if(M[(playercordenadas.playerY)][(playercordenadas.playerX)-1] == 'H')     //Verificando se a posição a esquerda do Pac-Man é uma parede
        {
          /*Nao altera mapa*/                      //Caso seja, não Efetue nenhuma ação
        }
      else{
        if(M[(playercordenadas.playerY)][(playercordenadas.playerX)-1] == '.'){
            playercordenadas.pontos=playercordenadas.pontos+10;
        }
        if(M[(playercordenadas.playerY)][(playercordenadas.playerX)-1] == '*'){
            playercordenadas.pontos=playercordenadas.pontos+50; 
        }
        if(M[(playercordenadas.playerY)][(playercordenadas.playerX)-1] == 'F'){
            playercordenadas.pontos=playercordenadas.pontos+100; 
        }
        M[(playercordenadas.playerY)][(playercordenadas.playerX)] = ' ';           //Deixando vazio por onde Pac_man passar
          (playercordenadas.playerX) = (playercordenadas.playerX) - 1;               //Atribuindo a nova posição à nosso personagem
          M[(playercordenadas.playerY)][(playercordenadas.playerX)] = '>'; 
      }
    } 
}