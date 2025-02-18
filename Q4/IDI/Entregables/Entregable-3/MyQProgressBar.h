#include <QTimer>
#include <QProgressBar>
#include <cmath>
#include <iostream>

class MyQProgressBar: public QProgressBar{
    Q_OBJECT
    private:
    int valor = -1;
    double temps;
    static QTimer timer, timer2;
    static double amplada, fase;
    static bool timerAct;
    public:

    MyQProgressBar (QWidget *parent);
     
    public slots:
    void ActAmp(const int x);
    void ActFase(const int x);
    void inici();
    void animar();
    void animar2();
    void ActivarTimer();

    signals:
    void setBarraHoritzontal(const int);
    void setBarraVert(const int);
};