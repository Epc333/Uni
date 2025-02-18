// MyGLWidget.cpp
#include "MyGLWidget.h"
#include <iostream>
#include <stdio.h>

#define printOpenGLError() printOglError(__FILE__, __LINE__)
#define CHECK() printOglError(__FILE__, __LINE__,__FUNCTION__)
#define DEBUG() std::cout << __FILE__ << " " << __LINE__ << " " << __FUNCTION__ << std::endl;

void MyGLWidget::initializeGL() {
    BL2GLWidget::initializeGL();
    ini_escena();
    prespective = true;
    accio = TimerActiu = false;
    psi = theta = phi = 0;
    Rotate = 0;
    timerPat.start(32);
    ini_camera();
    glEnable(GL_DEPTH_TEST);
    connect(&timer, SIGNAL(timeout()), this, SLOT(animar()));
    connect(&timerPat, SIGNAL(timeout()), this, SLOT(animarPat()));
}

void MyGLWidget::animar(){
    makeCurrent();
    Rotate += 0.15;
    update();
}

void MyGLWidget::animarPat(){
    makeCurrent();
    rotatePat += 0.15;
    update();
}

void MyGLWidget::carregaShaders(){
    BL2GLWidget::carregaShaders();
    projLoc = glGetUniformLocation(program->programId(), "proj");
    viewLoc = glGetUniformLocation(program->programId(), "view");
}

void MyGLWidget::projectTransform(){
    glm::mat4 Proj;
    if (prespective) Proj = glm::perspective(fov, ratio, znear, zfar);
    else Proj = glm::ortho(left, right, bottom, top, znear, zfar);
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, &Proj[0][0]);
}

void MyGLWidget::viewTransform() {
    glm::mat4 View (1.0f);
    View = glm::translate(View, glm::vec3(0, 0, -distancia));
    View = glm::rotate(View, -phi, glm::vec3(0.,0.,1.));
    View = glm::rotate(View, theta, glm::vec3(0.,1.,0));
    View = glm::rotate(View, -psi, glm::vec3(1.0,0.,0.));
    View = glm::translate(View, -VRP);
    glUniformMatrix4fv (viewLoc, 1, GL_FALSE, &View[0][0]);
}

void MyGLWidget::paintGL () 
{
    projectTransform();
    viewTransform();
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  //glBindVertexArray(VAO_Homer);
  //modelTransformHomer();
  //sglDrawArrays(GL_TRIANGLES, 0, size_model);

  glBindVertexArray(VAO_Pat);
  modelTransformPat();
  glDrawArrays(GL_TRIANGLES, 0, size_model_pat);
  modelTransformPat2();
  glDrawArrays(GL_TRIANGLES, 0, size_model_pat);
  modelTransformPat3();
  glDrawArrays(GL_TRIANGLES, 0, size_model_pat);
  modelTransformPat4();
  glDrawArrays(GL_TRIANGLES, 0, size_model_pat);

   glBindVertexArray(VAO_Terra);
  modelTransformTerra();
  glDrawArrays(GL_TRIANGLES, 0, 6);

  glBindVertexArray(0);
}

void MyGLWidget::calculaCentreEscena(){                
    float xmax, xmin, ymax, ymin, zmax, zmin;
    xmax = xmin = pat.vertices()[0];
    ymin = ymax = pat.vertices()[1];
    zmax = zmin = pat.vertices()[2];
    for (uint i = 3; i< pat.vertices().size(); i+= 3) {
        if (pat.vertices()[i] > xmax) xmax = pat.vertices()[i];
        else if (pat.vertices()[i] < xmin) xmin =pat.vertices()[i];
        if (pat.vertices()[i+1] > ymax) ymax = pat.vertices()[i+1];
        else if (pat.vertices()[i+1] < ymin) ymin =pat.vertices()[i+1];
        if (pat.vertices()[i+2] > zmax) zmax = pat.vertices()[i+2];
        else if (pat.vertices()[i+2] < zmin) zmin =pat.vertices()[i+2];
    }
    CentreCapsaPat = glm::vec3((xmax+xmin)/2, (ymax + ymin)/2, (zmax + zmin)/2);
    CentreBasePat = glm::vec3((xmax+xmin)/2, ymin, (zmax + zmin)/2);
    MaxEscenaPat = glm::vec3(xmax, ymax, zmax);
    MinEscenaPat =glm::vec3(xmin, ymin, zmin);
    escalaPat = 4/(ymax-ymin);
    alçadaPat = ymax-ymin;
    ampladaPat = xmax-xmin;
    profunditatPat = zmax - zmin; 
    //ini_escena2();
    
}

