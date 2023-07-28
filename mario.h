
#ifndef MARIO_H
#define MARIO_H
#include <glm/glm.hpp>



class Mario{
private:

    float marioposicaox;
    float marioposicaoy;
    float marioaltura;
    float mariolargura;


public:
    Mario();
    void desenha(float x, float y);
};

#endif // MARIO_H
