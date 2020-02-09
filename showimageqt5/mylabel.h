#ifndef MYLABEL_H
#define MYLABEL_H
#include <QWidget>
#include <QPainter>
#include <QLabel>

using namespace std;

class Mylabel:public QLabel
{
    //Q_OBJECT
public:
    explicit Mylabel(QWidget *parent=0);
    //~Mylabel();

    //virtual void paintEvent(QPaintEvent *event) override;
//protected:
public:
    virtual void paintEvent(QPaintEvent *event);
};
#endif // MYLABEL_H
