// g++ -o proj01.out proj01_2D.cpp -lglut -lGLU -lGL -lm
#include <GL/glut.h>
#include <cmath>

float avatar_x = 0.0;
float avatar_y = 0.0;
float avatar_angle = 0.0;
float avatar_scale = 1.0;
char ultima_tecla_precionada;
char tecla_precionada = 'd';
void display()  
{  
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);  // Fundo preto

   // Desenha o avatar do Pacman
    glPushMatrix();
    glTranslatef(avatar_x, avatar_y, 0.0);
    glRotatef(avatar_angle, 0.0, 0.0, 1.0);
    glScalef(avatar_scale, avatar_scale, 1.0);

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

    glPopMatrix();

    glFlush();  
}  

void keyboard(unsigned char key, int x, int y)
{
    switch (key) {
        case 'a':
            tecla_precionada = 'a';
            avatar_x -= 0.1;
            if(ultima_tecla_precionada != tecla_precionada){
                avatar_angle -= 180.0;
            }
            break;
        case 'w':
            tecla_precionada = 'w';
            avatar_y += 0.1;
            if(ultima_tecla_precionada != tecla_precionada){
                avatar_angle += 90.0;
            }
            break;
        case 's':
            tecla_precionada = 's';
            avatar_y -= 0.1;
            if(ultima_tecla_precionada != 's'){
                avatar_angle += 90.0;
            }
            break;
        case 'd':
            tecla_precionada = 'd';
            avatar_x += 0.1;
            if(ultima_tecla_precionada != tecla_precionada){
                avatar_angle += 180.0;
            }
            break;
        case 'e':
            tecla_precionada = 'e';
            avatar_scale += 0.1;
            break;
        case 'q':
            tecla_precionada = 'q';
            avatar_scale -= 0.1;
            break;
    }
    ultima_tecla_precionada = tecla_precionada;
    glutPostRedisplay();
}

int main(int argc, char** argv)  
{  
    glutInit(&argc, argv);  
    glutCreateWindow("Galáxia");  
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMainLoop();  
    return 0;  
}