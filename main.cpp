#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include <fstream>.h>
#include "Temporizador.h"
#include "Poligono.h"
#include "Ponto.h"

Temporizador T;
double AccumDeltaT=0;
Ponto Min, Max;
Poligono nave;

static void init()
{
    glClearColor( 0.25f, 0.25f, 0.75f, 1.0f );
    glutIgnoreKeyRepeat(0);
    Min = Ponto (-20, -20);
    Max = Ponto (20, 20);
    nave.LePoligono("sprites\\nave3.txt");
}

static void reshape(int w, int h)
{
    // Reset the coordinate system before modifying
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // Define a area a ser ocupada pela area OpenGL dentro da Janela
    glViewport(0, 0, w, h);  // Janela de Exibicao
    // Define os limites logicos da area OpenGL dentro da Janela

    glOrtho(Min.x,Max.x, Min.y,Max.y, 0,1); //Janela de Selecao
    //glOrtho(0,10, 0,10, 0,1);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

static void display(void)
{

    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    nave.desenhaPoligono();

    glutSwapBuffers();
}


static void keyboard(unsigned char key, int x, int y)
{

}

static void idle(void)
{
    double dt;
    dt = T.getDeltaT();
    AccumDeltaT += dt;

    if(AccumDeltaT > 1.0/60)
    {
        AccumDeltaT = 0;
        glutPostRedisplay();
    }
}

int main(int argc, char *argv[])
{
    glutInit( &argc, argv );
    glutInitDisplayMode( GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB );
    glutInitWindowPosition( 0,0 );
    glutInitWindowSize( 1280,720 );

    glutCreateWindow( "T2" );

    init();

    glutDisplayFunc( display );
    glutIdleFunc( idle );
    glutReshapeFunc( reshape );
    glutKeyboardFunc( keyboard );

    glutMainLoop();
    return 0;
}
