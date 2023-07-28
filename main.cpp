/*
 *      UNIVERSIDADE FEDERAL DO CEARÁ - CAMPUS RUSSAS
 *      DISCIPLINA: COMPUTAÇÃO GRAFICA
 *      DOCENTE: RAFAEL IVO
 *      EQUIPE: MALLECK RAVYN LEITE DOS SANTOS - 516373
 *              JOÃO PEREIRA DE SOUSA NETO - 403810
 *
 *      TEMA: MARIO BROS


*/
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#include <GL/glut.h>
#include <glm/glm.hpp>
#include <GL/glext.h>
#include <cmath>
#include <vector>
#include <glm/ext.hpp>
#include <iostream>
#include "mario.h"
#include "inimigos.h"
#include "plataforma.h"
#include <unistd.h>
#include "fonteluz.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

using namespace std;

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//Informa o caminho onde estara o arquivo que sera usado para textura.

#define TEX_MARIOFRENTE_FILE "C:/Users/malle/OneDrive/Documentos/computacaografica/MarioBros/MarioBros/texturamariobros/mariofrente.png"
#define TEX_MARIOPERFIL_FILE "C:/Users/malle/OneDrive/Documentos/computacaografica/MarioBros/MarioBros/texturamariobros/marioperfil.png"
#define TEX_GRAMA_FILE "C:/Users/malle/OneDrive/Documentos/computacaografica/MarioBros/MarioBros/texturamariobros/grama.jpg"
#define TEX_TERRA_FILE "C:/Users/malle/OneDrive/Documentos/computacaografica/MarioBros/MarioBros/texturamariobros/terra.jpg"
#define TEX_TERRENO_FILE "C:/Users/malle/OneDrive/Documentos/computacaografica/MarioBros/MarioBros/texturamariobros/terreno.jpg"
#define TEX_MARIOCIMA_FILE "C:/Users/malle/OneDrive/Documentos/computacaografica/MarioBros/MarioBros/texturamariobros/mariocima.jpg"

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//Variaveis que serão usadas para o uso da textura.

unsigned int texMariofrenteid;      //textura que sera usada para mostrar o mario visto de frente.
unsigned int texMarioperfilid;      //textura que sera usada para mostrar o mario de perfil ou de lado.
unsigned int texMariocima;          //textura que sera a visão do mario visto de cima.
unsigned int texGramaid;            //textura que sera usado na face de cima da plataforma que simular um gramado.
unsigned int texTerraid;            //textura das faces de baixo das plataformas que simular aspecto de terra.
unsigned int texTerrenoid;          //textura das faces de lado das plataformas.

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//Variaveis com finalidades diferentes

float frameRate = 60;               //Utlizado pela função time.
int larguraJanela, alturaJanela;    //ultilizados pela função alterajanela.
float aspectRatio;                  //ultilizado pela função alterajanela

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//Variaveis que receberam diferentes valores ao longo da função evento teclado.

float posx = -0.9;              //variavel referente a valores do eixo X.
float posy = -0.95;             //variavel referente a valores do eixo Y.
float posvelocidade = 0.0;      //variavel referente a velocidade so mario.
bool jumping = false;           //variavel que sera utilizada para fazer o mario pular somente quando presionado a respectivar teclar.
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// Variaveis relacionadas a camera, que vai variando seus valores confome o evento de teclado.

float camerax = 0.5; //eixo X da camera.
float cameray = 0.5; //eixo Y da camera.
float cameraz = 2;   //eixo Z da camera.

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//variveis relacionadas a iluminação e o ponto de luz.

float luzy = 1; //variavel que será usado para reposiciona o ponto de luz variando no eixo Y.

//as variaveis de face1ilu até face9ilu assume os valores que serão usados para definir os valores dos parametros de : ambiente, difusa e especular da iluminação de cada face das plataformas.
//esses valores irão mudando e consequente mudando a cor das faces das plataformas conforme o reposicionamento da luz, pois quando o ponto de luz se afasta, os valores ambiente, difusa e especular
//cair tornando com aparencia mais escura e quando a luz se aproxima das faces seus valores aumentam tornando mais brilhosos, esse evento e desecadeado com evento de teclado do ponto de luz.
float face1ilu = 0.6;
float face2ilu = 0.2;
float face3ilu = 0.1;
float face4ilu = 0.8;
float face5ilu = 0.4;
float face6ilu = 0.3;
float face7ilu = 1;
float face8ilu = 0.6;
float face9ilu = 0.5;

//as variaveis face1iluM até face9iluM assume os valores que serão usados para definir os valores dos parametros de : ambiente, difusa e especular da iluminação de cada face do Mario.
//o comportamento de ambas se da mesma forma que as variaveis usadas para as pltaformas.
float face1iluM = 0.6;
float face2iluM = 0.2;
float face3iluM = 0.1;
float face4iluM = 0.8;
float face5iluM = 0.4;
float face6iluM = 0.3;
float face7iluM = 1;
float face8iluM = 0.6;
float face9iluM = 0.5;

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//instâncias em uso.

FonteLuz luz; //instância que será nosso ponto de luz.

//instâncias que serão nossos inimigos onde por paramentro estou passando os pontos que serão usados para desenhar na tela, e também o parametro de direção para movimentação.
Inimigos inimigo1(glm::vec3(0,0,-0.2), glm::vec3(0,0,-0.3), DIREITA);
Inimigos inimigo2(glm::vec3(0,0,-0.2), glm::vec3(0,0,-0.3), DIREITA);
Inimigos inimigo3(glm::vec3(0,0,-0.2), glm::vec3(0,0,-0.3), DIREITA);
Inimigos inimigo4(glm::vec3(0,0,-0.2), glm::vec3(0,0,-0.3), DIREITA);

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//Função que ira atualizar o Mario na tela após o pressionar do teclado

