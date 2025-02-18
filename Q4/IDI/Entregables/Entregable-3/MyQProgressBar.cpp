#include "MyQProgressBar.h"

QTimer MyQProgressBar::timer;
QTimer MyQProgressBar::timer2;
double MyQProgressBar::amplada;
double MyQProgressBar::fase;
bool MyQProgressBar::timerAct;

MyQProgressBar::MyQProgressBar (QWidget *parent)
    : QProgressBar(parent) {
    connect (&timer, SIGNAL(timeout()), this, SLOT(animar2()));
    connect (&timer2, SIGNAL(timeout()), this, SLOT(animar())); //Per quan canvies fase/amplitud es canvi també 
    }

void MyQProgressBar::animar() {
    int y = amplada*sin(double(valor)+fase+temps)*100;
    temps += 0.1;
    setValue(y);
}

void MyQProgressBar::animar2() {
    int y = amplada*sin(double(valor)+fase+temps)*100;
    setValue(y);
    timer.stop();
}


void MyQProgressBar::ActAmp(const int a){
    amplada = double(a)/100.0;
    if (not timerAct){
        timer.start(2);
    }
}

void MyQProgressBar::ActFase(const int a){
    fase = double(a)/100.0;
    if (not timerAct){
        timer.start(2);
    }
}

void MyQProgressBar::ActivarTimer(){
    if (valor != -1){     //Pq no s'activi el timer quan encara no s'ha iniciat
        if (timerAct) timer2.stop();
        else timer2.start(100);
        timerAct = !timerAct;
    }
}

void MyQProgressBar::inici(){
    temps = 0;
    amplada = 0.5;
    fase = 0;
    timerAct = false;
    timer2.stop();
    if (valor == -1) valor = value();
    emit setBarraHoritzontal(int(fase*100.));
    emit setBarraVert(int(amplada*100.));
    int y = amplada*sin(double(valor)+fase)*100;
    setValue(y);
}