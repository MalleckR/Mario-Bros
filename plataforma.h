
#ifndef PLATAFORMA_H
#define PLATAFORMA_H
#include <glm/glm.hpp>



class plataforma
{
private:
    glm::vec2 pontoum;
    glm::vec2 pontodois;
    glm::vec2 pontotres;
    glm::vec2 pontoquatro;


public:
    plataforma(glm::vec2 ponto1, glm::vec2 ponto2, glm::vec2 ponto3, glm::vec2 ponto4);
    void desenha();

};

#endif // PLATAFORMA_H
