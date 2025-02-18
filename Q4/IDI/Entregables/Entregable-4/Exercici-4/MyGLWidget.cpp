// MyGLWidget.cpp
#include "MyGLWidget.h"
#include <iostream>
#include <stdio.h>

#define printOpenGLError() printOglError(__FILE__, __LINE__)
#define CHECK() printOglError(__FILE__, __LINE__,__FUNCTION__)
#define DEBUG() std::cout << __FILE__ << " " << __LINE__ << " " << __FUNCTION__ << std::endl;

MyGLWidget::MyGLWidget(QWidget *parent) : LL4GLWidget(parent) {
  connect (&timer, SIGNAL (timeout()), this, SLOT (animar ()));
}

void MyGLWidget::animar () {
  makeCurrent ();
  angleCotxe[0] += 2;
  angleCotxe[1] += 3;
  update ();
}
int MyGLWidget::printOglError(const char file[], int line, const char func[]) 
{
    GLenum glErr;
    int    retCode = 0;

    glErr = glGetError();
    const char * error = 0;
    switch (glErr)
    {
        case 0x0500:
            error = "GL_INVALID_ENUM";
            break;
        case 0x501:
            error = "GL_INVALID_VALUE";
            break;
        case 0x502: 
            error = "GL_INVALID_OPERATION";
            break;
        case 0x503:
            error = "GL_STACK_OVERFLOW";
            break;
        case 0x504:
            error = "GL_STACK_UNDERFLOW";
            break;
        case 0x505:
            error = "GL_OUT_OF_MEMORY";
            break;
        default:
            error = "unknown error!";
    }
    if (glErr != GL_NO_ERROR)
    {
        printf("glError in file %s @ line %d: %s function: %s\n",
                             file, line, error, func);
        retCode = 1;
    }
    return retCode;
}

MyGLWidget::~MyGLWidget() {
}

void MyGLWidget::mouseMoveEvent(QMouseEvent *e)
{
  makeCurrent();
  // Aqui cal que es calculi i s'apliqui la rotacio o el zoom com s'escaigui...
  if (DoingInteractive == ROTATE)
  {
    // Fem la rotació
    angleY -= (e->x() - xClick) * M_PI / ample;
    angleX += (e->y() - yClick) * M_PI / alt;
    viewTransform ();
  }
  xClick = e->x();
  yClick = e->y();

  update ();
}

void MyGLWidget::keyPressEvent(QKeyEvent* event) {
  makeCurrent();
  switch (event->key()) {
  case Qt::Key_Up: {
      angleCotxe[0] += 2;
      angleCotxe[1] += 3;
      // ...
    break;
	}
  case Qt::Key_L: {
      // ...
      if (llum)
        glClearColor(0.3, 0.3, 0.3, 1.0);
      else 
        glClearColor(0.5, 0.7, 1.0, 1.0);
      llum = not llum;
      glUniform1i(llumLoc, llum);
    break;
	}
  case Qt::Key_S: {
      // ...
      if (not timerAct)
        timer.start(50);
      else 
        timer.stop();
      timerAct = not timerAct;
    break;
	}	
  default: LL4GLWidget::keyPressEvent(event); break;
  }
  update();
}

void MyGLWidget::initializeGL(){
  LL4GLWidget::initializeGL();
  colorCotxeLoc = glGetUniformLocation (program->programId(), "colorCotxe");
  posFocusEscLoc = glGetUniformLocation (program->programId(), "posFocusEsc");
  posFocus2EscLoc = glGetUniformLocation (program->programId(), "posFocus2Esc");
  llumLoc = glGetUniformLocation(program->programId(), "llum");
  glUniform1i(llumLoc, llum);
}


void MyGLWidget::iniEscena(){
  centreEsc = glm::vec3(0., 2.5, 0.);
  radiEsc = sqrt(318.75);
  angleCotxe[0] = 0.0f;
  angleCotxe[1] = 0.0f;
  posCotxe[0] = glm::vec3(6.5, 0., 0.);
  posCotxe[1] = glm::vec3(9, 0., 0.);
  colorCotxe[0] = glm::vec3(1.0,0.,0.);
  colorCotxe[1] = glm::vec3 (0.0, 1.0, 0.0);
  colorCotxe[2] = glm::vec3 (0.);
  timerAct = false;
  llum = true;
  timer.stop();
}
void MyGLWidget::iniCamera(){
  angleY = 0.0;
  angleX = 0.0;
  viewTransform ();
}
void MyGLWidget::viewTransform(){
  glm::mat4 View(1.0);
	View = glm::translate(View, glm::vec3(0., 0., -2*radiEsc));
	View = glm::rotate(View, angleX, glm::vec3(1., 0., 0.));
	View = glm::rotate(View, -angleY, glm::vec3(0., 1., 0.));
	View = glm::translate(View, -centreEsc);
	glUniformMatrix4fv (viewLoc, 1, GL_FALSE, &View[0][0]);
}

