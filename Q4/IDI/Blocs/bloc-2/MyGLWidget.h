// MyGLWidget.h
#include "BL2GLWidget.h"
#include "Model/model.h"
#include <QMouseEvent>
#include <QTimer>

class MyGLWidget : public BL2GLWidget {
  Q_OBJECT

  public slots:
  void animar();
  void animarPat();
  public:
    MyGLWidget(QWidget *parent=0) : BL2GLWidget(parent) {}
    ~MyGLWidget();

  protected:
  virtual void carregaShaders();
  virtual void projectTransform();
  virtual void paintGL();
  virtual void viewTransform();
  virtual void ini_camera();
  virtual void ini_escena();
  virtual void ini_escena2();
  virtual void initializeGL();
  virtual void modelTransformTerra();
  virtual void modelTransformHomer();
  virtual void modelTransformPat();
  virtual void modelTransformPat2();
  virtual void modelTransformPat3();
  virtual void modelTransformPat4();
  virtual void creaHomer();
  virtual void creaTerra();
  virtual void creaPatricio();
  virtual void creaBuffers();
  virtual void calculaCentreEscena();
  virtual void keyPressEvent (QKeyEvent *event);
  virtual void mousePressEvent( QMouseEvent * event);
  virtual void mouseMoveEvent(QMouseEvent * event);
  virtual void mouseReleaseEvent(QMouseEvent * event);
  virtual void resizeGL (int width, int height);

  GLuint projLoc, viewLoc;
  float fov, ratio, znear, zfar, Rotate, fov_ini;  //PM
  glm::vec3 OBS, VRP, UP;         //VM

  GLuint VAO_Homer, VAO_Terra, VAO_Pat;
  int size_model, size_model_pat;
  Model m, pat;
  glm::vec3 CentreCapsaPat, CentreBasePat, MaxEscenaPat, MinEscenaPat;
  float escalaPat, alçadaPat, ampladaPat, profunditatPat;

  glm::vec3 CentreEscena, MaxEscena, MinEscena;
  float radi, left, right, bottom, top, psi, theta, phi, distancia;

  bool prespective;
  bool TimerActiu;

  QTimer timer, timerPat;
  float rotatePat;
  //Ratolí
  bool accio;
  float posx, posy;

  private:
    int printOglError(const char file[], int line, const char func[]);
};
