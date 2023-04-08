/* PACMAN - 2D modeling project with OpenGL 
 *  - Compilar: g++ pacman.cpp -lSOIL -lglfw -lglut -lGL -lGLU -o pacman.out
 *  - Executar: ./pacman.out
 */

//#define _USE_MATH_DEFINES           //# Para rodar no Visual Studio descomente essa linha
#include <stdio.h>
#include <math.h>
#include <unistd.h> 
#include <GL/glut.h>
#include <GLFW/glfw3.h>
#include <SOIL/SOIL.h>
#include "pacman.h"

/************************************************************************************************************************************/
/*******                                                 VARIAVEIS GLOBAIS                                                    *******/
/************************************************************************************************************************************/
bool gFlag_habilita_logs = true;

POSICAO pacman; // posição atual do pacman
int haveFoodPill = 0;  // qtd de pilulas de comida
int havePowerPill = 0; // qtd de pilulas de poder

char ultima_tecla_precionada;
char tecla_precionada = DIREITA;

bool game_over = false;

/************************************************************************************************************************************/
/*******                                                      MAIN                                                            *******/
/************************************************************************************************************************************/
int main(int argc, char** argv){
    // Inicializa a biblioteca FreeGLUT
    glutInit(&argc, argv); 
    GLFWwindow* window;

    // Inicializa o GLFW
    if (!glfwInit()) return -1;

    glutInitDisplayMode(GLUT_DOUBLE);
    glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);

    // Atribuindo a posição inicial do Pacman
    pacman.x = SCREEN_WIDTH/4; // coordenada da horizontal
    pacman.y = SCREEN_HEIGHT/4; // coordenada da vertical
    pacman.angle = 0.0;
    pacman.scale = 1.0;

    //if(gFlag_habilita_logs) printf("[LOG] main(): pacman (x, y): (%d,%d )\n", int(pacman.x), int(pacman.y));

    // Cria uma janela em modo janela e seu contexto OpenGL
    window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "PacMan", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    // Torna o contexto da janela atual
    glfwMakeContextCurrent(window);

    // Define a matriz de projeção
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, SCREEN_WIDTH, 0, SCREEN_HEIGHT);

    // Define a matriz modelview
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glfwSetKeyCallback(window, keyboard);

    // MAIN LOOP
    while (!glfwWindowShouldClose(window)) {
        if(gFlag_habilita_logs) printf("[LOG] Main loop\n");

        // Limpa a tela
        glClearColor(0.0, 0.0, 0.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);

        // Desenha os elementos no mapa e o Pacman
        glPushMatrix();
        desenhaLabirinto();
        desenhaFoodPill();
        desenhaFantasma();
        desenhaPowerPill();
        morreu(); // Verrifica se o Pacman "moreu"
        desenhaPacman();
        glPopMatrix();

        // Troca buffers e eventos de votação
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Terminate GLFW
    glfwTerminate();
    return 0; 
}

/*************************************************************************************************************************************
*******                                                 ESCOPO DAS FUNÇÕES                                                     *******
*************************************************************************************************************************************/

