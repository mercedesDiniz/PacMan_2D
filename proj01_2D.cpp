// g++ -o proj01.out proj01_2D.cpp -lglut -lGLU -lGL -lm
#include <GL/glut.h>

float avatar_x = 0.0;
float avatar_y = 0.0;
float avatar_angle = 0.0;
float avatar_scale = 1.0;

void display()  
{  
    glClear(GL_COLOR_BUFFER_BIT);  

    // Desenha a galáxia genérica
    glBegin(GL_POINTS);
    for (int i = 0; i < 10000; i++) {
        float x = (float) rand() / RAND_MAX * 2 - 1;
        float y = (float) rand() / RAND_MAX * 2 - 1;
        glColor3f(1.0, 1.0, 1.0);
        glVertex2f(x, y);
    }
    glEnd();

   // Desenha o avatar triangular azul
    glPushMatrix();
    glTranslatef(avatar_x, avatar_y, 0.0);
    glRotatef(avatar_angle, 0.0, 0.0, 1.0);
    glScalef(avatar_scale, avatar_scale, 1.0);
    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_TRIANGLES);
        glVertex2f(0.0, 0.1);
        glVertex2f(-0.05, -0.05);
        glVertex2f(0.05, -0.05);
    glEnd();
    glPopMatrix();

    glFlush();  
}  

void keyboard(unsigned char key, int x, int y)
{
    switch (key) {
        case 'a':
            avatar_x -= 0.1;
            break;
        case 'w':
            avatar_y += 0.1;
            break;
        case 's':
            avatar_y -= 0.1;
            break;
        case 'd':
            avatar_x += 0.1;
            break;
        case 'e':
            avatar_scale += 0.1;
            break;
        case 'q':
            avatar_scale -= 0.1;
            break;
    }
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