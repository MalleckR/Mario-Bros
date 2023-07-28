#include "inimigos.h"
#include <GL/gl.h>
#include "fonteluz.h"

Inimigos::Inimigos(glm::vec3 posicao, glm::vec3 faceatras, int direcao){

    this->posicao = posicao;        //Coordenadas que serão usadas para desenhar os planos da frente dos poligonos.
    this->faceatras = faceatras;    //São as coordenadas dos pontos que ficam mais atras do poligonos, sera usado para desenhar os planos de fundo.
    this->direcao = direcao;

}

//Metodo que irá modificar a posição dos inimigos em relação ao eixo Z, no caso DIREITA seria crescendo para o Z postivo e ESQUERDA diminuindo para o Z negativo.
void Inimigos::move(float distancia){

    if(direcao == DIREITA){                    //se o objeto se move para o z negativo...
        posicao.z += distancia;                //aumente sua coordenada z dos pontos mais proximo da camera.
        faceatras.z += distancia;              //aumente sua coordenada z dos pontos mais distante da camera.
        if(posicao.z > -0.1) direcao = ESQUERDA; //se sua coordenada z ultrapassar o limite máximo, mude sua direção para esquerda.
    }
    else{                                      //se o objeto se move pra esquerda...
        faceatras.z -= distancia;              //diminua sua coordenada z dos pontos distantes da camera.
        posicao.z -= distancia;                //diminua sua coordenada z dos pontos proximo da camera.
        if(posicao.z < -0.4) direcao = DIREITA; //se sua coordenada z ultrapassar o limite mínimo, mude sua direção para direita
    }

}

//Método que irá desenhar os inimigos, os valores passado pro parametros são o resultado do calculo da iluminação de cada ponto feito na main
void Inimigos::desenha(glm::vec3 corinimigo1, glm::vec3 corinimigo2, glm::vec3 corinimigo3, glm::vec3 corinimigo4, glm::vec3 corinimigo5, glm::vec3 corinimigo6){


    glPushMatrix();
    glBegin(GL_QUADS);
    glColor3f(corinimigo1.x, corinimigo1.y, corinimigo1.z); //Definição de cor ao ponto usando o calculo de iluminação passado por parametro no método, o mesmo vale para os demais pontos.
        glVertex3f(0.25  , 0.5, posicao.z  );
        glVertex3f(0.3, 0.5, posicao.z  );
        glVertex3f(0.3, 0.55, posicao.z);
        glVertex3f(0.25  , 0.55, posicao.z);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glBegin(GL_QUADS);
    glColor3f(corinimigo2.x, corinimigo2.y, corinimigo2.z);
        glVertex3f(0.25  , 0.5, faceatras.z  );
        glVertex3f(0.3, 0.5, faceatras.z  );
        glVertex3f(0.3, 0.55, faceatras.z);
        glVertex3f(0.25  , 0.55, faceatras.z);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glBegin(GL_QUADS);
    glColor3f(corinimigo3.x, corinimigo3.y, corinimigo3.z);
        glVertex3f(0.25, 0.5, posicao.z);
        glVertex3f(0.25, 0.55, posicao.z);
        glVertex3f(0.25, 0.55, faceatras.z);
        glVertex3f(0.25, 0.5, faceatras.z);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glBegin(GL_QUADS);
    glColor3f(corinimigo4.x, corinimigo4.y, corinimigo4.z);
        glVertex3f(0.3, 0.5, posicao.z);
        glVertex3f(0.3, 0.55, posicao.z);
        glVertex3f(0.3, 0.55, faceatras.z);
        glVertex3f(0.3, 0.5, faceatras.z);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glBegin(GL_QUADS);
    glColor3f(corinimigo5.x, corinimigo5.y, corinimigo5.z);
        glVertex3f(0.25, 0.55, posicao.z);
        glVertex3f(0.3, 0.55, posicao.z);
        glVertex3f(0.3, 0.55, faceatras.z);
        glVertex3f(0.25, 0.55, faceatras.z);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glBegin(GL_QUADS);
    glColor3f(corinimigo6.x, corinimigo6.y, corinimigo6.z);
        glVertex3f(0.25, 0.5, posicao.z);
        glVertex3f(0.3, 0.5, posicao.z);
        glVertex3f(0.3, 0.5, faceatras.z);
        glVertex3f(0.25, 0.5, faceatras.z);
    glEnd();
    glPopMatrix();
}



