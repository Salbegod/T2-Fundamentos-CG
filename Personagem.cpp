#include "Personagem.h"


//void DesenhaPersonagem();
//void DesenhaRetangulo();
// ***********************************************************
//  void InstanciaPonto(Ponto3D *p, Ponto3D *out)
//  Esta funcao calcula as coordenadas de um ponto no
//  sistema de referencia do universo (SRU), ou seja,
//  aplica as rotacoes, escalas e translacoes a um
//  ponto no sistema de referencia do objeto (SRO).
// ***********************************************************

Personagem::Personagem(std::string nome, std::string tipo, float posX, float posY, float posZ)
{
    sprite.LePoligono("sprites\\"+nome+".txt");
    this->flag = tipo;
    this->x = posX;
    this->y = posY;
    this->z = posZ;
    envelope = sprite.criaEnvelope();
}

Personagem::Personagem(std::string nome, std::string tipo)
{
    sprite.LePoligono("sprites\\"+nome+".txt");
    this->flag = tipo;
    this->x = 0;
    this->y = 0;
    this->z = 0;
    envelope = sprite.criaEnvelope();
}

void InstanciaPonto(Ponto &p, Ponto &out)
{
    GLfloat ponto_novo[4];
    GLfloat matriz_gl[4][4];
    int  i;

    glGetFloatv(GL_MODELVIEW_MATRIX,&matriz_gl[0][0]);

    for(i=0;i<4;i++)
    {
        ponto_novo[i]= matriz_gl[0][i] * p.x+
        matriz_gl[1][i] * p.y+
        matriz_gl[2][i] * p.z+
        matriz_gl[3][i];
    }
    out.x=ponto_novo[0];
    out.y=ponto_novo[1];
    out.z=ponto_novo[2];
}

Ponto InstanciaPonto(Ponto P)
{
    Ponto temp;
    InstanciaPonto(P, temp);
    return temp;
}


void Personagem::desenha()
{
    // aplica as transformacoes geometricas no modelo
    // desenha a geometria do objeto

    glPushMatrix();
    glTranslatef(Posicao.x+x, Posicao.y+y, 0);
    glRotatef(rotacao, 0, 0, 1);
    Ponto PosicaoDoPersonagem;
    Ponto Origem (x,y,z);
    InstanciaPonto(PosicaoDoPersonagem, Origem);
    //PosicaoDoPersonagem.imprime(); cout << endl;
    sprite.desenhaPoligono();
    glPopMatrix();
}
