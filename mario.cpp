//CLASSE SEM USO, POIS MIGREI A FUNÇÃO DE DESENHAR O MARIO PARA MAIN, POIS NÃO CONSEGUIR UTILIZAR TEXTURA NAS CLASSES :-(.
//PORÉM ELA AINDA DESENHAR UM POLIGONO E FAZ O MESMO SE MOVER NOS EIXOS X E Y SÓ QUE SEM TEXTURA.

#include "mario.h"
#include <cmath>
#include <GL/gl.h>
#include <iostream>

Mario::Mario(){

}

//Método que desenha o poligono que sera o personagem Mario, os parametros x e y são referentes os valores de posição que o mario ira ter, e irão mudar conforme o evento de teclado.
void Mario::desenha(float x, float y){

    float marioposicaox = x;
    float marioposicaoy = y;
    float marioaltura = 0.1; //altura que o mario vai ter.
    float mariolargura = 0.1; // sua largura.

    float posicaox = x + mariolargura; //variavel que sera usado para desenhar alguns pontos do "mario"
    float posicaoy = y + marioaltura;  //variavel que sera usado para desenhar alguns pontos do "mario"

    glPushMatrix();
    glColor3f(1, 0.0, 0.0);
    glBegin(GL_QUADS);
        glVertex3f(marioposicaox  , marioposicaoy, -0.2 );
        glVertex3f(posicaox, marioposicaoy, -0.2 );
        glVertex3f(posicaox, posicaoy, -0.2 );
        glVertex3f(marioposicaox, posicaoy, -0.2 );
    glEnd();

    glBegin(GL_QUADS);
        glVertex3f(marioposicaox, marioposicaoy, -0.25 );
        glVertex3f(posicaox, marioposicaoy, -0.25 );
        glVertex3f(posicaox, posicaoy, -0.25 );
        glVertex3f(marioposicaox, posicaoy, -0.25 );
    glEnd();


    glBegin(GL_QUADS);
        glVertex3f(marioposicaox, marioposicaoy, -0.2 );
        glVertex3f(marioposicaox, posicaoy, -0.2 );
        glVertex3f(marioposicaox, posicaoy, -0.25 );
        glVertex3f(marioposicaox, marioposicaoy, -0.25 );
    glEnd();

    glBegin(GL_QUADS);
        glVertex3f(posicaox, marioposicaoy, -0.2 );
        glVertex3f(posicaox, posicaoy, -0.2 );
        glVertex3f(posicaox, posicaoy, -0.25 );
        glVertex3f(posicaox, marioposicaoy, -0.25 );
    glEnd();

    glBegin(GL_QUADS);
        glVertex3f(marioposicaox, posicaoy, -0.2 );
        glVertex3f(posicaox, posicaoy, -0.2 );
        glVertex3f(posicaox, posicaoy, -0.25 );
        glVertex3f(posicaox, posicaoy, -0.25 );
    glEnd();

    glBegin(GL_QUADS);
        glVertex3f(marioposicaox, marioposicaoy, -0.2 );
        glVertex3f(posicaox, marioposicaoy, -0.2 );
        glVertex3f(posicaox, marioposicaoy, -0.25 );
        glVertex3f(posicaox, marioposicaoy, -0.25 );
    glEnd();

    glPopMatrix();

}
