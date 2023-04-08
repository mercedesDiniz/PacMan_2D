/*  Compilar:
        g++ pacman.cpp -lglfw -lglut -lGL -lGLU -o pacman.out
    Executar:
        ./pacman.out
*/

//#define _USE_MATH_DEFINES           //# Para rodar no Visual Studio descomente essa linha
#include <stdio.h>
#include <GL/glut.h>
#include <GLFW/glfw3.h>
#include <SOIL/SOIL.h>
#include <math.h>
#include "pacman.h"

// Declarando Variaveis Globais
POSICAO pacman; // posição atual do pacman
POSICAO fantasme01; // posição atual do pacman
POSICAO fantasme02; // posição atual do pacman

int haveFoodPill = 0;  // qtd de pilulas de comida
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

    pacman.x = SCREEN_WIDTH/4; // coordenada da horizontal
    pacman.y = SCREEN_HEIGHT/4; // coordenada da vertical
    pacman.angle = 0.0;
    pacman.scale = 1.0;

    printf("[LOG] main: pacman x: %d\n", int(pacman.x));
    printf("[LOG] main: pacman y: %d\n", int(pacman.y));

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
        //printf("[LOG] Main loop\n");

        // Clear the screen
        glClearColor(0.0, 0.0, 0.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);

        // Draw the maze and Pacman
        glPushMatrix();
        desenhaLabirinto();
        desenhaFoodPill();
        desenhaFantasma();
        desenhaPowerPill();
        desenhaPacman();
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

// Função tratar as entradas no teclado
void keyboard(GLFWwindow* window, int key, int scancode, int action, int mods) {
    //printf("[LOG] keyboard()\n");

    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) glfwSetWindowShouldClose(window, GLFW_TRUE);

    POSICAO nova_posicao;
    switch (key) {
    case ESQUERDA:
        tecla_precionada = ESQUERDA;

        // Verifica se a nova posição para onde o Pac-Man quer ir é uma parede
        nova_posicao = { static_cast<float>(pacman.x - PASSO - 9), static_cast<float>(pacman.y) };
        if (!eh_parede(nova_posicao)) {
            pacman.x -= PASSO;
            if (ultima_tecla_precionada != tecla_precionada) {
                pacman.angle = 0.0;
                pacman.angle -= 180.0;
            }
        }
        eh_FoodPill(nova_posicao);
        eh_PowerPill(nova_posicao);
        if (eh_fantasma(nova_posicao)){
            if (havePowerPill){
              printf(">> MATA FANTASMA << ");
              maze[19 - (int)(nova_posicao.y/TILE_SIZE)][(int)(nova_posicao.x / TILE_SIZE)] = VAZIO;
              havePowerPill--;
            }else{
              printf(">> GAMER OVER << ");
            }
        }


        break;

    case DIREITA:
        tecla_precionada = DIREITA;

        // Verifica se a nova posição para onde o Pac-Man quer ir é uma parede
        nova_posicao = { static_cast<float>(pacman.x + PASSO + 9), static_cast<float>(pacman.y) };
        if (!eh_parede(nova_posicao)) {
            pacman.x += PASSO;
            if (ultima_tecla_precionada != tecla_precionada) {
                pacman.angle = 0.0;
                pacman.angle += 360.0;
            }
        }
        eh_FoodPill(nova_posicao);
        eh_PowerPill(nova_posicao);
        if (eh_fantasma(nova_posicao)) {
            if (havePowerPill) {
                printf(">> MATA FANTASMA << ");
                maze[19 - (int)(nova_posicao.y / TILE_SIZE)][(int)(nova_posicao.x / TILE_SIZE)] = VAZIO;
                havePowerPill--;
            }
            else {
                printf(">> GAMER OVER << ");
            }
        }
        break;

    case CIMA:
        tecla_precionada = CIMA;

        // Verifica se a nova posição para onde o Pac-Man quer ir é uma parede
        nova_posicao = { static_cast<float>(pacman.x), static_cast<float>(pacman.y + PASSO + 9) };
        if (!eh_parede(nova_posicao)) {
            pacman.y += PASSO;
            if (ultima_tecla_precionada != tecla_precionada) {
                pacman.angle = 0.0;
                pacman.angle += 90.0;
            }
        }
        eh_FoodPill(nova_posicao);
        eh_PowerPill(nova_posicao);
        if (eh_fantasma(nova_posicao)) {
            if (havePowerPill) {
                printf(">> MATA FANTASMA << ");
                maze[19 - (int)(nova_posicao.y / TILE_SIZE)][(int)(nova_posicao.x / TILE_SIZE)] = VAZIO;
                havePowerPill--;
            }
            else {
                printf(">> GAMER OVER << ");
            }
        }
        break;

    case BAIXO:
        tecla_precionada = BAIXO;

        // Verifica se a nova posição para onde o Pac-Man quer ir é uma parede
        nova_posicao = { static_cast<float>(pacman.x), static_cast<float>(pacman.y - PASSO - 9) };
        if (!eh_parede(nova_posicao)) {
            pacman.y -= PASSO;
            if (ultima_tecla_precionada != tecla_precionada) {
                pacman.angle = 0.0;
                pacman.angle -= 90.0;
            }
        }
        eh_FoodPill(nova_posicao);
        eh_PowerPill(nova_posicao);
        if (eh_fantasma(nova_posicao)) {
            if (havePowerPill) {
                printf(">> MATA FANTASMA << ");
                maze[19 - (int)(nova_posicao.y / TILE_SIZE)][(int)(nova_posicao.x / TILE_SIZE)] = VAZIO;
                havePowerPill--;
            }
            else {
                printf(">> GAMER OVER << ");
            }
        }
        break;
    }
    ultima_tecla_precionada = tecla_precionada;

    // atualiza a tela
    glfwSwapBuffers(window);
}