void atualizarmario(float deltaTime) {

    // Atualiza a posição vertical do quadrado
    if(jumping){    //condição que vai garatir que a animação de pulo só aconteça quando pressionado a teclar

        posy += posvelocidade * deltaTime;

        // Simula a gravidade
        posvelocidade -= 6.8f * deltaTime;

        // Os seguinte if e else if são condição de parada do mario nas plataformas, com base em sua posição dependo em qual plataforma ele esteja sua condição de parada após pulo muda.
        if (posy <= -0.95f && posx <= -0.1) {
            posy = -0.95f;
            posvelocidade = 2.0f;
            jumping = false;

        }else if(posy <= -0.95f && posx <= 0 && posx >= -0.2){ //espaço para pular
            posy = -0.95f;
            jumping = false;

        }else if(posy <= -0.95f && posx >= 0.2){
            posy = -0.95f;
            posvelocidade = 2.0f;
            jumping = false;

        }else if(posy <= -0.3 && posy >= -0.31 && posx <= -0.2){
            posy = -0.35f;
            posvelocidade = 2.0f;
            jumping = false;

        }else if(posy <= -0.3 && posy >= -0.31 && posx >= 0.2 && posx <= 0.4){//espaço para pular
            posy = -0.35f;
            posvelocidade = 3.0f;
            jumping = false;

        }else if(posy <= -0.3 && posy >= -0.31 && posx >= 0.1){
            posy = -0.35f;
            posvelocidade = 2.0f;
            jumping = false;

        }else if(posy <= 0.26 && posy >= 0.15 && posx <= 0.1){
            posy = 0.26f;
            posvelocidade = 2.0f;
            jumping = false;

        }else if(posy <= 0.26 && posy >= 0.15 && posx >= 0.3){
            posy = 0.26f;
            posvelocidade = 2.0f;
            jumping = false;
        }

    }
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//Função qua ativa a função pula do Mario

void pularmario() {


    if(!jumping){ //Verificar se a variavel possui false.

        jumping = true; //faz a variavel receber true para ativar a função atualizarmario.

        // Verifica se o quadrado está no chão antes de pular
        if (posy <= -0.9f){

            if(posy <= -0.95f && posx <= 0 && posx >= -0.2){ //espaço para pular

                posvelocidade = 3.0f;

            }else if(posy <= -0.3 && posy >= -0.31 && posx >= 0.1 && posx <= 0.3){//espaço para pular

                posvelocidade = 3.0f;

            }else{
                posvelocidade = 1.5f;
            }

        }
    }
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//Função que faz o mario andar no eixo X positivo.

void moverParaFrentemario() {
    if (posx < 1.0f)    //Tratar uma simples colisão para fazer o Mario não ultrapassar o parametro.
        posx += 0.05f;
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//Função que faz o mario andar no eixo X negativo.

void moverParaTrasmario() {
    if (posx > -1.0f)   //Tratar uma simples colisão para fazer o Mario não ultrapassar o parametro.
        posx -= 0.05f;
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//Função que ira controlar todos os movimentos dos poligonos.

void tecladoSpecial(int key, int x, int y){

    switch(key){

    case GLUT_KEY_LEFT: moverParaTrasmario(); break;        //SETA ESQUERDA: Ira fazer o mario andar para o eixo X negativo.

    case GLUT_KEY_RIGHT: moverParaFrentemario(); break;     //SETA DIREITA: Ira fazer o mario andar para o eixo X positivo.

    case GLUT_KEY_UP: pularmario(); break;                  //SETA CIMA: Ira fazer o mario pular.

    case GLUT_KEY_F1:    posx = -0.9; posy = -0.95; break;  //TECLA F1: Faz os valores do X e do Y do Mario voltarem para a posição inicial.

    case GLUT_KEY_F2:    camerax += 0.05; break;            //TECLA F2: Ira fazer a camera andar para o eixo X positivo.

    case GLUT_KEY_F3:    camerax -= 0.05; break;            //TECLA F3: Ira fazer a camera andar para o eixo X negativo.

    case GLUT_KEY_F4:    cameray += 0.05; break;            //TECLA F4: Ira fazer a camera andar para o eixo Y positivo.

    case GLUT_KEY_F5:    cameray -= 0.05; break;            //TECLA F5: Ira fazer a camera andar para o eixo Y negativo.

    case GLUT_KEY_F6:    cameraz -= 0.05; break;            //TECLA F6: Ira fazer a camera andar para o eixo Z negativo.

    case GLUT_KEY_F7:    cameraz += 0.05; break;            //TECLA F7: Ira fazer a camera andar para o eixo Z positivo.

    case GLUT_KEY_F8:                                       //TECLA F8: Ira fazer o ponto de luz andar para o eixo Y positivo, e decair os valores de iluminação dos poligonos.

        if(luzy <= 1.5){

            face1ilu -= 0.05;
            face2ilu -= 0.05;
            face3ilu -= 0.05;
            face4ilu -= 0.05;
            face5ilu -= 0.05;
            face6ilu -= 0.05;
            face7ilu -= 0.05;
            face8ilu -= 0.05;
            face9ilu -= 0.05;

            luzy += 0.05;
            luz.setLuzPos(glm::vec3(0.5, luzy, -0.3));

        }
        break;

    case GLUT_KEY_F9:                                   //TECLA F9: Ira fazer o ponto de luz andar para o eixo Y negativo, e acrencentar aos valores de iluminação dos poligonos.

        if(luzy >= 0){

            face1ilu += 0.05;
            face2ilu += 0.05;
            face3ilu += 0.05;
            face4ilu += 0.05;
            face5ilu += 0.05;
            face6ilu += 0.05;
            face7ilu += 0.05;
            face8ilu += 0.05;
            face9ilu += 0.05;

            luzy -= 0.05;
            luz.setLuzPos(glm::vec3(0.5, luzy, -0.3));
        }
        break;
    }

    glutPostRedisplay();
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//Função de carregamento de textura.

unsigned int carregaTextura(char fileName[]){
    unsigned int texId;
    int largura, altura, nCanais;
    stbi_set_flip_vertically_on_load(true);
    unsigned char *imagem = stbi_load(fileName, &largura, &altura, &nCanais, 0); //qtd de pixels na largura e altura preenchidas automaticamente
    if(imagem == NULL) //verificação se o carregamento da imagem ocorreu com sucesso
        cout << "Erro, Imagem não carregada" << endl;
            else
            cout << "Imagem carregada com sucesso" << endl;

    glEnable(GL_TEXTURE_2D);             //habilitando o uso de texturas
    glGenTextures(1, &texId);            //gerando um objeto textura na máquina OpenGL
    glBindTexture(GL_TEXTURE_2D, texId); //ativando o objeto textura recém criado

    //parâmetros da textura caso coordenadas além do intervalo [0,1] seja utilizado
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); //repetição espelhada no eixo S
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); //repetição espelhada no eixo T

    //parâmetros da textura para filtragem quando tamanho de pixel e texel sejam diferentes (interpolação linear em ambos os casos)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); //magnificação - quando um texel cobre vários pixels
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //minificação - quando muitos texels cabem em um único pixel

    //parâmetros da textura para indicar se a textura deve-se combinar ou substituir a atual cor do objeto
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE); //GL_REPLACE = substitui, GL_COMBINE = combina (ou multiplica)

    //envio dos dados da textura para o OpenGL
    glTexImage2D(GL_TEXTURE_2D,
                 0,
                 GL_RGB,
                 largura,          //largura da textura
                 altura,           //altura da textura (carregadas automaticamente pela função da biblioteca)
                 0,
                 GL_RGB,           //formato da cor da textura
                 GL_UNSIGNED_BYTE, //tipos de dados de cada texel da textura
                 imagem);          //ponteiro para os dados da textura

    glBindTexture(GL_TEXTURE_2D, 0); //desativando o objeto textura criado (ativa apenas quando for usar em algum objeto)

    stbi_image_free(imagem); //memória RAM pode ser liberada pois a imagem foi enviada ao OpenGL (memória gráfica)

    return texId; //retornando o identificador da textura (sem ele não há como acessar a textura carregada)
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void inicio(){
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glEnable(GL_DEPTH_TEST);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);

    glEnable(GL_LINE_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT, GL_LINEAR);

    glPointSize(10.0);
    glLineWidth(2.0);

    char buffer[FILENAME_MAX];
    if (getcwd(buffer, sizeof(buffer)) != NULL) {
        std::cout << "Diretório corrente: " << buffer << std::endl;
    } else {
        std::cerr << "Erro ao obter o diretório corrente." << std::endl;
    }

    //Carregando os objetos textura para seus respectivos id's.
    texGramaid =        carregaTextura(TEX_GRAMA_FILE);
    texMariofrenteid =  carregaTextura(TEX_MARIOFRENTE_FILE);
    texMarioperfilid =  carregaTextura(TEX_MARIOPERFIL_FILE);
    texTerraid =        carregaTextura(TEX_TERRA_FILE);
    texTerrenoid =      carregaTextura(TEX_TERRENO_FILE);
    texMariocima =      carregaTextura(TEX_MARIOCIMA_FILE);
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void alteraJanela(int largura, int altura){
    larguraJanela = largura;
    alturaJanela  = altura;
    aspectRatio   = (float)larguraJanela/alturaJanela;
    glutPostRedisplay();
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void timer(int v){
    glutTimerFunc(1000.0/frameRate, timer, 0);

    //Chamada da função atualizarmario para acontecer a animação de pulo utilizando o framerate.
    atualizarmario(0.01f);

    //Chamando o metodo de movimentação dos inimigos passando o framerate.
    inimigo1.move(0.01);
    inimigo2.move(0.03);
    inimigo3.move(0.05);
    inimigo4.move(0.04);

    glutPostRedisplay();
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//Função que ira desenhar os inimigos utlizando seu respectivo metodo.

void allInimigos(){

    //Essas variaveis são respectivamente as faces de cada inimigo ou seja sua cor ira mudar confome sua face e sua normal.
    glm::vec3 inimiilumin1;
    glm::vec3 inimiilumin2;
    glm::vec3 inimiilumin3;
    glm::vec3 inimiilumin4;
    glm::vec3 inimiilumin5;
    glm::vec3 inimiilumin6;
    inimiilumin1 = luz.iluminacao(glm::vec3(0.37, 0.35, -0.25), glm::vec3(camerax, cameray, cameraz), glm::vec3(face2ilu, face2ilu, face2ilu), glm::vec3(0.8,0.8,0.8), glm::vec3(0.8,0.8,0.8), 10.0f, glm::vec3(0,1,0));
    inimiilumin2 = luz.iluminacao(glm::vec3(0.37, 0.35, -0.25), glm::vec3(camerax, cameray, cameraz), glm::vec3(face3ilu, face3ilu, face3ilu), glm::vec3(0.8,0.8,0.8), glm::vec3(0.8,0.8,0.8), 10.0f, glm::vec3(0,1,0));
    inimiilumin3 = luz.iluminacao(glm::vec3(0.37, 0.35, -0.25), glm::vec3(camerax, cameray, cameraz), glm::vec3(face4ilu, face4ilu, face4ilu), glm::vec3(0.8,0.8,0.8), glm::vec3(0.8,0.8,0.8), 10.0f, glm::vec3(0,1,0));
    inimiilumin4 = luz.iluminacao(glm::vec3(0.37, 0.35, -0.25), glm::vec3(camerax, cameray, cameraz), glm::vec3(face5ilu, face5ilu, face5ilu), glm::vec3(0.8,0.8,0.8), glm::vec3(0.8,0.8,0.8), 10.0f, glm::vec3(0,1,0));
    inimiilumin5 = luz.iluminacao(glm::vec3(0.37, 0.35, -0.25), glm::vec3(camerax, cameray, cameraz), glm::vec3(face1ilu, face1ilu, face1ilu), glm::vec3(0.8,0.8,0.8), glm::vec3(0.8,0.8,0.8), 10.0f, glm::vec3(0,1,0));
    inimiilumin6 = luz.iluminacao(glm::vec3(0.37, 0.35, -0.25), glm::vec3(camerax, cameray, cameraz), glm::vec3(face6ilu, face6ilu, face6ilu), glm::vec3(0.8,0.8,0.8), glm::vec3(0.8,0.8,0.8), 10.0f, glm::vec3(0,1,0));

    // Inimigo 1 esquerda baixo
    glPushMatrix();
    glTranslatef(-1.05,-0.82,0);   
    inimigo1.desenha(inimiilumin1, inimiilumin2, inimiilumin3, inimiilumin4, inimiilumin5, inimiilumin6);
    glPopMatrix();

    // Inimigo 2 esquerda cima
    glPushMatrix();
    glTranslatef(-0.65,-0.22,0);
    inimigo2.desenha(inimiilumin1, inimiilumin2, inimiilumin3, inimiilumin4, inimiilumin5, inimiilumin6);
    glPopMatrix();

    // Inimigo 3 direita baixo
    glPushMatrix();
    glTranslatef(0.2,-0.82,0);
    inimigo3.desenha(inimiilumin1, inimiilumin2, inimiilumin3, inimiilumin4, inimiilumin5, inimiilumin6);
    glPopMatrix();

    // Inimigo 4 Direita cima
    glPushMatrix();
    glTranslatef(0.45,-0.22,0);
    inimigo4.desenha(inimiilumin1, inimiilumin2, inimiilumin3, inimiilumin4, inimiilumin5, inimiilumin6);
    glPopMatrix();
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//Função que ira desenhar as plataformas com suas respectivas texturas.

void texturaplataforma(glm::vec3 face1, glm::vec3 face2, glm::vec3 face3, glm::vec3 face4, glm::vec3 face5, glm::vec3 face6){

    glm::vec3 corIluminada1; // variavel que ser usado para preencher os valores RGB da função glColor.

    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, texGramaid);   //Habilita o uso da textura.
    glBegin(GL_QUADS);
        corIluminada1 = luz.iluminacao(glm::vec3(0.37, 0.35, -0.25), glm::vec3(camerax, cameray, cameraz), face1, glm::vec3(0.8,0.8,0.8), glm::vec3(0.8,0.8,0.8), 10.0f, glm::vec3(0,1,0)); // Aqui o calculo da iluminação será armazenado na variavel.
        glColor3f(corIluminada1.x, corIluminada1.y, corIluminada1.z);   //utilizando a cor calculadar para uma face do poligono plataforma.
        glTexCoord2f(0,0);  glVertex3f(0.25, 0.35, 0);
        glTexCoord2f(5,0);  glVertex3f(0.25, 0.35, -0.5);
        glTexCoord2f(5,5);  glVertex3f(0.5, 0.35, -0.5);
        glTexCoord2f(0,5);  glVertex3f(0.5, 0.35, 0);
    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);    //Desabilita o uso da textura.
    glPopMatrix();

    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, texTerrenoid);
    glBegin(GL_QUADS);
        corIluminada1 = luz.iluminacao(glm::vec3(0.37, 0.35, -0.25), glm::vec3(camerax, cameray, cameraz), face2, glm::vec3(0.8,0.8,0.8), glm::vec3(0.8,0.8,0.8), 10.0f, glm::vec3(0,1,0));
        glColor3f(corIluminada1.x, corIluminada1.y, corIluminada1.z);
        glTexCoord2f(0,0);  glVertex3f(0.25,0.25,0);
        glTexCoord2f(0,1);  glVertex3f(0.25,0.35,0);
        glTexCoord2f(1,1);  glVertex3f(0.5,0.35,0);
        glTexCoord2f(1,0);  glVertex3f(0.5,0.25,0);
    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);
    glPopMatrix();

    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, texTerrenoid);
    glBegin(GL_QUADS);
        corIluminada1 = luz.iluminacao(glm::vec3(0.37, 0.35, -0.25), glm::vec3(camerax, cameray, cameraz), face3, glm::vec3(0.8,0.8,0.8), glm::vec3(0.8,0.8,0.8), 10.0f, glm::vec3(0,1,0));
        glColor3f(corIluminada1.x, corIluminada1.y, corIluminada1.z);
        glTexCoord2f(0,0);  glVertex3f(0.25, 0.25, -0.5);
        glTexCoord2f(0,1);  glVertex3f(0.25, 0.35, -0.5);
        glTexCoord2f(1,1);  glVertex3f(0.5, 0.35, -0.5);
        glTexCoord2f(1,0);  glVertex3f(0.5, 0.25, -0.5);
    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);
    glPopMatrix();

    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, texTerrenoid);
    glBegin(GL_QUADS);
    corIluminada1 = luz.iluminacao(glm::vec3(0.37, 0.35, -0.25), glm::vec3(camerax, cameray, cameraz), face4, glm::vec3(0.8,0.8,0.8), glm::vec3(0.8,0.8,0.8), 10.0f, glm::vec3(0,1,0));
    glColor3f(corIluminada1.x, corIluminada1.y, corIluminada1.z);
        glTexCoord2f(0,0);  glVertex3f(0.25, 0.25, 0);
        glTexCoord2f(0,1);  glVertex3f(0.25, 0.35, 0);
        glTexCoord2f(1,1);  glVertex3f(0.25, 0.35, -0.5);
        glTexCoord2f(1,0);  glVertex3f(0.25, 0.25, -0.5);
    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);
    glPopMatrix();

    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, texTerrenoid);
    glBegin(GL_QUADS);
        corIluminada1 = luz.iluminacao(glm::vec3(0.37, 0.35, -0.25), glm::vec3(camerax, cameray, cameraz), face5, glm::vec3(0.8,0.8,0.8), glm::vec3(0.8,0.8,0.8), 10.0f, glm::vec3(0,1,0));
        glColor3f(corIluminada1.x, corIluminada1.y, corIluminada1.z);
        glTexCoord2f(0,0);  glVertex3f(0.5, 0.25, 0);
        glTexCoord2f(0,1);  glVertex3f(0.5, 0.35, 0);
        glTexCoord2f(1,1);  glVertex3f(0.5, 0.35, -0.5);
        glTexCoord2f(1,0);  glVertex3f(0.5, 0.25, -0.5);
    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);
    glPopMatrix();

    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, texTerraid);
    glBegin(GL_QUADS);
        corIluminada1 = luz.iluminacao(glm::vec3(0.37, 0.35, -0.25), glm::vec3(camerax, cameray, cameraz), face6, glm::vec3(0.8,0.8,0.8), glm::vec3(0.8,0.8,0.8), 10.0f, glm::vec3(0,1,0));
        glColor3f(corIluminada1.x, corIluminada1.y, corIluminada1.z);
        glTexCoord2f(0,0);  glVertex3f(0.25, 0.25, 0);
        glTexCoord2f(3,0);  glVertex3f(0.25, 0.25, -0.5);
        glTexCoord2f(3,3);  glVertex3f(0.5, 0.25, -0.5);
        glTexCoord2f(0,3);  glVertex3f(0.5, 0.25, 0);
    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);
    glPopMatrix();


}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//Função onde faço a chamada de função para desenhar os poligonos e ajustar sua Escalar e Posição com translação.

