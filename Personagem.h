#ifndef Personagem_hpp
#define Personagem_hpp
#include <iostream>
using namespace std;

#include "Poligono.h"

class Personagem{
    //Poligono *modelo;

public:
    Ponto Posicao, Escala, Direcao, Velocidade;
    float rotacao;
    int modelo;
    void desenha();
};


#endif
