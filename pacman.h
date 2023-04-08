#ifndef _PACMAN_H_
#define _PACMAN_H_

#include <GL/gl.h>

#define PASSO 5.5
#define RAIO_PACMAN 1 

struct posicao{
	float x;
	float y;
	float angle;
	float scale;
};
typedef struct posicao POSICAO;

const int num_fantasmas = 7;

struct coordenada{
	int x;
	int y;
};
typedef struct coordenada FANTASMAS;

#define CIMA GLFW_KEY_W          // 'w'
#define BAIXO GLFW_KEY_S         // 's'
#define DIREITA GLFW_KEY_D       // 'd'
#define ESQUERDA GLFW_KEY_A      // 'a'
#define EXPLODE GLFW_KEY_BACKSPACE // 'b'

#define VAZIO 0
#define PAREDE 1
#define FOOD_PILL 2
#define POWER_PILL 3
#define FANTASMA 4


#define TILE_SIZE 20

const int SCREEN_WIDTH = 800;  // 800 1800;
const int SCREEN_HEIGHT = 800; // 600 1000

const int MAZE_WIDTH = 20; //10;
const int MAZE_HEIGHT = 20; //10;

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

// PROTOTYPE OF FUNCTIONS

void keyboard(GLFWwindow* window, int key, int scancode, int action, int mods);

void desenhaPacman();
void desenhaLabirinto();
void desenhaFoodPill();
void desenhaPowerPill();
void desenhaFantasma();

// void desenhaGameOver();

bool eh_parede(POSICAO p);
bool eh_parede_xy(int x, int y);
bool eh_FoodPill(POSICAO p);
bool eh_PowerPill(POSICAO p);
bool eh_fantasma(POSICAO p);

void morreu();
void rotinaFantasma();
void moveFantasmas(int direcao);
#endif