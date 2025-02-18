#include <QLabel>
class MyLabel :public QLabel
{
    Q_OBJECT
    public:
    MyLabel (QWidget *parent);
    string text;
    public slots:
    void tractaReturn();
    signals:
    void returnPressed (const QString &);
}; 