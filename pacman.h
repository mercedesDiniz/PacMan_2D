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


#define PASSO 5.5


const int SCREEN_WIDTH = 800;  // 800 1800;
const int SCREEN_HEIGHT = 800; // 600 1000

const int MAZE_WIDTH = 20; //10;
const int MAZE_HEIGHT = 20; //10;

#define RAIO_PACMAN 1 
#define TILE_SIZE 20
int maze[MAZE_HEIGHT][MAZE_WIDTH] = {
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,0,0,1,2,2,2,0,0,3,0,0,0,2,2,2,1,0,3,1},
    {1,0,0,1,2,2,0,0,0,4,0,0,0,0,2,2,1,0,0,1},
    {1,0,0,1,1,1,0,0,1,1,1,1,0,0,1,1,1,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,2,0,0,0,0,0,4,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,1,0,0,0,1,0,0,1,0,0,0,1,0,0,0,1},
    {1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1},
    {1,0,0,0,1,0,0,0,1,0,0,1,0,0,0,1,0,0,0,1},
    {1,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,2,0,0,0,0,0,0,0,0,0,0,0,4,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,1,1,1,0,0,1,1,1,1,0,0,1,1,1,0,0,1},
    {1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1},
    {1,0,0,0,1,0,0,0,0,3,0,0,0,0,0,1,0,0,0,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
};

// int maze[MAZE_HEIGHT][MAZE_WIDTH] = {
//     {1,1,1,1,1,1,1,1,1,1},
//     {1,0,1,0,0,0,0,0,0,1},
//     {1,0,1,0,1,1,1,1,0,1},
//     {1,0,1,0,0,0,0,1,0,1},
//     {1,0,1,1,1,1,0,1,0,1},
//     {1,0,0,0,0,1,0,1,0,1},
//     {1,0,1,1,0,1,0,1,0,1},
//     {1,0,0,1,0,1,0,0,0,1},
//     {1,1,0,1,0,0,0,1,1,1},
//     {1,1,1,1,1,1,1,1,1,1},
// };

// void display();
void desenhaPacman();
void desenhaLabirinto();
void desenhaFoodPill();
void desenhaPowerPill();
void desenhaFantasma();
// void keyboard(unsigned char key, int x, int y);
void keyboard(GLFWwindow* window, int key, int scancode, int action, int mods);

// bool eh_parede(POSICAO p);
bool eh_parede(POSICAO p);
bool eh_FoodPill(POSICAO p);
bool eh_PowerPill(POSICAO p);
bool eh_fantasma(POSICAO p);
bool colisao_parede(POSICAO p);
#endif