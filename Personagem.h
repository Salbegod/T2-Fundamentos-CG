#ifndef Personagem_hpp
#define Personagem_hpp
#include <iostream>
using namespace std;

#include "Poligono.h"

class Personagem{
    Poligono sprite;

public:
    Poligono envelope;
    Personagem(std::string nome, std::string tipo, float posX, float posY, float posZ);
    Personagem(std::string nome, std::string tipo);
    Ponto Posicao, Escala, Direcao, Velocidade;
    float rotacao;
    std::string flag;
    void desenha();
private:
    float x, y, z;
};


#endif