void MyGLWidget::ini_escena2() {
    //float xmax, xmin, ymax, ymin, zmax, zmin;
    if ((MinEscenaPat.x - CentreBasePat.x)*escalaPat < MinEscena.x) MinEscena.x = (MinEscenaPat.x - CentreBasePat.x)*escalaPat;
    if ((MinEscenaPat.y - CentreBasePat.y)*escalaPat < MinEscena.y) MinEscena.y = (MinEscenaPat.y - CentreBasePat.y)*escalaPat;
    if ((MinEscenaPat.z - CentreBasePat.x)*escalaPat < MinEscena.z) MinEscena.z = (MinEscenaPat.z - CentreBasePat.z)*escalaPat;
    if ((MaxEscenaPat.x - CentreBasePat.x)*escalaPat > MaxEscena.x) MaxEscena.x = (MaxEscenaPat.x - CentreBasePat.x)*escalaPat;
    if ((MaxEscenaPat.y - CentreBasePat.y)*escalaPat > MaxEscena.y) MaxEscena.y = (MaxEscenaPat.y - CentreBasePat.y)*escalaPat;
    if ((MaxEscenaPat.z - CentreBasePat.z)*escalaPat > MaxEscena.z) MaxEscena.z = (MaxEscenaPat.z - CentreBasePat.z)*escalaPat;

    CentreEscena = glm::vec3((MaxEscena.x+MinEscena.x)/2.f, (MaxEscena.y+MinEscena.y)/2.f, (MaxEscena.z+MinEscena.z)/2.f);
    //CentreEscena = glm::vec3((xmin+xmax)/2.f, (ymax+ymin)/2.f, (zmin+zmax)/2.f);
    radi = glm::distance(CentreEscena, MaxEscena);
    std::cout  << "Hola" << std::endl;
    ini_camera();
}

void MyGLWidget::ini_camera(){
    distancia = 2*radi;
    fov_ini = 2*(asin(float(radi/distancia)));
    fov = fov_ini;
    ratio = 1.0f;
    znear = radi;
    zfar = 3*radi;
    OBS = CentreEscena + distancia*glm::vec3(0.,0.,1.);
    VRP = CentreEscena;
    UP = glm::vec3 (0, 1, 0);

    left = bottom = -radi;
    right = top = radi;

    projectTransform();
    viewTransform();
}

