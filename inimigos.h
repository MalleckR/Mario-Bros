#ifndef INIMIGOS_H
#define INIMIGOS_H
#include <glm/glm.hpp>

enum{
    ESQUERDA = 1,
    DIREITA
};

class Inimigos{

private:
    glm::vec3 posicao;
    glm::vec3 faceatras;
    int direcao;
public:
    Inimigos(glm::vec3 posicao, glm::vec3 faceatras, int direcao);
    void desenha(glm::vec3 corinimigo1, glm::vec3 corinimigo2, glm::vec3 corinimigo3, glm::vec3 corinimigo4, glm::vec3 corinimigo5, glm::vec3 corinimigo6);
    void move(float distancia);

};

#endif // INIMIGOS_H

