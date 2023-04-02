/*  gcc -c mapa.c -o mapa.o
    gcc -c ui.c -o ui.o
    g++ main.cpp mapa.o ui.o -lglut -lGL -lGLU -o pacman.out
    g++ main.cpp -lglut -lGL -lGLU -o pacman.out
    g++ main.cpp -lglfw -lglut -lGL -lGLU -o pacman.out
    ./pacman.out
*/

// #include <cstdlib>
// #include <GL/glu.h>
#include <stdio.h>
#include <GL/glut.h>
#include <GLFW/glfw3.h>
#include <math.h>
#include "pacman.h"

// Declarando Variaveis Globais
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
    glutInitDisplayMode(GLUT_DOUBLE);
    glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);

    pacman.x = SCREEN_WIDTH/2.0;
    pacman.y = SCREEN_HEIGHT/2.0;
    pacman.angle = 0.0;
    pacman.scale = 1.0;

    // Create a windowed mode window and its OpenGL context
    window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "PacMan", NULL, NULL);
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

    glfwSetKeyCallback(window, keyboard);

    // Main loop
    while (!glfwWindowShouldClose(window)) {
        printf("Main loop\n");
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
}

// FUCTIONS:

// void keyboard(unsigned char key, int x, int y){
void keyboard(GLFWwindow* window, int key, int scancode, int action, int mods){
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) glfwSetWindowShouldClose(window, GLFW_TRUE);

    POSICAO nova_posicao;
    switch (key) {
        case ESQUERDA:
            tecla_precionada = ESQUERDA;
            // Verifica se a nova posição do Pac-Man é uma parede
            nova_posicao = { static_cast<float>(pacman.x - 0.1), static_cast<float>(pacman.y) };
            if (colisao_parede(nova_posicao)) return;

            pacman.x -= 0.1;
            if(ultima_tecla_precionada != tecla_precionada){
                pacman.angle = 0.0;
                pacman.angle -= 180.0;
            }
            break;

        case CIMA:
            tecla_precionada = CIMA;
            // Verifica se a nova posição do Pac-Man é uma parede
            nova_posicao = { static_cast<float>(pacman.x), static_cast<float>(pacman.y + 0.1) };
            if (colisao_parede(nova_posicao)) return;

            pacman.y += 0.1;
            if(ultima_tecla_precionada != tecla_precionada){
                pacman.angle = 0.0;
                pacman.angle += 90.0;
            }
            break;

        case BAIXO:
            tecla_precionada = BAIXO;
            // Verifica se a nova posição do Pac-Man é uma parede
            nova_posicao = { static_cast<float>(pacman.x), static_cast<float>(pacman.y - 0.1) };
            if (colisao_parede(nova_posicao)) return;

            pacman.y -= 0.1;
            if(ultima_tecla_precionada != tecla_precionada){
                pacman.angle = 0.0;
                pacman.angle -= 90.0;
            }
            break;

        case DIREITA:
            tecla_precionada = DIREITA;
            // Verifica se a nova posição do Pac-Man é uma parede
            nova_posicao = { static_cast<float>(pacman.x + 0.1), static_cast<float>(pacman.y) };
            if (colisao_parede(nova_posicao)) return;

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

    // atualiza a tela
    glfwSwapBuffers(window);
}


void desenha_pacman(){
    printf("desenha_pacma()\n");
    // Desenha o avatar do Pacman
    glTranslatef(pacman.x, pacman.y, 0.0);
    glRotatef(pacman.angle, 0.0, 0.0, 1.0);
    glScalef(pacman.scale, pacman.scale, 1.0);

    // Desenha o corpo do Pacman
    glColor3f(1.0, 1.0, 0.0); // amarelo
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(0.0, 0.0);
    for (int i = 0; i <= 360; i += 5) {
        float rad = i * 3.14159 / 180.0;
        glVertex2f(cos(rad) * 0.1, sin(rad) * 0.1);
    }
    glEnd();

    // Desenha a boca do Pacman
    glColor3f(0.0, 0.0, 0.0); // preto
    glBegin(GL_TRIANGLES);
    glVertex2f(0.0, 0.0);
    glVertex2f(0.1, 0.05);
    glVertex2f(0.1, -0.05);
    glEnd();
}

void desenhaLabirinto() {
    printf("desenhaLabirinto()\n");
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

// Função para verificar se o Pac-Man colidiu com uma parede
bool colisao_parede(POSICAO p) {
    // Converter as coordenadas do Pac-Man para as coordenadas do labirinto
    int x = (int) (p.x / TILE_SIZE);
    int y = (int) (p.y / TILE_SIZE);

    // Verificar se as coordenadas correspondem a uma parede
    if (maze[y][x] == 1) {
        printf("colisao_parede() = TRUE\n");
        return true;
    }
    return false;
}