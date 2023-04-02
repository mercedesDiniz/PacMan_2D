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

#define CIMA 'w'
#define BAIXO 's'
#define DIREITA 'd'
#define ESQUERDA 'a'
#define BOMBA 'b'

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

const int MAZE_WIDTH = 10;
const int MAZE_HEIGHT = 10;


#define TILE_SIZE 20

int maze[MAZE_HEIGHT][MAZE_WIDTH] = {
    {1,1,1,1,1,1,1,1,1,1},
    {1,0,1,0,0,0,0,0,0,1},
    {1,0,1,0,1,1,1,1,0,1},
    {1,0,1,0,0,0,0,1,0,1},
    {1,0,1,1,1,1,0,1,0,1},
    {1,0,0,0,0,1,0,1,0,1},
    {1,0,1,1,0,1,0,1,0,1},
    {1,0,0,1,0,1,0,0,0,1},
    {1,1,0,1,0,0,0,1,1,1},
    {1,1,1,1,1,1,1,1,1,1},
};

// void display();
void desenha_pacman();
void desenhaLabirinto();
// void keyboard(unsigned char key, int x, int y);
void keyboard(GLFWwindow* window, int key, int scancode, int action, int mods);
bool colisao_parede(POSICAO p);
#endif