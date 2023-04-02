#ifndef _PACMAN_H_
#define _PACMAN_H_

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


void display();
void keyboard(unsigned char key, int x, int y);

void desenha_pacman();

#endif