void desenhaplataforma(){

    //glTranslaf estar sendo usado para reposicionar as plataformas em suas respectivos lugares pois sem essa função ambas as plataformas seriam desenhadas na mesma posição.
    //glScalef estar sendo utilizado para modificar o tamanho das plataformas pois ambas sem essa função teriam as mesmas dimesões.
    //glPushMatrix: Como estou aplicando tranformações diferentes para poligono preciso salvar a matriz de transformação original para que as mudanças feitas em um poligono afetam aos outros poligonos.
    //glPopMatrix: após as tranformações trago de volta a matriz original.

    glPushMatrix();
    glTranslatef(-0.01,-0.801,0);
    glScalef(5,1,1);
    glTranslatef(-0.5,-0.5,0);
    texturaplataforma(glm::vec3(face1ilu,face1ilu,face1ilu), glm::vec3(face2ilu,face2ilu,face2ilu), glm::vec3(face2ilu,face2ilu,face2ilu), glm::vec3(face2ilu,face2ilu,face2ilu), glm::vec3(face2ilu,face2ilu,face2ilu), glm::vec3(face3ilu,face3ilu,face3ilu));
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1,-0.801,0);
    glScalef(3,1,1);
    glTranslatef(-0.5,-0.5,0);
    texturaplataforma(glm::vec3(face1ilu,face1ilu,face1ilu), glm::vec3(face2ilu,face2ilu,face2ilu), glm::vec3(face2ilu,face2ilu,face2ilu), glm::vec3(face2ilu,face2ilu,face2ilu), glm::vec3(face2ilu,face2ilu,face2ilu), glm::vec3(face3ilu,face3ilu,face3ilu));
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.2,-0.201,0);
    glScalef(3.5,0.8,1);
    glTranslatef(-0.5,-0.5,0);
    texturaplataforma(glm::vec3(face4ilu,face4ilu,face4ilu), glm::vec3(face5ilu,face5ilu,face5ilu), glm::vec3(face5ilu,face5ilu,face5ilu), glm::vec3(face5ilu,face5ilu,face5ilu), glm::vec3(face5ilu,face5ilu,face5ilu), glm::vec3(face6ilu,face6ilu,face6ilu));
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1,-0.201,0);
    glScalef(3.5,0.8,1);
    glTranslatef(-0.5,-0.5,0);
    texturaplataforma(glm::vec3(face4ilu,face4ilu,face4ilu), glm::vec3(face5ilu,face5ilu,face5ilu), glm::vec3(face5ilu,face5ilu,face5ilu), glm::vec3(face5ilu,face5ilu,face5ilu), glm::vec3(face5ilu,face5ilu,face5ilu), glm::vec3(face6ilu,face6ilu,face6ilu));
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.1,0.401,0);
    glScalef(5,0.8,1);
    glTranslatef(-0.5,-0.5,0);
    texturaplataforma(glm::vec3(face7ilu,face7ilu,face7ilu), glm::vec3(face8ilu,face8ilu,face8ilu), glm::vec3(face8ilu,face8ilu,face8ilu), glm::vec3(face8ilu,face8ilu,face8ilu), glm::vec3(face8ilu,face8ilu,face8ilu), glm::vec3(face9ilu,face9ilu,face9ilu));
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1,0.401,0);
    glScalef(2.5,0.8,1);
    glTranslatef(-0.5,-0.5,0);
    texturaplataforma(glm::vec3(face7ilu,face7ilu,face7ilu), glm::vec3(face8ilu,face8ilu,face8ilu), glm::vec3(face8ilu,face8ilu,face8ilu), glm::vec3(face8ilu,face8ilu,face8ilu), glm::vec3(face8ilu,face8ilu,face8ilu), glm::vec3(face9ilu,face9ilu,face9ilu));
    glPopMatrix();
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//Função responsavel por desenhar o Mario com suas respectivas texturas.

