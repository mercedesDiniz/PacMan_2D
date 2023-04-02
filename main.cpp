// g++ -o proj01.out proj01_2D.cpp -lglut -lGLU -lGL -lm
/*  gcc -c mapa.c -o mapa.o
    gcc -c ui.c -o ui.o
    g++ main.cpp mapa.o ui.o -lglut -lGL -lGLU -o pacman.out
    ./pacman.out
*/

#include <GL/glut.h>
#include <math.h>
#include "pacman.h"


// Declarando Variaveis Globais
// MAPA mp;
POSICAO pacman; // posição atual do pacman
int havePowerPill = 0; // qtd de pilulas de poder
char ultima_tecla_precionada;
char tecla_precionada = 'd';

// MAIN
int main(int argc, char** argv)  
{  
    pacman.x = 0.0;
    pacman.y = 0.0;
    pacman.angle = 0.0;
    pacman.scale = 1.0;

    glutInit(&argc, argv);  
    glutCreateWindow("PacMan");  
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMainLoop();  

    return 0;  
}

// FUCTIONS BASIC
void display()  
{  
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);  // Fundo preto
    glPushMatrix();

    desenha_pacman();

    glPopMatrix();
    glFlush();  
}  


void keyboard(unsigned char key, int x, int y)
{
    switch (key) {
        case ESQUERDA:
            tecla_precionada = ESQUERDA;
            pacman.x -= 0.1;
            if(ultima_tecla_precionada != tecla_precionada){
                pacman.angle = 0.0;
                pacman.angle -= 180.0;
            }
            break;
        case CIMA:
            tecla_precionada = CIMA;
            pacman.y += 0.1;
            if(ultima_tecla_precionada != tecla_precionada){
                pacman.angle = 0.0;
                pacman.angle += 90.0;
            }
            break;
        case BAIXO:
            tecla_precionada = BAIXO;
            pacman.y -= 0.1;
            if(ultima_tecla_precionada != tecla_precionada){
                pacman.angle = 0.0;
                pacman.angle -= 90.0;
            }
            break;
        case DIREITA:
            tecla_precionada = DIREITA;
            pacman.x += 0.1;
            if(ultima_tecla_precionada != tecla_precionada){
                pacman.angle = 0.0;
                pacman.angle += 360.0;
            }
            break;
        // case 'e':
        //     tecla_precionada = 'e';
        //     pacman.scale += 0.1;
        //     break;
        // case 'q':
        //     tecla_precionada = 'q';
        //     pacman.scale -= 0.1;
        //     break;
    }
    ultima_tecla_precionada = tecla_precionada;
    glutPostRedisplay();
}

// FUCTIONS 
void desenha_pacman(){
    // Desenha o avatar do Pacman
    glTranslatef(pacman.x, pacman.y, 0.0);
    glRotatef(pacman.angle, 0.0, 0.0, 1.0);
    glScalef(pacman.scale, pacman.scale, 1.0);

    // Desenha o corpo do Pacman
    glColor3f(1.0, 1.0, 0.0);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(0.0, 0.0);
    for (int i = 0; i <= 360; i += 5) {
        float rad = i * 3.14159 / 180.0;
        glVertex2f(cos(rad) * 0.1, sin(rad) * 0.1);
    }
    glEnd();

    // Desenha a boca do Pacman
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_TRIANGLES);
    glVertex2f(0.0, 0.0);
    glVertex2f(0.1, 0.05);
    glVertex2f(0.1, -0.05);
    glEnd();
}

// void imprime_mapa(MAPA* mp, POSICAO pacman){
// 	// Exibindo o mapa
// 	for(int i = 0; i<mp->linhas; i++){
//         for(int j=0; j < mp->colunas; j++){
//             float x = j * TAMANHO_CELULA;
//             float y = (ALTURA - i - 1) * TAMANHO_CELULA;
//             switch(mp->matriz[i][j]){
//                 case VAZIO:
//                 // Desenha um quadrado vazio
//                 glColor3f(1.0, 1.0, 1.0);
//                 glBegin(GL_LINE_LOOP);
//                 glVertex2f(x, y);
//                 glVertex2f(x + TAMANHO_CELULA, y);
//                 glVertex2f(x + TAMANHO_CELULA, y + TAMANHO_CELULA);
//                 glVertex2f(x, y + TAMANHO_CELULA);
//                 glEnd();
//                 break;

//                 case PAREDE_HORIZONTAL:
//                     // Desenha uma linha horizontal
//                     glColor3f(1.0, 1.0, 1.0);
//                     glBegin(GL_LINES);
//                     glVertex2f(x, y + TAMANHO_CELULA / 2);
//                     glVertex2f(x + TAMANHO_CELULA, y + TAMANHO_CELULA / 2);
//                     glEnd();
//                     break;

//                 case PAREDE_VERTICAL:
//                     // Desenha uma linha vertical
//                     glColor3f(1.0, 1.0, 1.0);
//                     glBegin(GL_LINES);
//                     glVertex2f(x + TAMANHO_CELULA / 2, y);
//                     glVertex2f(x + TAMANHO_CELULA / 2, y + TAMANHO_CELULA);
//                     glEnd();
//                     break;

//                 case PACMAN:
//                     // Desenha o avatar do Pacman
//                     glPushMatrix();
//                     glTranslatef(x + TAMANHO_CELULA / 2, y + TAMANHO_CELULA / 2, 0.0);
//                     glRotatef(pacman.angle, 0.0, 0.0, 1.0);
//                     glScalef(pacman.scale, pacman.scale, 1.0);

//                     // Desenha o corpo do Pacman
//                     glColor3f(1.0, 1.0, 0.0);
//                     glBegin(GL_TRIANGLE_FAN);
//                     glVertex2f(0.0, 0.0);
//                     for (int k = 0; k <= 360; k += 5) {
//                         float rad = k * 3.14159 / 180.0;
//                         glVertex2f(cos(rad) * TAMANHO_CELULA / 2, sin(rad) * TAMANHO_CELULA / 2);
//                     }
//                     glEnd();
//                     break;
//             }
//         }       
// 	}
// }