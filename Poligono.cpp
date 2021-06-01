//
//  Poligono.cpp
//  OpenGLTest
//
//  Created by Márcio Sarroglia Pinho on 18/08/20.
//  Copyright © 2020 Márcio Sarroglia Pinho. All rights reserved.
//
#include <iostream>
#include <fstream>
using namespace std;

#include "Poligono.h"

Poligono::Poligono()
{

}

void Poligono::insereVertice(Ponto p)
{
    Vertices.push_back(p);
}

void Poligono::insereVertice(Ponto p, int pos)
{
    if ((pos < 0) || (pos>Vertices.size()))
    {
        cout << "Metodo " << __FUNCTION__ << ". Posicao Invalida. Vertice nao inserido." << endl;
        return;
    }
    Vertices.insert(Vertices.begin()+pos, p);
}

Ponto Poligono::getVertice(int i)
{
    return Vertices[i];
}
void Poligono::desenhaPoligono()
{
    glBegin(GL_LINE_LOOP);
    for (int i=0; i<Vertices.size(); i++)
        glVertex3f(Vertices[i].x,Vertices[i].y,Vertices[i].z);
    glEnd();
}
void Poligono::desenhaVertices()
{
    glBegin(GL_POINTS);
    for (int i=0; i<Vertices.size(); i++)
        glVertex3f(Vertices[i].x,Vertices[i].y,Vertices[i].z);
    glEnd();
}
void Poligono::imprime()
{
    for (int i=0; i<Vertices.size(); i++)
        Vertices[i].imprime();
}
unsigned long Poligono::getNVertices()
{
    return Vertices.size();
}

void Poligono::obtemLimites(Ponto &Min, Ponto &Max)
{
    Max = Min = Vertices[0];

    for (int i=0; i<Vertices.size(); i++)
    {
        Min = ObtemMinimo (Vertices[i], Min);
        Max = ObtemMaximo (Vertices[i], Max);
    }
}

Poligono Poligono :: criaEnvelope() {
    Poligono envelope;
    float xMaisDir = Vertices[0].x, xMaisEsq = Vertices[0].x, yMaisAcima = Vertices[0].y, yMaisAbaixo = Vertices[0].y;

    for (int i = 0; i < Vertices.size(); i++)
    {
        Ponto Atual = Vertices[i];
        if (Atual.x > xMaisDir)
        {
            xMaisDir = Atual.x;
        }
        if (Atual.x < xMaisEsq)
        {
            xMaisEsq = Atual.x;
        }
        if (Atual.y > yMaisAcima)
        {
            yMaisAcima = Atual.y;
        }
        if (Atual.y < yMaisAbaixo)
        {
            yMaisAbaixo = Atual.y;
        }
    }
    envelope.insereVertice(Ponto(xMaisDir, yMaisAcima)); // ponto mais alto e mais para a direita
    envelope.insereVertice(Ponto(xMaisDir, yMaisAbaixo)); // ponto mais baixo e mais para a direita
    envelope.insereVertice(Ponto(xMaisEsq,yMaisAbaixo)); // ponto mais baixo e mais para esquerda
    envelope.insereVertice(Ponto(xMaisEsq,yMaisAcima)); // ponto mais alto e mais para esquerda
    return envelope;

}

// **********************************************************************
//
// **********************************************************************
void Poligono::LePoligono(std::string nome)
{
    ifstream input;            // ofstream arq;
    input.open(nome, ios::in); //arq.open(nome, ios::out);
    if (!input)
    {
        cout << "Erro ao abrir " << nome << ". " << endl;
        exit(0);
    }
    cout << "Lendo arquivo " << nome << "...";
    string S;
    //int nLinha = 0;
    unsigned int qtdVertices;

    input >> qtdVertices;  // arq << qtdVertices

    for (int i=0; i< qtdVertices; i++)
    {
        double x,y;
        // Le cada elemento da linha
        input >> x >> y; // arq << x  << " " << y << endl
        if(!input)
            break;
        //nLinha++;
        insereVertice(Ponto(x,y));
    }
    cout << "Poligono lido com sucesso!" << endl;

}