void texturamario(glm::vec3 face1, glm::vec3 face2, glm::vec3 face3, glm::vec3 face4, glm::vec3 face5, glm::vec3 face6){

    //Variaveis representando os X e Y do Mario
    float marioposicaox = posx;     //Variavel representando o X inicial
    float marioposicaoy = posy;     //Variavel representado o Y inicial
    float marioaltura = 0.15;       //Altura que o mario deve ter.
    float mariolargura = 0.15;      //Largura que o mario deve ter.

    float posicaox = posx + mariolargura;   //Variavel que sera utlizado pra fazer o X final do Mario.
    float posicaoy = posy + marioaltura;    //Variavel que sera utlizado pra fazer o Y final do Mario.

    glm::vec3 corIluminada2;    //Variavel que sera utilizado como parametro na função glColor.

    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, texMarioperfilid); //Habilitar Textura.
    glBegin(GL_QUADS);
        corIluminada2 = luz.iluminacao(glm::vec3(0.37, 0.35, -0.25), glm::vec3(camerax, cameray, cameraz), face2, glm::vec3(0.8,0.8,0.8), glm::vec3(0.8,0.8,0.8), 10.0f, glm::vec3(0,1,0)); //Calcular a cor calculada.
        glColor3f(corIluminada2.x, corIluminada2.y, corIluminada2.z);
        glTexCoord2f(0,0); glVertex3f(marioposicaox  , marioposicaoy, -0.2 );
        glTexCoord2f(1,0); glVertex3f(posicaox, marioposicaoy, -0.2 );
        glTexCoord2f(1,1); glVertex3f(posicaox, posicaoy, -0.2 );
        glTexCoord2f(0,1); glVertex3f(marioposicaox, posicaoy, -0.2 );
    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);      //Desabilitar Textura.
    glPopMatrix();

    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, texMarioperfilid);
    glBegin(GL_QUADS);
        corIluminada2 = luz.iluminacao(glm::vec3(0.37, 0.35, -0.25), glm::vec3(camerax, cameray, cameraz), face3, glm::vec3(0.8,0.8,0.8), glm::vec3(0.8,0.8,0.8), 10.0f, glm::vec3(0,1,0));
        glColor3f(corIluminada2.x, corIluminada2.y, corIluminada2.z);
        glTexCoord2f(0,0); glVertex3f(marioposicaox, marioposicaoy, -0.3 );
        glTexCoord2f(1,0); glVertex3f(posicaox, marioposicaoy, -0.3 );
        glTexCoord2f(1,1); glVertex3f(posicaox, posicaoy, -0.3 );
        glTexCoord2f(0,1); glVertex3f(marioposicaox, posicaoy, -0.3 );
    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);
    glPopMatrix();

    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, texMariofrenteid);
    glBegin(GL_QUADS);
        corIluminada2 = luz.iluminacao(glm::vec3(0.37, 0.35, -0.25), glm::vec3(camerax, cameray, cameraz), face4, glm::vec3(0.8,0.8,0.8), glm::vec3(0.8,0.8,0.8), 10.0f, glm::vec3(0,1,0));
        glColor3f(corIluminada2.x, corIluminada2.y, corIluminada2.z);
        glTexCoord2f(0,0); glVertex3f(marioposicaox, marioposicaoy, -0.2 );
        glTexCoord2f(0,1); glVertex3f(marioposicaox, posicaoy, -0.2 );
        glTexCoord2f(1,1); glVertex3f(marioposicaox, posicaoy, -0.3 );
        glTexCoord2f(1,0); glVertex3f(marioposicaox, marioposicaoy, -0.3 );
    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);
    glPopMatrix();

    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, texMariofrenteid);
    glBegin(GL_QUADS);
        corIluminada2 = luz.iluminacao(glm::vec3(0.37, 0.35, -0.25), glm::vec3(camerax, cameray, cameraz), face5, glm::vec3(0.8,0.8,0.8), glm::vec3(0.8,0.8,0.8), 10.0f, glm::vec3(0,1,0));
        glColor3f(corIluminada2.x, corIluminada2.y, corIluminada2.z);
        glTexCoord2f(0,0); glVertex3f(posicaox, marioposicaoy, -0.2 );
        glTexCoord2f(0,1); glVertex3f(posicaox, posicaoy, -0.2 );
        glTexCoord2f(1,1); glVertex3f(posicaox, posicaoy, -0.3 );
        glTexCoord2f(1,0); glVertex3f(posicaox, marioposicaoy, -0.3 );
    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);
    glPopMatrix();

    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, texMariocima);
    glBegin(GL_QUADS);
        corIluminada2 = luz.iluminacao(glm::vec3(0.37, 0.35, -0.25), glm::vec3(camerax, cameray, cameraz), face1, glm::vec3(0.8,0.8,0.8), glm::vec3(0.8,0.8,0.8), 10.0f, glm::vec3(0,1,0));
        glColor3f(corIluminada2.x, corIluminada2.y, corIluminada2.z);
        glTexCoord2f(1,0); glVertex3f(marioposicaox, posicaoy, -0.2 );
        glTexCoord2f(1,1); glVertex3f(posicaox, posicaoy, -0.2 );
        glTexCoord2f(0,1); glVertex3f(posicaox, posicaoy, -0.3 );
        glTexCoord2f(0,0); glVertex3f(marioposicaox, posicaoy, -0.3 );
    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);
    glPopMatrix();

    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, texMariocima);
    glBegin(GL_QUADS);
        corIluminada2 = luz.iluminacao(glm::vec3(0.37, 0.35, -0.25), glm::vec3(camerax, cameray, cameraz), face6, glm::vec3(0.8,0.8,0.8), glm::vec3(0.8,0.8,0.8), 10.0f, glm::vec3(0,1,0));
        glColor3f(corIluminada2.x, corIluminada2.y, corIluminada2.z);
        glTexCoord2f(1,0); glVertex3f(marioposicaox, marioposicaoy, -0.2 );
        glTexCoord2f(1,1); glVertex3f(posicaox, marioposicaoy, -0.2 );
        glTexCoord2f(0,1); glVertex3f(posicaox, marioposicaoy, -0.3 );
        glTexCoord2f(0,0); glVertex3f(marioposicaox, marioposicaoy, -0.3 );
    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);
    glPopMatrix();
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//Função que tratarar as colisões que acontecem com o poligono mario quando suas coordenadas acabam atravessando as coordenadas de outro poligono.
//Cada if e Else é uma condição para que o mario seja desenhando somente em ambas suas condiçoes.
//ou seja dependendo onde o mario vai passeando ele sera desenhando em um if ou else diferente, pois nessas areas existem comportamento especificos.