void MyGLWidget::ini_escena(){
    float xmax, xmin, ymax, ymin, zmax, zmin;
    xmin = zmin = -2.5f;
    xmax = zmax = 2.5f;
    ymin = 0.f;
    ymax = 1.f;
    
    MinEscena = glm::vec3(xmin, ymin, zmin);
    MaxEscena = glm::vec3(xmax, ymax, zmax);
    CentreEscena = glm::vec3((xmin+xmax)/2.f, (ymax+ymin)/2.f, (zmin+zmax)/2.f);
    radi = glm::distance(CentreEscena, MaxEscena);
}
void MyGLWidget::creaTerra(){
    glm::vec3 posicio_terra[6] = {
        glm::vec3(-2.0f, -1.0f, -2.0f),
        glm::vec3(2.0f, -1.0f, -2.0f),
        glm::vec3(-2.0f, -1.0f, 2.0f),
        glm::vec3(-2.0f, -1.0f, 2.0f),
        glm::vec3(2.0f, -1.0f, -2.0f),
        glm::vec3(2.0f, -1.0f, 2.0f)
    };
    glm::vec3 color_terra[6] = {
        glm::vec3(1,0,0),
        glm::vec3(0,1,0),
        glm::vec3(0,0,1),
        glm::vec3(0,0,1),
        glm::vec3(0,1,0),
        glm::vec3(1,0,0)
    };
    glGenVertexArrays(1, &VAO_Terra);
    glBindVertexArray(VAO_Terra);

    GLuint VBO_Terra[2];
    glGenBuffers(2, VBO_Terra);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_Terra[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(posicio_terra), posicio_terra, GL_STATIC_DRAW);
    glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(vertexLoc);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_Terra[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(color_terra), color_terra, GL_STATIC_DRAW);
    glVertexAttribPointer(colorLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(colorLoc);
    glBindVertexArray(0);
}

void MyGLWidget::creaHomer(){
    m.load("models/HomerProves.obj");
    size_model = m.faces().size()*3;
    glGenVertexArrays(1, &VAO_Homer);
    glBindVertexArray(VAO_Homer);

    GLuint VBO_Homer[2];
    glGenBuffers(2, VBO_Homer);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_Homer[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*size_model*3, m.VBO_vertices(), GL_STATIC_DRAW);
    glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(vertexLoc);

    glBindBuffer(GL_ARRAY_BUFFER, VBO_Homer[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*size_model*3, m.VBO_matdiff(), GL_STATIC_DRAW);
    glVertexAttribPointer(colorLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(colorLoc);
    glBindVertexArray(0);
}

void MyGLWidget::modelTransformPat(){
    glm::mat4 transform (1.0f);
    transform = glm::rotate(transform, Rotate + float(M_PI/2), glm::vec3(0.0, 1., 0.));
    transform = glm::scale(transform, glm::vec3(1.f/alçadaPat));
    transform = glm::translate(transform, glm::vec3(-CentreBasePat));
    glUniformMatrix4fv(transLoc, 1, GL_FALSE, &transform[0][0]);
}
void MyGLWidget::modelTransformPat2(){
    glm::mat4 transform (1.0f);
    transform = glm::translate(transform, glm::vec3(2.0, 0.0, 2.0));
    transform = glm::rotate(transform, Rotate, glm::vec3(0.0, 1., 0.));
    transform = glm::scale(transform, glm::vec3(1.f/alçadaPat));
    transform = glm::translate(transform, glm::vec3(-CentreBasePat));
    glUniformMatrix4fv(transLoc, 1, GL_FALSE, &transform[0][0]);
}

void MyGLWidget::modelTransformPat3(){
    glm::mat4 transform (1.0f);
    transform = glm::translate(transform, glm::vec3(-2.0, 0.0, -2.0));
    transform = glm::rotate(transform, Rotate + float(M_PI), glm::vec3(0.0, 1., 0.));
    transform = glm::scale(transform, glm::vec3(1.f/alçadaPat));
    transform = glm::translate(transform, glm::vec3(-CentreBasePat));
    glUniformMatrix4fv(transLoc, 1, GL_FALSE, &transform[0][0]);
}

void MyGLWidget::modelTransformPat4(){
    glm::mat4 transform (1.0f);
    transform = glm::rotate(transform, rotatePat, glm::vec3(0.,1.,0.));
    transform = glm::translate(transform, glm::vec3(1.5, 0., 0.));
    transform = glm::rotate(transform, Rotate + float(M_PI), glm::vec3(0.0, 1., 0.));
    transform = glm::scale(transform, glm::vec3(1.f/alçadaPat));
    transform = glm::translate(transform, glm::vec3(-CentreBasePat));
    glUniformMatrix4fv(transLoc, 1, GL_FALSE, &transform[0][0]);
}

void MyGLWidget::creaPatricio(){
    pat.load("models/Patricio.obj");
    size_model_pat = pat.faces().size()*3;
    glGenVertexArrays(1, &VAO_Pat);
    glBindVertexArray(VAO_Pat);

    GLuint VBO_Pat[2];
    glGenBuffers(2, VBO_Pat);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_Pat[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*size_model_pat*3, pat.VBO_vertices(), GL_STATIC_DRAW);
    glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(vertexLoc);

    glBindBuffer(GL_ARRAY_BUFFER, VBO_Pat[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*size_model_pat*3, pat.VBO_matdiff(), GL_STATIC_DRAW);
    glVertexAttribPointer(colorLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(colorLoc);
    glBindVertexArray(0);

    calculaCentreEscena();

}

void MyGLWidget::creaBuffers(){
    BL2GLWidget::creaBuffers();

    creaTerra();    
    creaHomer();
    creaPatricio();
}

void MyGLWidget::resizeGL (int w, int h) 
{
  ample = w;
  alt = h;
  float ra = float(w)/float(h);
  if (prespective){
    if (ra < 1) {
        fov = 2*atan(tan(fov_ini/2)/ra);
        ratio = 1;
    }
    else ratio = ra;
  }else{
    if (ra > 1) {
        left = -radi * ra;
        right = radi * ra;
    } else {
        bottom = -radi/ra;
        top = radi/ra;
    }


  }
  projectTransform();
}


void MyGLWidget::keyPressEvent(QKeyEvent *event) {
    makeCurrent();
    switch (event->key()) {
        case Qt::Key_R: {
            Rotate += M_PI/4;
            break;
        }
        case Qt::Key_O: {
            prespective = not prespective;
            projectTransform();
            break;
        }
        case Qt::Key_Z: {
            if (fov > 0.1) fov -= float(M_PI)/45;
            if (not prespective) {  //No va bé
                left += 0.08;
                right -= 0.08;
                bottom += 0.08;
                top -= 0.08;
            }
            break;
        }
        case Qt::Key_X: {
            if (fov < M_PI) fov += float(M_PI)/45;
            if (not prespective) {
                left -= 0.08;
                right += 0.08;
                bottom -= 0.08;
                top += 0.08;
            }
            break;
        }
        case Qt::Key_Q: {
            TimerActiu = not TimerActiu;
            if (TimerActiu) timer.start(16);
            else timer.stop();
            break;
        }
        default: event->ignore(); break;
    }
    update();
}

void MyGLWidget::mousePressEvent(QMouseEvent *event) {
    makeCurrent();
    if (event -> buttons() == Qt::LeftButton && !(event->modifiers() & (Qt::ShiftModifier | Qt::AltModifier | Qt::ControlModifier))) {
        accio = true;
        posx = event->x();
        posy = event->y();
    }
    update();
}

void MyGLWidget::mouseMoveEvent(QMouseEvent *event) {
    makeCurrent();
    if(accio) {
        theta += (event->x() - posx)/200;
        psi -= (event->y() - posy)/200;
        posx = event->x();
        posy = event->y();
    }
    update();
}

void MyGLWidget::mouseReleaseEvent(QMouseEvent *event) {
    makeCurrent();
    accio = false;
    event->ignore();
    update();

}

void MyGLWidget::modelTransformTerra() {
    glm::mat4 transform (1.0f);
    transform = glm::scale(transform, glm::vec3(escala));
    transform = glm::scale(transform, glm::vec3(1.25));
    transform = glm::translate(transform, glm::vec3(0., 1., 0.));
    glUniformMatrix4fv(transLoc, 1, GL_FALSE, &transform[0][0]);
}

void MyGLWidget::modelTransformHomer () 
{
  // Matriu de transformació de model
  glm::mat4 transform (1.0f);
  transform = glm::rotate(transform, Rotate, glm::vec3(0.0, 1., 0.));
  transform = glm::scale(transform, glm::vec3(escala));
  glUniformMatrix4fv(transLoc, 1, GL_FALSE, &transform[0][0]);
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


