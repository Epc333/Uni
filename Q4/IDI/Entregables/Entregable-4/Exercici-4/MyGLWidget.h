// MyGLWidget.h
#include "LL4GLWidget.h"
#include <QTimer>

class MyGLWidget : public LL4GLWidget {
  Q_OBJECT
  public:
    MyGLWidget(QWidget *parent=0);
    ~MyGLWidget();

  public slots:
    void animar();
    
  protected:


    virtual void initializeGL();

    virtual void paintGL();

    virtual void viewTransform ();

    virtual void mouseMoveEvent(QMouseEvent *e);
    virtual void keyPressEvent(QKeyEvent* event);

    virtual void iniEscena();
    virtual void iniCamera();
    virtual void iniMaterialTerra();

    

    virtual void modelTransformTerra();
    virtual void modelTransformRoad(float angle);
    virtual void modelTransformPipe ();
    virtual void modelTransformCar (float radi, float angle);


    float angleCotxe[2];
    glm::vec3 posCotxe[2], colorCotxe[3];

    float angleX;

    glm::vec3 colorFocus, posFocusEsc;
    GLuint colorCotxeLoc, posFocusEscLoc, posFocus2EscLoc, llumLoc;
    bool timerAct, llum;
    QTimer timer;

  private:
    int printOglError(const char file[], int line, const char func[]);
};
