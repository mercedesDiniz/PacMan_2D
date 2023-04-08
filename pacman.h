#ifndef _PACMAN_H_
#define _PACMAN_H_

#include <GL/gl.h>

struct posicao{
	float x;
	float y;
	float angle;
	float scale;
};
typedef struct posicao POSICAO;

#define PASSO 5.5
#define RAIO_PACMAN 1 

#define CIMA GLFW_KEY_W             // 'w'
#define BAIXO GLFW_KEY_S            // 's'
#define DIREITA GLFW_KEY_D          // 'd'
#define ESQUERDA GLFW_KEY_A         // 'a'
#define EXPLODE GLFW_KEY_BACKSPACE  // 'b'

#define VAZIO 0
#define PAREDE 1
#define FOOD_PILL 2
#define POWER_PILL 3
#define FANTASMA 4

#define TILE_SIZE 20

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 800; 

const int MAZE_WIDTH = 20; 
const int MAZE_HEIGHT = 20; 

int maze[MAZE_HEIGHT][MAZE_WIDTH] = {
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,3,2,1,2,2,2,2,2,3,2,2,2,2,2,2,1,2,3,1},
    {1,2,2,1,2,2,2,2,2,4,2,2,2,2,2,2,1,2,2,1},
    {1,2,2,1,1,1,2,2,1,1,1,1,2,2,1,1,1,2,2,1},
    {1,2,2,2,2,0,0,2,2,2,2,2,0,0,0,2,2,2,2,1},
    {1,2,4,2,2,0,0,2,2,2,2,2,0,0,0,2,2,4,2,1},
    {1,2,2,2,2,0,0,2,2,2,2,2,0,0,0,2,2,2,2,1},
    {1,2,2,2,1,0,0,3,1,0,0,1,3,0,0,1,2,2,2,1},
    {1,2,2,1,1,0,0,1,1,0,0,1,1,0,0,1,1,2,2,1},
    {1,2,2,2,2,2,2,2,0,0,0,0,2,2,2,2,2,2,2,1},
    {1,2,4,2,2,2,2,2,0,0,0,0,2,2,2,2,2,4,2,1},
    {1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1},
    {1,0,0,0,1,0,0,3,1,0,0,1,3,0,0,1,0,0,0,1},
    {1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1},
    {1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1},
    {1,0,0,0,0,0,4,0,2,2,2,0,0,4,0,0,0,0,0,1},
    {1,2,2,1,1,1,2,2,1,1,1,1,2,2,1,1,1,2,2,1},
    {1,2,2,2,1,2,2,2,2,2,2,2,2,2,2,1,2,2,2,1},
    {1,2,2,2,1,2,2,2,2,3,2,2,2,2,2,1,2,2,2,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
};

void keyboard(GLFWwindow* window, int key, int scancode, int action, int mods);

void desenhaPacman();
void desenhaLabirinto();
void desenhaFoodPill();
void desenhaPowerPill();
void desenhaFantasma();

bool eh_parede(POSICAO p);
bool eh_FoodPill(POSICAO p);
bool eh_PowerPill(POSICAO p);
bool eh_fantasma(POSICAO p);
void morreu();
#endif