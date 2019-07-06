#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "termip.h"

typedef struct{
    int playerCol, playerRow, ghostCol, ghostRow, mapCol, mapRow;
    char **mapa;
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
        if(botao == 23361){ //pra esquerda
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