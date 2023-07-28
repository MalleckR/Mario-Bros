//CLASSE SEM USO, POIS MIGREI A FUNÇÃO DE DESENHAR AS PLATAFORMAS PARA MAIN, POIS NÃO CONSEGUIR UTILIZAR TEXTURA NAS CLASSES :-(.
//PORÉM ELA AINDA DESENHAR UM POLIGONO SÓ QUE SEM TEXTURA.

#include "plataforma.h"
#include <cmath>
#include <GL/gl.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <iostream>
#include <unistd.h>

//contrutor que receber parametros que serão usados para desenhar os pontos do poligono.
plataforma::plataforma(glm::vec2 ponto1, glm::vec2 ponto2, glm::vec2 ponto3, glm::vec2 ponto4)
{
    this->pontoum = ponto1;
    this->pontodois = ponto2;
    this->pontotres = ponto3;
    this->pontoquatro = ponto4;

}


//Função que ira desenhar os pontos que formaram as faces da plataforma, para duas primeiras faces utilizei os valores passado por parametro
//porém as demais trabalhei com valores fixo só para testes mas como migrei a criação para main por conta da textura então não vi necessidade de deixar um só uso de valores.
void plataforma::desenha(){

    glPushMatrix();
    glColor3f(0.5, 0.3, 0.2);
    glBegin(GL_QUADS);
        glVertex3f(pontoum.x, pontoum.y, 0);
        glVertex3f(pontodois.x, pontodois.y, 0);
        glVertex3f(pontotres.x, pontotres.y, 0);
        glVertex3f(pontoquatro.x, pontoquatro.y, 0);
    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);
    glPopMatrix();

    glPushMatrix();
    glBegin(GL_QUADS);
        glVertex3f(pontoum.x, pontoum.y, -0.5);
        glVertex3f(pontodois.x, pontodois.y, -0.5);
        glVertex3f(pontotres.x, pontotres.y, -0.5);
        glVertex3f(pontoquatro.x, pontoquatro.y, -0.5);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glBegin(GL_QUADS);
        glVertex3f(0.25, 0.25, 0);
        glVertex3f(0.25, 0.35, 0);
        glVertex3f(0.25, 0.35, -0.5);
        glVertex3f(0.25, 0.25, -0.5);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glBegin(GL_QUADS);
        glVertex3f(0.5, 0.25, 0);
        glVertex3f(0.5, 0.35, 0);
        glVertex3f(0.5, 0.35, -0.5);
        glVertex3f(0.5, 0.25, -0.5);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glBegin(GL_QUADS);
        glVertex3f(0.25, 0.25, 0);
        glVertex3f(0.25, 0.25, -0.5);
        glVertex3f(0.5, 0.25, -0.5);
        glVertex3f(0.5, 0.25, 0);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glBegin(GL_QUADS);
        glVertex3f(0.25, 0.35, 0);
        glVertex3f(0.25, 0.35, -0.5);
        glVertex3f(0.5, 0.35, -0.5);
        glVertex3f(0.5, 0.35, 0);
    glEnd();
    glPopMatrix();

}
