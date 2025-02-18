#define GLM_FORCE_RADIANS
#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLWidget>
#include <QOpenGLShader>
#include <QOpenGLShaderProgram>
#include <QKeyEvent>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class MyGLWidget : public QOpenGLWidget, protected QOpenGLFunctions_3_3_Core
{
  Q_OBJECT

  public:
    MyGLWidget (QWidget *parent=0);
    ~MyGLWidget ();
    
  protected:
    // initializeGL - Aqui incluim les inicialitzacions del contexte grafic.
    virtual void initializeGL ();

    // paintGL - Mètode cridat cada cop que cal refrescar la finestra.
    // Tot el que es dibuixa es dibuixa aqui.
    virtual void paintGL ();
 
    // resize - Es cridat quan canvia la mida del widget
    virtual void resizeGL (int width, int height);  

    // keyPressEvent - Es cridat quan es prem una tecla
    virtual void keyPressEvent (QKeyEvent *event);


  private:

    
    void creaBuffersQuadrat();
    
    void carregaShaders();
    
    void modelTransformQuadrat();

    void modelTransformQuadratGir(glm::vec3 posicio, glm::vec3 escala, float angle);
    
    void pintaTanc();

    void pintaCanoTanc();

    void pintaRodesTanc();

    void pintaRodaIndividual(int pos);
    // program
    QOpenGLShaderProgram *program;
    // attribute locations
    GLuint vertexLoc;
    // uniform locations
    GLuint TGLoc;

    GLuint colorLoc;

    // VAOs
    GLuint VAOQuadrat;

    // viewport
    GLint ample, alt;    
    
    // colors
    glm::vec3 verd = glm::vec3(0.0,0.6,0.0);
    glm::vec3 negre = glm::vec3(0.0);    
    glm::vec3 gris = glm::vec3(0.5,0.5,0.5);

    //variables globals
    glm::vec3 posRoda1 = glm::vec3(-0.375, -0.125, 0);
    float AngleIniRoda = 0;      
    glm::vec3 posCano = glm::vec3(0.125, 0.25, 0); 
    float AngleTorreta=0;
    glm::vec3 posBaseTanc = glm::vec3(0);

};
