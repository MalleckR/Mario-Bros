#include "fonteluz.h"
#include <iostream>
#include <GL/gl.h>

FonteLuz::FonteLuz(){

}


//método que calcula a cor que um ponto irá possuir após ser iluminado pela fonte de luz usando Modelo de Iluminação de Phong
glm::vec3 FonteLuz::iluminacao(glm::vec3 P, glm::vec3 camPos, glm::vec3 matAmb, glm::vec3 matDiff, glm::vec3 matSpec, float matShine, glm::vec3 n){

    //Calculo da reflexão ambiente
    glm::vec3 amb = luzAmb * matAmb;

    //Calculo da reflexão difusa
    glm::vec3 l = glm::vec3(luzPos) - P;
    l = glm::normalize(l);
    n = glm::normalize(n);
    glm::vec3 dif = luzDiff * matDiff * glm::max(0.0f, glm::dot(l,n));

    //Calculo da reflexão especular
    glm::vec3 esp;
    glm::vec3 v = glm::vec3(camPos) - P;
    v = glm::normalize(v);
    glm::vec3 r = 2*glm::dot(n,l)*n - l;

    if(glm::dot(v,r) < 0){
        esp = glm::vec3(0,0,0);
    }else{
        esp = luzSpec * matSpec * (float)(pow(glm::max(0.0f, glm::dot(v,r)), matShine));
    }

    return amb + dif + esp; //retorno da cor após o calculo.
}

//método que desenha a fonte de luz na tela
void FonteLuz::desenha(){

    glPointSize(20);
    glColor3f(1,1,0);
    glBegin(GL_POINTS);
        glVertex3f(luzPos.x, luzPos.y, luzPos.z);
    glEnd();
}

//Get's
const glm::vec3 &FonteLuz::getLuzPos() const
{
    return luzPos;
}

const glm::vec3 &FonteLuz::getLuzAmb() const
{
    return luzAmb;
}

const glm::vec3 &FonteLuz::getLuzDiff() const
{
    return luzDiff;
}

const glm::vec3 &FonteLuz::getLuzSpec() const
{
    return luzSpec;
}

//Set's
void FonteLuz::setLuzPos(const glm::vec3 &newLuzPos)
{
    luzPos = newLuzPos;
}

void FonteLuz::setLuzAmb(const glm::vec3 &newLuzAmb)
{
    luzAmb = newLuzAmb;
}

void FonteLuz::setLuzDiff(const glm::vec3 &newLuzDiff)
{
    luzDiff = newLuzDiff;
}

void FonteLuz::setLuzSpec(const glm::vec3 &newLuzSpec)
{
    luzSpec = newLuzSpec;
}
