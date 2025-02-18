#include "MyLabelQt.h"


MyLabelQt::MyLabelQt (QWidget *parent)
    : QLineEdit(parent) {
        connect (this, SIGNAL(returnPressed()), this, SLOT(tractaReturn()));
    }

    void MyLabelQt::tractaReturn() {
        emit returnPressed(text());
    }