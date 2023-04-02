/*  gcc -c mapa.c -o mapa.o
    gcc -c ui.c -o ui.o
    g++ main.cpp mapa.o ui.o -lglut -lGL -lGLU -o pacman.out
    g++ main.cpp -lglut -lGL -lGLU -o pacman.out
    g++ main.cpp -lglfw -lglut -lGL -lGLU -o pacman.out
    ./pacman.out
*/

#include <GL/glut.h>
#include <GL/glu.h>
#include <GLFW/glfw3.h>
#include <math.h>
#include "pacman.h"


// Declarando Variaveis Globais
// MAPA mp;
POSICAO pacman; // posição atual do pacman
int havePowerPill = 0; // qtd de pilulas de poder
char ultima_tecla_precionada;
char tecla_precionada = 'd';

// MAIN
int main(int argc, char** argv){
    glutInit(&argc, argv); // Inicializa a biblioteca FreeGLUT
    GLFWwindow* window;
    // Initialize GLFW
    if (!glfwInit()) {
        return -1;
    }

    pacman.x = 0.0;
    pacman.y = 0.0;
    pacman.angle = 0.0;
    pacman.scale = 1.0;

    // Create a windowed mode window and its OpenGL context
    window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Maze Game", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);

    // Set the projection matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, SCREEN_WIDTH, 0, SCREEN_HEIGHT);

    // Set the modelview matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();


    // glutInit(&argc, argv);  
    // glutCreateWindow("PacMan");  
    // glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    // glutMainLoop();
    // Main loop
    while (!glfwWindowShouldClose(window)) {
        // Clear the screen
        glClearColor(0.0, 0.0, 0.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);

        // Draw the maze and Pacman
        glPushMatrix();
        desenhaLabirinto();
        desenha_pacman();
        glPopMatrix();

        // Swap buffers and poll events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Terminate GLFW
    glfwTerminate();
    return 0; 

    // return 0;  
}

// FUCTIONS BASIC
void display(){  
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);  // Fundo preto
    glPushMatrix();
    desenhaLabirinto();
    desenha_pacman();
    glPopMatrix();
    glFlush();  
}

void keyboard(unsigned char key, int x, int y){
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
void desenhaLabirinto() {
    glLineWidth(2.0);
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_LINES);

    for (int i = 0; i < MAZE_HEIGHT; i++) {
        for (int j = 0; j < MAZE_WIDTH; j++) {
            int x = j * (SCREEN_WIDTH / MAZE_WIDTH);
            int y = (MAZE_HEIGHT - i - 1) * (SCREEN_HEIGHT / MAZE_HEIGHT);
            int cellWidth = SCREEN_WIDTH / MAZE_WIDTH;
            int cellHeight = SCREEN_HEIGHT / MAZE_HEIGHT;

            if (maze[i][j] == 1) {
                // draw top line
                glVertex2f(x, y + cellHeight);
                glVertex2f(x + cellWidth, y + cellHeight);

                // draw left line
                glVertex2f(x, y);
                glVertex2f(x, y + cellHeight);

                // draw bottom line
                glVertex2f(x, y);
                glVertex2f(x + cellWidth, y);

                // draw right line
                glVertex2f(x + cellWidth, y);
                glVertex2f(x + cellWidth, y + cellHeight);
            }
        }
    }

    glEnd();
}