// Função para tratar as entradas no teclado
void keyboard(GLFWwindow* window, int key, int scancode, int action, int mods) {
    // Fecha a janela quando o "ESC" é precionado
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) glfwSetWindowShouldClose(window, GLFW_TRUE);
    
    if(!(game_over)){
        POSICAO nova_posicao;
        // Trata os comandos para movimentar o Pacmen:
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
                
                // Verifica se na nova posição para onde o Pacman vai tem algo para comer
                eh_FoodPill(nova_posicao);
                eh_PowerPill(nova_posicao);

                // Verifica se na nova posição para onde o Pacman vai tem um fantasma
                if (eh_fantasma(nova_posicao)){
                    // Verifica se o Pacman tem a power pill para mata o fantasma
                    if (havePowerPill){
                    if(gFlag_habilita_logs) printf(">> MATA FANTASMA << \n");
                        maze[19 - (int)(nova_posicao.y/TILE_SIZE)][(int)(nova_posicao.x / TILE_SIZE)] = VAZIO;
                        havePowerPill--;
                    }else{
                        if(gFlag_habilita_logs) printf(">> GAMER OVER << \n");
                        game_over = true;
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

                // Verifica se na nova posição para onde o Pacman vai tem algo para comer
                eh_FoodPill(nova_posicao);
                eh_PowerPill(nova_posicao);

                // Verifica se na nova posição para onde o Pacman vai tem um fantasma
                if (eh_fantasma(nova_posicao)) {
                    // Verifica se o Pacman tem a power pill para mata o fantasma
                    if (havePowerPill) {
                        if(gFlag_habilita_logs) printf(">> MATA FANTASMA << \n");
                        maze[19 - (int)(nova_posicao.y / TILE_SIZE)][(int)(nova_posicao.x / TILE_SIZE)] = VAZIO;
                        havePowerPill--;
                    }
                    else {
                        if(gFlag_habilita_logs) printf(">> GAMER OVER << \n");
                        game_over = true;
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
                
                // Verifica se na nova posição para onde o Pacman vai tem algo para comer
                eh_FoodPill(nova_posicao);
                eh_PowerPill(nova_posicao);

                // Verifica se na nova posição para onde o Pacman vai tem um fantasma
                if (eh_fantasma(nova_posicao)) {
                    // Verifica se o Pacman tem a power pill para mata o fantasma
                    if (havePowerPill) {
                        if(gFlag_habilita_logs) printf(">> MATA FANTASMA << \n");
                        maze[19 - (int)(nova_posicao.y / TILE_SIZE)][(int)(nova_posicao.x / TILE_SIZE)] = VAZIO;
                        havePowerPill--;
                    }
                    else {
                        if(gFlag_habilita_logs) printf(">> GAMER OVER << \n");
                        game_over = true;
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

                // Verifica se na nova posição para onde o Pacman vai tem algo para comer
                eh_FoodPill(nova_posicao);
                eh_PowerPill(nova_posicao);

                // Verifica se na nova posição para onde o Pacman vai tem um fantasma
                if (eh_fantasma(nova_posicao)) {
                    // Verifica se o Pacman tem a power pill para mata o fantasma
                    if (havePowerPill) {
                        if(gFlag_habilita_logs) printf(">> MATA FANTASMA << \n");
                        maze[19 - (int)(nova_posicao.y / TILE_SIZE)][(int)(nova_posicao.x / TILE_SIZE)] = VAZIO;
                        havePowerPill--;
                    }
                    else {
                        if(gFlag_habilita_logs) printf(">> GAMER OVER << \n");
                        game_over = true;
                    }
                }
                break;
        }

    }

    ultima_tecla_precionada = tecla_precionada;

    // atualiza a tela
    glfwSwapBuffers(window);
}

// Função para desenha o pacman
void desenhaPacman(){
    if(gFlag_habilita_logs) printf("[LOG] desenha_pacman()\n");

    // Desenha o avatar do Pacman
    glTranslatef(pacman.x, pacman.y, 0.0);
    glPushMatrix();
    glRotatef(pacman.angle, 0.0, 0.0, 1.0);
    glScalef(pacman.scale, pacman.scale, 1.0);
    glPopMatrix();
    glFlush();

    // Desenha o corpo do Pacman
    if (havePowerPill != 0){
        glColor3f(1.0, 0.5, 0.0); // laranja
    }else{
        glColor3f(1.0, 1.0, 0.0); // amarelo
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
    glScalef(pacman.scale, pacman.scale, 1.0);
    glColor3f(0.0, 0.0, 0.0); // Preto
    glBegin(GL_TRIANGLES);
    glVertex2f(0.0, 0.0);
    glVertex2f(20.0, 13.0);
    glVertex2f(20.0, -10.0);
    glEnd();
    glPopMatrix();
}

// Função para desenha os Fantasmas
void desenhaFantasma() {
    if(gFlag_habilita_logs) printf("[LOG] desenhaFantasma()\n");

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

// Função para verificar se o Pacman está "vivo", ou seja, se o jogo ja acabou
void morreu(){
    if(game_over){
        // Se o pacman "morreu", ele escolhe até sumir
        if (pacman.scale>0.0 ) {
            pacman.scale -= 0.1;
            glPushMatrix();
            desenhaPacman();
            glPopMatrix();
            if(gFlag_habilita_logs) printf("[LOG] morreu(): escala = %f\n",pacman.scale);
            sleep(0.75); // pausa o programa por 1 segundo
        }
    }
}

// Função para desenha o labirinto
void desenhaLabirinto() {
    if(gFlag_habilita_logs) printf("[LOG] desenhaLabirinto()\n");

    glLineWidth(2.0);
    glColor3f(0.0, 0.0, 1.0); // azul
    glBegin(GL_LINES);

    for (int i = 0; i < MAZE_HEIGHT; i++) {
        for (int j = 0; j < MAZE_WIDTH; j++) {
            int x = j * (SCREEN_WIDTH / MAZE_WIDTH);
            int y = (MAZE_HEIGHT - i - 1) * (SCREEN_HEIGHT / MAZE_HEIGHT);
            int cellWidth = SCREEN_WIDTH / MAZE_WIDTH;
            int cellHeight = SCREEN_HEIGHT / MAZE_HEIGHT;

            if (maze[i][j] == PAREDE) {
                // desenha a linha superior
                glVertex2f(x, y + cellHeight);
                glVertex2f(x + cellWidth, y + cellHeight);

                // desenha a linha esquerda
                glVertex2f(x, y);
                glVertex2f(x, y + cellHeight);

                // desenha a linha de baixo
                glVertex2f(x, y);
                glVertex2f(x + cellWidth, y);

                // desenha linha direita
                glVertex2f(x + cellWidth, y);
                glVertex2f(x + cellWidth, y + cellHeight);
            }
        }
    }

    glEnd();
}

// Função para desenha as pílulas de comida
void desenhaFoodPill() {
    if(gFlag_habilita_logs) printf("[LOG] desenhaFoodPill()\n");
    glLineWidth(2.0);
    glColor3f(1.0, 1.0, 1.0); // branco
    glBegin(GL_QUADS);

    for (int i = 0; i < MAZE_HEIGHT; i++) {
        for (int j = 0; j < MAZE_WIDTH; j++) {
            int x = (j * (SCREEN_WIDTH / MAZE_WIDTH))+20;
            int y = ((MAZE_HEIGHT - i - 1) * (SCREEN_HEIGHT / MAZE_HEIGHT))+20;
            int cellWidth = 10;
            int cellHeight = 10;

            if(gFlag_habilita_logs) printf("[LOG] desenhaFoodPill(): (x, y): (%d,%d)\n", x, y);

            if (maze[i][j] == FOOD_PILL) {
                // desenha a linha superior
                glVertex2f(x, y + cellHeight);
                glVertex2f(x + cellWidth, y + cellHeight);

                // desenha a linha esquerda
                glVertex2f(x, y);
                glVertex2f(x, y + cellHeight);

                // desenha a linha inferior
                glVertex2f(x, y);
                glVertex2f(x + cellWidth, y);

                // desenha a linha direita
                glVertex2f(x + cellWidth, y);
                glVertex2f(x + cellWidth, y + cellHeight);
            }
        }
    }

    glEnd();
}

// Função para desenha as pílulas de poder

void desenhaPowerPill() {
    if(gFlag_habilita_logs) printf("[LOG] desenhaPowerPill()\n");
    glLineWidth(2.0);
    glColor3f(1.0, 0.0, 0.0); // vermelho
    glBegin(GL_QUADS);

    for (int i = 0; i < MAZE_HEIGHT; i++) {
        for (int j = 0; j < MAZE_WIDTH; j++) {
            int x = (j * (SCREEN_WIDTH / MAZE_WIDTH))+20;
            int y = ((MAZE_HEIGHT - i - 1) * (SCREEN_HEIGHT / MAZE_HEIGHT))+20;
            int cellWidth = 10;
            int cellHeight = 10;

            if(gFlag_habilita_logs) printf("[LOG] desenhaPowerPill(): (x, y): (%d,%d)\n", x, y);

            if (maze[i][j] == POWER_PILL) {
                // desenha a linha superior
                glVertex2f(x, y + cellHeight);
                glVertex2f(x + cellWidth, y + cellHeight);

                // desenha a linha esquerda
                glVertex2f(x, y);
                glVertex2f(x, y + cellHeight);

                // desenha a linha inferior
                glVertex2f(x, y);
                glVertex2f(x + cellWidth, y);

                // desenha a linha direita
                glVertex2f(x + cellWidth, y);
                glVertex2f(x + cellWidth, y + cellHeight);
            }
        }
    }

    glEnd();
}

// Função para verificar se em determinada posição existe uma parede
bool eh_parede(POSICAO p){
    // Converter as coordenadas do Pac-Man para as coordenadas do labirinto
    int x = (int) (p.x / TILE_SIZE);
    int y = (int) (p.y / TILE_SIZE);
    y = 19 - y;

    // Verificar se as coordenadas correspondem a uma parede
    if (maze[y][x] == PAREDE) {
        if(gFlag_habilita_logs) printf("[LOG] eh_parede(): colidiu com\n");
        return true;
    }
    return false;
}

// Função para verificar se em determinada posição existe comida
bool eh_FoodPill(POSICAO p) {
    // Converter as coordenadas do Pac-Man para as coordenadas do labirinto
    int x = (int)(p.x / TILE_SIZE);
    int y = (int)(p.y / TILE_SIZE);
    y = 19 - y;

    // Verificar se as coordenadas correspondem a uma comida
    if (maze[y][x] == FOOD_PILL) {
        haveFoodPill += 1;
        maze[y][x] = VAZIO;
        if(gFlag_habilita_logs) printf("[LOG] eh_FoodPill(): achou comida: %d\n", haveFoodPill);
        return true;
    }
    return false;
}

// Função para verificar se em determinada posição existe uma pirula de poder
bool eh_PowerPill(POSICAO p){
    // Converter as coordenadas do Pac-Man para as coordenadas do labirinto
    int x = (int) (p.x / TILE_SIZE);
    int y = (int) (p.y / TILE_SIZE);
    y = 19 - y;

    // Verificar se as coordenadas correspondem a uma pirula de poder
    if(maze[y][x] == POWER_PILL) {
        havePowerPill += 1;
        maze[y][x] = VAZIO;
        if(gFlag_habilita_logs) printf("[LOG] eh_PowerPill(): achou power pill: %d\n", havePowerPill);
        return true;
    }
    return false;
}

// Função para verificar se em determinada posição existe um fantasma
bool eh_fantasma(POSICAO p){
    /// Converter as coordenadas do Pac-Man para as coordenadas do labirinto
    int x = (int) (p.x / TILE_SIZE);
    int y = (int) ((p.y) / TILE_SIZE);
    y = 19 - y;

    // Verificar se as coordenadas correspondem a uma pirula de poder
    if(maze[y][x] == FANTASMA) return true;
    if(gFlag_habilita_logs) printf("[LOG] eh_fantasma(): BOO!\n");
    return false;
}