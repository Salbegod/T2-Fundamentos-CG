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
#include "Personagem.h"

Temporizador T;
double AccumDeltaT=0;
Ponto Min, Max;
bool keys[256];
Personagem jogador ("nave3","jogador", 0, -13, 0);
Personagem predio ("predio2", "cenario", 10, -15, 0);
Personagem chao ("chao", "cenario", 0, -15, 0);

static void init()
{
    glClearColor( 0.25f, 0.25f, 0.75f, 1.0f );
    glutIgnoreKeyRepeat(0);
    Min = Ponto (-20, -20);
    Max = Ponto (20, 20);
}

static void desenhaAtores()
{
    jogador.desenha();
    predio.desenha();
    chao.desenha();
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

    desenhaAtores();

    glutSwapBuffers();
}


void keyboard_down(unsigned char key, int x, int y)
{
    switch ( key )
	{

    case 'a':
        keys[4] = true;
        break;

    case 'd':
        keys[5] = true;
        break;

    default:
        break;
	}
}

void keyboard_up(unsigned char key, int x, int y)
{
    switch ( key )
	{

    case 'a':
        keys[4] = false;
        break;

    case 'd':
        keys[5] = false;
        break;

    default:
        break;
	}
}

void arrow_down ( int a_keys, int x, int y ) //Detecta quando uma SETA e pressionada (pra baixo)
{
	switch ( a_keys )
	{

    case GLUT_KEY_UP:           //UP
        keys[0] = true;
        break;

    case GLUT_KEY_DOWN:         //DOWN
        keys[1] = true;
        break;

    case GLUT_KEY_LEFT:         //LEFT
        keys[2] = true;
        break;

    case GLUT_KEY_RIGHT:        //RIGHT
        keys[3] = true;
        break;

    default:                //DEFAULT
        break;
	}
}

void arrow_up(int a_keys, int x, int y) //Detecta quando uma SETA e solta (pra cima)
{
    switch ( a_keys )
	{

    case GLUT_KEY_UP:           //UP
        keys[0] = false;
        break;

    case GLUT_KEY_DOWN:         //DOWN
        keys[1] = false;
        break;

    case GLUT_KEY_LEFT:         //LEFT
        keys[2] = false;
        break;

    case GLUT_KEY_RIGHT:        //RIGHT
        keys[3] = false;
        break;

    default:                //DEFAULT
        break;
	}
}

void controle() //Controla o movimento do personagem de acordo com os botoes pressionados (soma um valor nas pos. dele)
{
    if(keys[0]) // CIMA
    {
        jogador.Posicao.soma(0,0.5,0);
    }
    if(keys[1]) // BAIXO
    {
        jogador.Posicao.soma(0,-0.5,0);
    }
    if(keys[2]) // ESQUERDA
    {
        jogador.Posicao.soma(-0.5,0,0);
    }
    if(keys[3]) // DIREITA
    {
        jogador.Posicao.soma(0.5,0,0);
    }
    if(keys[4]) //ROTACIONA ESQUERDA
    {
        if(jogador.rotacao >= 80)
        {

        }
        else
        {
            jogador.rotacao += 5;
        }
    }
    if(keys[5]) //ROTACIONA DIREITA
    {
        if(jogador.rotacao <= -80)
        {

        }
        else
        {
            jogador.rotacao += -5;
        }
    }
}

static void idle(void)
{
    double dt;
    dt = T.getDeltaT();
    AccumDeltaT += dt;

    if(AccumDeltaT > 1.0/60)
    {
        AccumDeltaT = 0;
        controle();
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
    glutKeyboardFunc( keyboard_down );
    glutKeyboardUpFunc( keyboard_up );
    glutSpecialFunc( arrow_down );
    glutSpecialUpFunc( arrow_up );

    glutMainLoop();
    return 0;
}
