// MyGLWidget.h
#include "BL3GLWidget.h"
#include "glm/gtc/matrix_inverse.hpp"

class MyGLWidget : public BL3GLWidget {
  Q_OBJECT

  public:
    MyGLWidget(QWidget *parent=0) : BL3GLWidget(parent) {}
    ~MyGLWidget();

  protected:
    virtual void initializeGL();
    virtual void iniMaterialTerra();
    //virtual void modelTransformTerra ();
    //virtual void modelTransformPatricio ();
    virtual void paintGL();
    virtual void iniFocus();

    virtual void mouseMoveEvent(QMouseEvent *e);
    virtual void keyPressEvent(QKeyEvent* event);

    // uniform Inversa
    glm::vec3 posFocus, colorFocus;
    GLuint colorFocusLoc, posFocusLoc;
    GLuint lSCOLoc;
    bool focus;

  private:
    int printOglError(const char file[], int line, const char func[]);
};