void MyGLWidget::modelTransformTerra(){
  glm::mat4 TG(1.0f);
  TG = glm::scale(TG, glm::vec3(25./10.));
  TG = glm::translate(TG, glm::vec3(-5., 0., -5.));
  glUniformMatrix4fv (transLoc, 1, GL_FALSE, &TG[0][0]);
}

void MyGLWidget::modelTransformRoad (float angle){
    glm::mat4 TG(1.0f);
    TG = glm::rotate(TG, glm::radians(angle), glm::vec3(0,1,0));
    TG = glm::translate(TG, glm::vec3(5, 0.01, -5));
    //TG = glm::scale(TG, glm::vec3(5, 0 ,5));
    TG = glm::scale(TG, glm::vec3(5*escalaModels[ROAD]));
    TG = glm::translate(TG, -centreBaseModels[ROAD]);
    glUniformMatrix4fv(transLoc, 1, GL_FALSE, &TG[0][0]);
}

void MyGLWidget::modelTransformPipe (){
  glm::mat4 TG(1.0f);
  TG = glm::scale(TG, glm::vec3(5.0f));
  TG = glm::scale(TG, glm::vec3(escalaModels[PIPE]));
  TG = glm::translate(TG, -centreBaseModels[PIPE]);
  glUniformMatrix4fv (transLoc, 1, GL_FALSE, &TG[0][0]);
}

void MyGLWidget::modelTransformCar(float radi, float angle) {
  glm::mat4 TG(1.0f); 
  TG = glm::rotate(TG, glm::radians(angle), glm::vec3(0., 1., 0.));
  TG = glm::translate(TG, glm::vec3(radi,0,0));
  TG = glm::scale(TG, glm::vec3(escalaModels[CAR]));
  TG = glm::translate(TG, -centreBaseModels[CAR]);
  
  glUniformMatrix4fv (transLoc, 1, GL_FALSE, &TG[0][0]);
  
  if (radi == posCotxe[0].x) {
    posFocusEsc =  TG * glm::vec4(2.48, 0.4, -3.2, 1) ;
    glUniform3fv(posFocusEscLoc, 1, &posFocusEsc[0]); 
  } else{
    posFocusEsc =  TG * glm::vec4(2.48, 0.4, -3.2, 1) ;
    glUniform3fv(posFocus2EscLoc, 1, &posFocusEsc[0]);
  }
}

void MyGLWidget::paintGL(){
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // TERRA
  glBindVertexArray (VAO_Terra);
  modelTransformTerra ();
  glDrawArrays(GL_TRIANGLES, 0, 6);
  
  // Road
  for (float i = 0; i < 4; i++) {
    glBindVertexArray (VAO_models[ROAD]);
    modelTransformRoad (90*i);
    glDrawArrays(GL_TRIANGLES, 0, models[ROAD].faces().size()*3);
  }

  // Car
  for (int i = 0; i < 2; i++) {
    glBindVertexArray (VAO_models[CAR]);
    modelTransformCar (posCotxe[i].x, angleCotxe[i]);
    glUniform3fv(colorCotxeLoc, 1,  &colorCotxe[i].x);
    glDrawArrays(GL_TRIANGLES, 0, models[CAR].faces().size()*3);
  }
  glUniform3fv(colorCotxeLoc, 1,  &colorCotxe[2][0]);
  

  // Pipe
  glBindVertexArray (VAO_models[PIPE]);
  modelTransformPipe ();
  glDrawArrays(GL_TRIANGLES, 0, models[PIPE].faces().size()*3);
  
  glBindVertexArray(0);
}

void MyGLWidget::iniMaterialTerra(){
    diff = glm::vec3(0, 0.5, 0.5);
    amb = glm::vec3(0.1);
    spec = glm::vec3(0.8);
    shin = 100;
}


