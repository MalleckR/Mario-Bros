#ifndef FONTELUZ_H
#define FONTELUZ_H

#include <glm/glm.hpp>

class FonteLuz{
private:

    glm::vec3 luzPos  = glm::vec3(0.5,1,-0.3); //Valores referentes da posição do ponto de luz

    //propriedades de cor da fonte de luz
    glm::vec3 luzAmb  = glm::vec3(1,1,1);            //valor referente ao ambiente
    glm::vec3 luzDiff = glm::vec3(0.01,0.01,0.01);   //valor referente a difusa
    glm::vec3 luzSpec = glm::vec3(0.01,0.01,0.01);   //valor referente a especular

public:

    FonteLuz();
    glm::vec3 iluminacao(glm::vec3 P, glm::vec3 camPos, glm::vec3 matAmb, glm::vec3 matDiff, glm::vec3 matSpec, float matShine, glm::vec3 n);
    void desenha();

    const glm::vec3 &getLuzPos() const;
    const glm::vec3 &getLuzAmb() const;
    const glm::vec3 &getLuzDiff() const;
    const glm::vec3 &getLuzSpec() const;

    void setLuzPos(const glm::vec3 &newLuzPos);
    void setLuzAmb(const glm::vec3 &newLuzAmb);
    void setLuzDiff(const glm::vec3 &newLuzDiff);
    void setLuzSpec(const glm::vec3 &newLuzSpec);

};

#endif // FONTELUZ_H