void colisaomario(){

    //Variaveis que serão apenas utlizados para comparação.
    float cabeca = posy + 0.1;
    float pe = posy;

    if(cabeca <= 1.05){
        texturamario(glm::vec3(face1iluM,face1iluM,face1iluM), glm::vec3(face2iluM,face2iluM,face2iluM), glm::vec3(face2iluM,face2iluM,face2iluM), glm::vec3(face2iluM,face2iluM,face2iluM), glm::vec3(face2iluM,face2iluM,face2iluM), glm::vec3(face3iluM,face3iluM,face3iluM));

    }else{
        posy -= 0.05;
        texturamario(glm::vec3(face1iluM,face1iluM,face1iluM), glm::vec3(face2iluM,face2iluM,face2iluM), glm::vec3(face2iluM,face2iluM,face2iluM), glm::vec3(face2iluM,face2iluM,face2iluM), glm::vec3(face2iluM,face2iluM,face2iluM), glm::vec3(face3iluM,face3iluM,face3iluM));

    }

    if(pe >= -0.95){
        texturamario(glm::vec3(face1iluM,face1iluM,face1iluM), glm::vec3(face2iluM,face2iluM,face2iluM), glm::vec3(face2iluM,face2iluM,face2iluM), glm::vec3(face2iluM,face2iluM,face2iluM), glm::vec3(face2iluM,face2iluM,face2iluM), glm::vec3(face3iluM,face3iluM,face3iluM));

    }else{
        posy += 0.05;
        texturamario(glm::vec3(face1iluM,face1iluM,face1iluM), glm::vec3(face2iluM,face2iluM,face2iluM), glm::vec3(face2iluM,face2iluM,face2iluM), glm::vec3(face2iluM,face2iluM,face2iluM), glm::vec3(face2iluM,face2iluM,face2iluM), glm::vec3(face3iluM,face3iluM,face3iluM));

    }

    if(posx >= -1){
        texturamario(glm::vec3(face1iluM,face1iluM,face1iluM), glm::vec3(face2iluM,face2iluM,face2iluM), glm::vec3(face2iluM,face2iluM,face2iluM), glm::vec3(face2iluM,face2iluM,face2iluM), glm::vec3(face2iluM,face2iluM,face2iluM), glm::vec3(face3iluM,face3iluM,face3iluM));

    }else{
        posx += 0.05;
        texturamario(glm::vec3(face1iluM,face1iluM,face1iluM), glm::vec3(face2iluM,face2iluM,face2iluM), glm::vec3(face2iluM,face2iluM,face2iluM), glm::vec3(face2iluM,face2iluM,face2iluM), glm::vec3(face2iluM,face2iluM,face2iluM), glm::vec3(face3iluM,face3iluM,face3iluM));

    }

    if(posx < 0.95){
        texturamario(glm::vec3(face1iluM,face1iluM,face1iluM), glm::vec3(face2iluM,face2iluM,face2iluM), glm::vec3(face2iluM,face2iluM,face2iluM), glm::vec3(face2iluM,face2iluM,face2iluM), glm::vec3(face2iluM,face2iluM,face2iluM), glm::vec3(face3iluM,face3iluM,face3iluM));

    }else{
        posx -= 0.05;
        texturamario(glm::vec3(face1iluM,face1iluM,face1iluM), glm::vec3(face2iluM,face2iluM,face2iluM), glm::vec3(face2iluM,face2iluM,face2iluM), glm::vec3(face2iluM,face2iluM,face2iluM), glm::vec3(face2iluM,face2iluM,face2iluM), glm::vec3(face3iluM,face3iluM,face3iluM));        
    }


    if(pe >= 0.26 && posx <= 0.09){
        texturamario(glm::vec3(face1ilu,face1ilu,face1ilu), glm::vec3(face2ilu,face2ilu,face2ilu), glm::vec3(face2ilu,face2ilu,face2ilu), glm::vec3(face2ilu,face2ilu,face2ilu), glm::vec3(face2ilu,face2ilu,face2ilu), glm::vec3(face3ilu,face3ilu,face3ilu));


    }else if(pe <= 0.26 && pe >= 0.2 && posx <= 0.09){
        posy += 0.05;
        texturamario(glm::vec3(face1ilu,face1ilu,face1ilu), glm::vec3(face2ilu,face2ilu,face2ilu), glm::vec3(face2ilu,face2ilu,face2ilu), glm::vec3(face2ilu,face2ilu,face2ilu), glm::vec3(face2ilu,face2ilu,face2ilu), glm::vec3(face3ilu,face3ilu,face3ilu));


    }else if (pe >= 0.15 && pe <= 0.26 && posx <= 0.09){
        posy -= 0.05;
        texturamario(glm::vec3(face1ilu,face1ilu,face1ilu), glm::vec3(face2ilu,face2ilu,face2ilu), glm::vec3(face2ilu,face2ilu,face2ilu), glm::vec3(face2ilu,face2ilu,face2ilu), glm::vec3(face2ilu,face2ilu,face2ilu), glm::vec3(face3ilu,face3ilu,face3ilu));

    }

    if(pe >= 0.26 && posx >= 0.3){
        texturamario(glm::vec3(face1ilu,face1ilu,face1ilu), glm::vec3(face2ilu,face2ilu,face2ilu), glm::vec3(face2ilu,face2ilu,face2ilu), glm::vec3(face2ilu,face2ilu,face2ilu), glm::vec3(face2ilu,face2ilu,face2ilu), glm::vec3(face3ilu,face3ilu,face3ilu));


    }else if(pe <= 0.26 && pe >= 0.2 && posx >= 0.3){
        posy += 0.05;
        texturamario(glm::vec3(face1ilu,face1ilu,face1ilu), glm::vec3(face2ilu,face2ilu,face2ilu), glm::vec3(face2ilu,face2ilu,face2ilu), glm::vec3(face2ilu,face2ilu,face2ilu), glm::vec3(face2ilu,face2ilu,face2ilu), glm::vec3(face3ilu,face3ilu,face3ilu));


    }else if (pe >= 0.15 && pe <= 0.26 && posx >= 0.3){
        posy -= 0.05;
        texturamario(glm::vec3(face1ilu,face1ilu,face1ilu), glm::vec3(face2ilu,face2ilu,face2ilu), glm::vec3(face2ilu,face2ilu,face2ilu), glm::vec3(face2ilu,face2ilu,face2ilu), glm::vec3(face2ilu,face2ilu,face2ilu), glm::vec3(face3ilu,face3ilu,face3ilu));       
    }

    if(pe <= -0.45 && posx <= -0.2){
        texturamario(glm::vec3(face1ilu,face1ilu,face1ilu), glm::vec3(face2ilu,face2ilu,face2ilu), glm::vec3(face2ilu,face2ilu,face2ilu), glm::vec3(face2ilu,face2ilu,face2ilu), glm::vec3(face2ilu,face2ilu,face2ilu), glm::vec3(face3ilu,face3ilu,face3ilu));


    }else if(pe <= -0.3 && pe >= -0.4 && posx <= -0.2){
        posy += 0.05;
        texturamario(glm::vec3(face1ilu,face1ilu,face1ilu), glm::vec3(face2ilu,face2ilu,face2ilu), glm::vec3(face2ilu,face2ilu,face2ilu), glm::vec3(face2ilu,face2ilu,face2ilu), glm::vec3(face2ilu,face2ilu,face2ilu), glm::vec3(face3ilu,face3ilu,face3ilu));


    }else if (pe >= -0.45 && pe <= -0.4 && posx <= -0.2){
        posy -= 0.05;
        texturamario(glm::vec3(face1ilu,face1ilu,face1ilu), glm::vec3(face2ilu,face2ilu,face2ilu), glm::vec3(face2ilu,face2ilu,face2ilu), glm::vec3(face2ilu,face2ilu,face2ilu), glm::vec3(face2ilu,face2ilu,face2ilu), glm::vec3(face3ilu,face3ilu,face3ilu));
    }

    if(pe <= -0.45 && posx >= 0){
        texturamario(glm::vec3(face1ilu,face1ilu,face1ilu), glm::vec3(face2ilu,face2ilu,face2ilu), glm::vec3(face2ilu,face2ilu,face2ilu), glm::vec3(face2ilu,face2ilu,face2ilu), glm::vec3(face2ilu,face2ilu,face2ilu), glm::vec3(face3ilu,face3ilu,face3ilu));


    }else if(pe <= -0.3 && pe >= -0.4 && posx >= 0.04){
        posy += 0.05;
        texturamario(glm::vec3(face1ilu,face1ilu,face1ilu), glm::vec3(face2ilu,face2ilu,face2ilu), glm::vec3(face2ilu,face2ilu,face2ilu), glm::vec3(face2ilu,face2ilu,face2ilu), glm::vec3(face2ilu,face2ilu,face2ilu), glm::vec3(face3ilu,face3ilu,face3ilu));


    }else if (pe >= -0.45 && pe <= -0.4 && posx >= 0.04){
        posy -= 0.05;
        texturamario(glm::vec3(face1ilu,face1ilu,face1ilu), glm::vec3(face2ilu,face2ilu,face2ilu), glm::vec3(face2ilu,face2ilu,face2ilu), glm::vec3(face2ilu,face2ilu,face2ilu), glm::vec3(face2ilu,face2ilu,face2ilu), glm::vec3(face3ilu,face3ilu,face3ilu));

    }
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//Função que tratara a colisão que acontece quando as coordenadas do mario coencidam com as do inimigo.
//quando cada if mapeia a dertemina localização dos inimigos quando as coordenadas do mario se tornam valores que serão aceito na codição
//dos if o poligo Mario tera suas coordenadas modificas para da uma simulação de sumido, apertando a tecla F1 é possivel restabelecer os valores iniciais do Mario.

void colisaoinimigos(){

    //direita cima
    if(posx <= 0.75 && posx >= 0.63 && posy <= 0.35 && posy >= 0.26){

        posx = 1000;
        posy = 1000;
    }

    //esquerda cima
    if(posx <= -0.35 && posx >= -0.49 && posy <= 0.35 && posy >= 0.26){
        posx = 1000;
        posy = 1000;
    }

    //esquerda baixo
    if(posx >= -0.9 && posx <= -0.75 && posy >= -0.3 && posy <= -0.25){

        posx = 1000;
        posy = 1000;
    }
    //direita baixo
    if(posx >= 0.4 && posx <= 0.55 && posy >= -0.3 && posy <= -0.25){

        posx = 1000;
        posy = 1000;
    }


}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//Camera em Perspectiva.

void projecaoPerspectiva(){

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glm::mat4 matrizProjecao = glm::frustum(-1,1,
                                            -1,1,
                                            1,100);
    glMultMatrixf(glm::value_ptr(matrizProjecao));

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glm::mat4 matrizCamera = glm::lookAt(glm::vec3(camerax,cameray,cameraz),
                                         glm::vec3(0,0,0),
                                         glm::vec3(0,2,0));
    glMultMatrixf(glm::value_ptr(matrizCamera));


    colisaomario();

    desenhaplataforma();

    colisaoinimigos();

    allInimigos();

    luz.desenha();


}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//Camera em Paralela.

void projecaoParalela(){

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glm::mat4 matrizProjecao = glm::ortho(-1.5f,1.5f,   //left e right (limites na largura do volume de visualização)
                                          -1.5f,1.5f,   //bottom e top (limites na altura do volume de visualização)
                                          1.0f,100.0f); //near e far   (limites na profundidade do volume de visualização)
    glMultMatrixf(glm::value_ptr(matrizProjecao));

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glm::mat4 matrizCamera = glm::lookAt(glm::vec3(camerax,cameray,cameraz), //eye = posição da câmera
                                         glm::vec3(0,0,0),  //at  = para onde a câmera aponta
                                         glm::vec3(0,1,0)); //up  = para onde o topo da câmera aponta
    glMultMatrixf(glm::value_ptr(matrizCamera)); //criada a matriz usando GLM, deve-se enviá-la para OpenGL


    colisaomario();

    desenhaplataforma();

    colisaoinimigos();

    allInimigos();

    luz.desenha();

}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void desenha(){

    glClear(GL_COLOR_BUFFER_BIT);
    projecaoParalela();
    //projecaoPerspectiva();

    glutSwapBuffers();
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

int main(int argc, char** argv){
    glutInit(&argc,argv);
    //GLUT_DOUBLE;

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    //glutSetOption(GLUT_MULTISAMPLE, 8);

    glutInitDisplayMode(GLUT_MULTISAMPLE | GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowPosition(0,0);
    glutInitWindowSize(800,700);
    glutCreateWindow("MARIO BROS");

    inicio();

    glutDisplayFunc(desenha);
    glutReshapeFunc(alteraJanela);
    glutSpecialFunc(tecladoSpecial);
    glutTimerFunc(1000.0/60, timer, 0);

    glutMainLoop();
    return 0;
}
