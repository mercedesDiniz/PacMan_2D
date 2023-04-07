/*  gcc -c mapa.c -o mapa.o
    gcc -c ui.c -o ui.o
    g++ main.cpp mapa.o ui.o -lglut -lGL -lGLU -o pacman.out
    g++ main.cpp -lglut -lGL -lGLU -o pacman.out
    g++ main.cpp -lglfw -lglut -lGL -lGLU -o pacman.out
    ./pacman.out
*/

// #include <cstdlib>
// #include <GL/glu.h>
//#define _USE_MATH_DEFINES           # Para rodar no Visual Studio descomente essa linha
#include <stdio.h>
#include <GL/glut.h>
#include <GLFW/glfw3.h>
#include <math.h>
#include "pacman.h"

// Declarando Variaveis Globais
POSICAO pacman; // posição atual do pacman
POSICAO fantasme01; // posição atual do pacman
POSICAO fantasme02; // posição atual do pacman

int havePowerPill = 0; // qtd de pilulas de poder
char ultima_tecla_precionada;
char tecla_precionada = DIREITA;


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

    pacman.x = SCREEN_WIDTH/8.5; // coordenada da horizontal
    pacman.y = SCREEN_HEIGHT/13; // coordenada da vertical
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
        printf("[LOG] Main loop\n");
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
    printf("[LOG] keyboard()\n");

    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) glfwSetWindowShouldClose(window, GLFW_TRUE);

    POSICAO nova_posicao;
    switch (key) {
        case ESQUERDA:
            tecla_precionada = ESQUERDA;

            // Verifica se a nova posição para onde o Pac-Man quer ir é uma parede
            nova_posicao = { static_cast<float>(pacman.x - PASSO), static_cast<float>(pacman.y)};
            if (!eh_parede(nova_posicao, -1)){
                pacman.x -= PASSO;
                if(ultima_tecla_precionada != tecla_precionada){
                    pacman.angle = 0.0;
                    pacman.angle -= 180.0;
                }
            }
            break;

        case DIREITA:
            tecla_precionada = DIREITA;

            // Verifica se a nova posição para onde o Pac-Man quer ir é uma parede
            nova_posicao = { static_cast<float>(pacman.x + PASSO), static_cast<float>(pacman.y) };
            if (!eh_parede(nova_posicao, 1)){
                pacman.x += PASSO;
                if(ultima_tecla_precionada != tecla_precionada){
                    pacman.angle = 0.0;
                    pacman.angle += 360.0;
                }
            }
            break;

        case CIMA:
            tecla_precionada = CIMA;

            // Verifica se a nova posição para onde o Pac-Man quer ir é uma parede
            nova_posicao = { static_cast<float>(pacman.x), static_cast<float>(pacman.y + PASSO) };
            if (!eh_parede(nova_posicao, 1)){
                pacman.y += PASSO;
                if(ultima_tecla_precionada != tecla_precionada){
                    pacman.angle = 0.0;
                    pacman.angle += 90.0;
                }
            }

            break;

        case BAIXO:
            tecla_precionada = BAIXO;

            // Verifica se a nova posição para onde o Pac-Man quer ir é uma parede
            nova_posicao = { static_cast<float>(pacman.x), static_cast<float>(pacman.y - PASSO) };
            if (!eh_parede(nova_posicao, -1)){
                pacman.y -= PASSO;
                if(ultima_tecla_precionada != tecla_precionada){
                    pacman.angle = 0.0;
                    pacman.angle -= 90.0;
                }
            }

            break;


        // case 'e':
        //     tecla_precionada = 'e';
        //     pacman.scale += PASSO;
        //     break;
        // case 'q':
        //     tecla_precionada = 'q';
        //     pacman.scale -= PASSO;
        //     break;
    }
    ultima_tecla_precionada = tecla_precionada;

    // atualiza a tela
    glfwSwapBuffers(window);
}


void desenha_pacman(){
    printf("[LOG] desenha_pacman()\n");
    // Desenha o avatar do Pacman
    glTranslatef(pacman.x, pacman.y, 0.0);
    glPushMatrix();
    glRotatef(pacman.angle, 0.0, 0.0, 1.0);
    glPopMatrix();
    glFlush();
    glScalef(pacman.scale, pacman.scale, 1.0);

    // Desenha o corpo do Pacman
    glColor3f(1.0, 1.0, 0.0);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(pacman.x, pacman.y);
    for (int i = 0; i <= 360; i++) {
        float x = pacman.x + pacman.scale * TILE_SIZE * cos(i * M_PI / 180.0);
        float y = pacman.y + pacman.scale * TILE_SIZE * sin(i * M_PI / 180.0);
        glVertex2f(x, y);
    }
    glEnd();

    glPushMatrix();
    glTranslatef(pacman.x, pacman.y, 0.0);
    glRotatef(pacman.angle, 0.0, 0.0, 1.0);
    glColor3f(0.0, 0.0, 0.0); // Preto
    glBegin(GL_TRIANGLES);
    glVertex2f(0.0, 0.0);
    glVertex2f(22.0, 13.0);
    glVertex2f(22.0, -10.0);
    glEnd();
    glPopMatrix();
}

void desenhaLabirinto() {
    printf("[LOG] desenhaLabirinto()\n");
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
bool pode_andar(POSICAO p) {
    // Verificar se as coordenadas correspondem a uma parede
    // if (!eh_parede(p)) return true;
    return false;
}

bool eh_parede(POSICAO p, int borda){
    // Converter as coordenadas do Pac-Man para as coordenadas do labirinto
    int x = (int) ((p.x / TILE_SIZE) + borda);
    int y = (int) ((p.y / TILE_SIZE) + borda);

    // Verificar se as coordenadas correspondem a uma parede
    if(maze[y][x] == PAREDE) return true;
    return false;
}

bool eh_FoodPill(POSICAO p){
    // Converter as coordenadas do Pac-Man para as coordenadas do labirinto
    int x = (int) (p.x / TILE_SIZE);
    int y = (int) (p.y / TILE_SIZE);

    // Verificar se as coordenadas correspondem a uma comida
    if(maze[y][x] == FOOD_PILL) {
        havePowerPill += 1;
        return true;
    }
    return false;
}

bool eh_PowerPill(POSICAO p){
    // Converter as coordenadas do Pac-Man para as coordenadas do labirinto
    int x = (int) (p.x / TILE_SIZE);
    int y = (int) (p.y / TILE_SIZE);

    // Verificar se as coordenadas correspondem a uma pirula de poder
    if(maze[y][x] == POWER_PILL) {
        havePowerPill += 1;
        return true;
    }
    return false;
}

bool eh_fantasma(POSICAO p, POSICAO f){
    // Converter as coordenadas do Pac-Man para as coordenadas do labirinto
    int px = (int) (p.x / TILE_SIZE);
    int py = (int) (p.y / TILE_SIZE);

    // Converter as coordenadas do Fantasma para as coordenadas do labirinto
    int fx = (int) (f.x / TILE_SIZE);
    int fy = (int) (f.y / TILE_SIZE);

    // Verificar se as coordenadas correspondem a uma pirula de poder
    if(px == fx && py == fy) return true;
    return false;
}

