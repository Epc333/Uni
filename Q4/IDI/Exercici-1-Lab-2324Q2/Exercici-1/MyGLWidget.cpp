#include "MyGLWidget.h"

#include <iostream>




MyGLWidget::MyGLWidget (QWidget* parent) : QOpenGLWidget(parent), program(NULL)
{
  setFocusPolicy(Qt::StrongFocus);  // per rebre events de teclat
}

MyGLWidget::~MyGLWidget ()
{
  if (program != NULL)
    delete program;
}

void MyGLWidget::initializeGL ()
{
  // Cal inicialitzar l'ús de les funcions d'OpenGL
  initializeOpenGLFunctions();
  
  glClearColor (0.5, 0.7, 1.0, 1.0); // defineix color de fons (d'esborrat)
  carregaShaders();
  creaBuffersQuadrat();
}

void MyGLWidget::pintaCanoTanc() {
  glBindVertexArray(VAOQuadrat);
  glm::mat4 TG(1.0f);
  TG = glm::translate(TG, posCano);
  TG = glm::rotate(TG, AngleTorreta, glm::vec3(0,0,1));
  TG = glm::translate(TG, glm::vec3(0.375, 0, 0));
  TG = glm::scale(TG, glm::vec3(0.75, 0.125, 1.0));
  TG = glm::translate(TG, glm::vec3(0.5, 0.5,0));
  glUniform3fv(colorLoc, 1, &gris[0]);
  glUniformMatrix4fv(TGLoc, 1, GL_FALSE, &TG[0][0]);
  glDrawArrays(GL_TRIANGLES, 0, 6);
  glBindVertexArray(0);  
}

//S'ha modificat per construir el tanc, és a dir
//els dos rectangles
void MyGLWidget::modelTransformQuadrat()
{
  glBindVertexArray(VAOQuadrat);
  glUniform3fv(colorLoc, 1, &verd[0]);
  glm::mat4 TG(1.0f);
  TG = glm::translate(TG, posBaseTanc);  
  TG = glm::scale(TG,glm::vec3(1, 0.25, 0)); 
  TG = glm::translate(TG, glm::vec3(0.5, 0.5, 0));
  glUniformMatrix4fv(TGLoc, 1, GL_FALSE, &TG[0][0]);
  glDrawArrays(GL_TRIANGLES, 0, 6); 
  TG = glm::mat4(1.0f);
  TG = glm:: translate(TG, glm::vec3(posBaseTanc.x + 0.125, posBaseTanc.y + 0.25, 0));
  TG = glm::scale(TG,glm::vec3(0.5, 0.25, 1));
  TG = glm::translate(TG, glm::vec3(0.5, 0.5, 0));
  glUniformMatrix4fv(TGLoc, 1, GL_FALSE, &TG[0][0]);
  glDrawArrays(GL_TRIANGLES, 0, 6);
  glBindVertexArray(0);
}

void MyGLWidget::pintaTanc() {
  modelTransformQuadrat();
  pintaCanoTanc();
  pintaRodesTanc();
  glBindVertexArray(0);
}

//S'ha agafat de base la funció inicial modelTransformQuadrat i s'ha aplicat una
//translació de 0.1 sobre l'eix de les x i un gir en l'eix de les z
void MyGLWidget::modelTransformQuadratGir(glm::vec3 posicio, glm::vec3 escala, float angle) {
  glm::mat4 TG(1.0f);
  TG = glm::translate(TG, posicio);
  TG = glm::rotate(TG, angle, glm::vec3(0,0,1));
  TG = glm::translate(TG, glm::vec3(0.1, 0 ,0));
  TG = glm::scale(TG, escala);
  TG = glm::translate(TG, glm::vec3(0.5, 0.5,0));
  glUniformMatrix4fv(TGLoc, 1, GL_FALSE, &TG[0][0]);
}

void MyGLWidget::pintaRodaIndividual(int pos){
  glBindVertexArray(VAOQuadrat);
  glm::vec3 LlocRoda = posRoda1 + glm::vec3(float(pos) * 0.25, 0, 0);
  for (int j = 0; j < 12; ++j) {
    glm::vec3 color;
    if (j % 2 == 0) 
      color = negre;
    else
      color = gris;
    glUniform3fv(colorLoc, 1, &color[0]);   //Segons la j, si es par o no, pinta el rectangle verd o gris
    modelTransformQuadratGir(LlocRoda, glm::vec3(0.1, 0.05, 1.0), float(j*M_PI/6) + AngleIniRoda);
    glDrawArrays(GL_TRIANGLES, 0, 6);
  }
   glBindVertexArray(0);
}