// Função para desenhar o pacman
void desenhaPacman(){
    //printf("[LOG] desenha_pacman()\n");
    // Desenha o avatar do Pacman
    glTranslatef(pacman.x, pacman.y, 0.0);
    glPushMatrix();
    glRotatef(pacman.angle, 0.0, 0.0, 1.0);
    glPopMatrix();
    glFlush();
    glScalef(pacman.scale, pacman.scale, 1.0);

    // Desenha o corpo do Pacman
    if (havePowerPill != 0){
        glColor3f(0.0, 0.0, 1.0);
    }else{
        glColor3f(1.0, 1.0, 0.0);
    }
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
    glVertex2f(20.0, 13.0);
    glVertex2f(20.0, -10.0);
    glEnd();
    glPopMatrix();
}

void desenhaFantasma() {
    for (int i = 0; i < MAZE_HEIGHT; i++) {
        for (int j = 0; j < MAZE_WIDTH; j++) {
            if (maze[i][j] == FANTASMA) {
                // Define as coordenadas do quadrado
                int x = (j * (SCREEN_WIDTH / MAZE_WIDTH))+20;
                int y = ((MAZE_HEIGHT - i - 1) * (SCREEN_HEIGHT / MAZE_HEIGHT))+20;
                int cellWidth = 10;
                int cellHeight = 10;
                float x1 = x + (cellWidth / 2) - 24;
                float y1 = y + (cellHeight / 2) - 24;
                float x2 = x + (cellWidth / 2) + 24;
                float y2 = y + (cellHeight / 2) + 24;

                // Carrega a textura
                GLuint textureID = SOIL_load_OGL_texture("texturas/fantasma1.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);

                // Ativa a textura
                glEnable(GL_TEXTURE_2D);
                glBindTexture(GL_TEXTURE_2D, textureID);

                // Desenha o quadrado com a textura
                glBegin(GL_QUADS);
                glTexCoord2f(0, 0);
                glVertex2f(x1, y1);
                glTexCoord2f(0, 1);
                glVertex2f(x1, y2);
                glTexCoord2f(1, 1);
                glVertex2f(x2, y2);
                glTexCoord2f(1, 0);
                glVertex2f(x2, y1);
                glEnd();

                // Desativa a textura
                glDisable(GL_BLEND);
                glDisable(GL_TEXTURE_2D);
            }
        }
    }
}

// Função para desenhar o labirinto
void desenhaLabirinto() {
    //printf("[LOG] desenhaLabirinto()\n");
    glLineWidth(2.0);
    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_LINES);

    for (int i = 0; i < MAZE_HEIGHT; i++) {
        for (int j = 0; j < MAZE_WIDTH; j++) {
            int x = j * (SCREEN_WIDTH / MAZE_WIDTH);
            int y = (MAZE_HEIGHT - i - 1) * (SCREEN_HEIGHT / MAZE_HEIGHT);
            int cellWidth = SCREEN_WIDTH / MAZE_WIDTH;
            int cellHeight = SCREEN_HEIGHT / MAZE_HEIGHT;

            if (maze[i][j] == PAREDE) {
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

void desenhaFoodPill() {
    //printf("[LOG] desenhaLabirinto()\n");
    glLineWidth(2.0);
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_QUADS);

    for (int i = 0; i < MAZE_HEIGHT; i++) {
        for (int j = 0; j < MAZE_WIDTH; j++) {
            int x = (j * (SCREEN_WIDTH / MAZE_WIDTH))+20;
            int y = ((MAZE_HEIGHT - i - 1) * (SCREEN_HEIGHT / MAZE_HEIGHT))+20;
            int cellWidth = 10;
            int cellHeight = 10;
            //printf("[LOG] desenhaFoodPill: x:%d/\n", x);
            //printf("[LOG] desenhaFoodPill: y:%d/\n", y);

            if (maze[i][j] == FOOD_PILL) {
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

void desenhaPowerPill() {
    //printf("[LOG] desenhaLabirinto()\n");
    glLineWidth(2.0);
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_QUADS);

    for (int i = 0; i < MAZE_HEIGHT; i++) {
        for (int j = 0; j < MAZE_WIDTH; j++) {
            int x = (j * (SCREEN_WIDTH / MAZE_WIDTH))+20;
            int y = ((MAZE_HEIGHT - i - 1) * (SCREEN_HEIGHT / MAZE_HEIGHT))+20;
            int cellWidth = 10;
            int cellHeight = 10;
            //printf("[LOG] desenhaFoodPill: x:%d/\n", x);
            //printf("[LOG] desenhaFoodPill: y:%d/\n", y);

            if (maze[i][j] == POWER_PILL) {
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
bool eh_parede(POSICAO p){
    // Converter as coordenadas do Pac-Man para as coordenadas do labirinto
    int x = (int) (p.x / TILE_SIZE);
    int y = (int) (p.y / TILE_SIZE);
    y = 19 - y;
    printf("x: %d\n",x);
    printf("y: %d\n" ,y);
    printf("\n");

    // Verificar se as coordenadas correspondem a uma parede
    if (maze[y][x] == PAREDE) {
        printf("colidiu\n");
        return true;
    }
    return false;
}

// Função para verificar se o Pac-Man encontrou comida
bool eh_FoodPill(POSICAO p) {
    // Converter as coordenadas do Pac-Man para as coordenadas do labirinto
    int x = (int)(p.x / TILE_SIZE);
    int y = (int)(p.y / TILE_SIZE);
    y = 19 - y;

    // Verificar se as coordenadas correspondem a uma comida
    if (maze[y][x] == FOOD_PILL) {
        haveFoodPill += 1;
        maze[y][x] = VAZIO;
        printf("[LOG] Main: FoodPill: %d\n", haveFoodPill);
        return true;
    }
    return false;
}

// Função para verificar se o Pac-Man encontrou uma pirula de poder
bool eh_PowerPill(POSICAO p){
    // Converter as coordenadas do Pac-Man para as coordenadas do labirinto
    int x = (int) (p.x / TILE_SIZE);
    int y = (int) (p.y / TILE_SIZE);
    y = 19 - y;
    // Verificar se as coordenadas correspondem a uma pirula de poder
    if(maze[y][x] == POWER_PILL) {
        havePowerPill += 1;
        maze[y][x] = VAZIO;
        printf("[LOG] Main: PowerPill: %d\n", havePowerPill);
        return true;
    }
    return false;
}

// Função para verificar se o Pac-Man colidiu com uma fantasma
bool eh_fantasma(POSICAO p){
    /// Converter as coordenadas do Pac-Man para as coordenadas do labirinto
    int x = (int) (p.x / TILE_SIZE);
    int y = (int) ((p.y) / TILE_SIZE);
    y = 19 - y;
    // Verificar se as coordenadas correspondem a uma pirula de poder
    if(maze[y][x] == FANTASMA) return true;
    return false;
}