void MyGLWidget::pintaRodesTanc(){
  for (int i = 0; i < 4; ++i) {
    pintaRodaIndividual(i);
  }
}

void MyGLWidget::paintGL ()
{
// En cas de voler canviar els paràmetres del viewport, descomenteu la crida següent i
// useu els paràmetres que considereu (els que hi ha són els de per defecte)
//  glViewport (0, 0, ample, alt);
  
  glClear (GL_COLOR_BUFFER_BIT);  // Esborrem el frame-buffer

  pintaTanc();

  // Desactivem el VAO
  glBindVertexArray(0);
}

void MyGLWidget::resizeGL (int w, int h)
{
// Aquest codi és necessari únicament per a MACs amb pantalla retina.
#ifdef __APPLE__
  GLint vp[4];
  glGetIntegerv (GL_VIEWPORT, vp);
  ample = vp[2];
  alt = vp[3];
#else
  ample = w;
  alt = h;
#endif
}

void MyGLWidget::keyPressEvent(QKeyEvent* event)
{
  makeCurrent();
  switch (event->key()) {
    case Qt::Key_Left: 
      if(AngleTorreta < 17*M_PI/18){
        AngleTorreta += M_PI/18;
      }
    	break;
    case Qt::Key_Right: 
      if (AngleTorreta > 0) {
        AngleTorreta -=  M_PI/18;
      }

    	break;
    case Qt::Key_A: 
      posRoda1 -= glm::vec3(0.01, 0, 0);
      posCano -= glm::vec3(0.01, 0, 0);
      posBaseTanc -= glm::vec3(0.01,0,0);
      AngleIniRoda += M_PI/180;  
    	break;
    case Qt::Key_D: 
      posCano += glm::vec3(0.01, 0, 0);
      posRoda1 += glm::vec3(0.01, 0, 0);
      posBaseTanc += glm::vec3(0.01,0,0);
      AngleIniRoda -= M_PI/180;  
    	break;		
    default: event->ignore(); break;
  }
  update();
}

void MyGLWidget::creaBuffersQuadrat ()
{
  glm::vec3 Vertices[6];  // vèrtexs amb X, Y i Z
  
  // minX = -1.0
  // maxX = 0.0
  // minY = -1.0
  // maxY = 0.0
  
  Vertices[0] = glm::vec3(-1.0, 0.0, 0);
  Vertices[1] = glm::vec3( 0.0, -1.0, 0);
  Vertices[2] = glm::vec3( 0.0, 0.0, 0);
  Vertices[3] = glm::vec3( 0.0, -1.0, 0);
  Vertices[4] = glm::vec3( -1.0, 0.0, 0);
  Vertices[5] = glm::vec3( -1.0, -1.0, 0);
  
  // Creació del Vertex Array Object (VAO) que usarem per pintar el quadrat
  glGenVertexArrays(1, &VAOQuadrat);
  glBindVertexArray(VAOQuadrat);

  // Creació del buffer amb les posicions dels vèrtexs
  GLuint VBO;
  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
  glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(vertexLoc);

  // Desactivem el VAO
  glBindVertexArray(0);
}


void MyGLWidget::carregaShaders()
{
  // Creem els shaders per al fragment shader i el vertex shader
  QOpenGLShader fs (QOpenGLShader::Fragment, this);
  QOpenGLShader vs (QOpenGLShader::Vertex, this);
  // Carreguem el codi dels fitxers i els compilem
  fs.compileSourceFile("shaders/basicShader.frag");
  vs.compileSourceFile("shaders/basicShader.vert");
  // Creem el program
  program = new QOpenGLShaderProgram(this);
  // Li afegim els shaders corresponents
  program->addShader(&fs);
  program->addShader(&vs);
  // Linkem el program
  program->link();
  // Indiquem que aquest és el program que volem usar
  program->bind();

  // Obtenim identificador per a l'atribut “vertex” del vertex shader
  vertexLoc = glGetAttribLocation (program->programId(), "vertex");
  
  // Obtenim els identificadors dels uniforms
  TGLoc = glGetUniformLocation(program->programId(), "TG"); 

  //Obtenim els identificadors dels uniform pel color
  colorLoc = glGetUniformLocation(program->programId(), "color_fs"); 
}
