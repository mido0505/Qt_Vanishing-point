#include "showimageqt5dialog.h"
#include "ui_showimageqt5dialog.h"
#include <qfiledialog.h>
#include <qdir.h>
#include <qlabel.h>
#include <QMouseEvent>
#include <QScrollArea>
#include <QLabel>
#include <math.h>
#include <qpainter.h>
#include <qpixmap.h>
#include "mylabel.h"

float show_x=0;
float show_y=0;//标记显示位置（像素）

float get_pix_x=0;
float get_pix_y=0;//获取图片像素值

float f_x=0.0;
float f_y=0.0;//设置焦距值

showimageqt5Dialog::showimageqt5Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::showimageqt5Dialog)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags()|Qt::WindowMaximizeButtonHint);//1
    setWindowFlags(windowFlags()|Qt::WindowMinimizeButtonHint);//2 1/2两句是为了在dialog中添加最大/最小化按钮
}

showimageqt5Dialog::~showimageqt5Dialog()
{
    delete ui;
}

void showimageqt5Dialog::on_showimage_2_clicked()
{
    QString filename=QFileDialog::getOpenFileName(this,tr("openfile"),QDir::currentPath());
    //QLabel label;

    if(!filename.isEmpty())
    {
        QImage image(filename);
        get_pix_x=image.width();
        get_pix_y=image.height();
        ui->label->resize(image.width(),image.height());//实现动态调整label大小
        ui->label->setPixmap(QPixmap::fromImage(image));
    }
}

void showimageqt5Dialog::on_show_deadpoint_2_clicked()
{
    QString pitch_value=ui->lineEdit_pichangle_in_2->text();
    double pitch_ang=pitch_value.toDouble()/57.3;
    QString head_value=ui->lineEdit_headangle_in_2->text();
    double head_ang=head_value.toDouble()/57.3;//获取输入角度值

    QString focal_x=ui->lineEdit_xfocal->text();
    double f_x=focal_x.toDouble();
    QString focal_y=ui->lineEdit_yfocal->text();
    double f_y=focal_y.toDouble();//获取输入焦距值

    show_x=f_x*tan(head_ang)+get_pix_x/2;
    show_y=f_y*tan(pitch_ang)+get_pix_y/2;//解算角度值对应的坐标值

    ui->label_tag->raise();

    QWidget::update();//强制调用绘图事件
}

Mylabel::Mylabel(QWidget *parent):
    QLabel(parent)
{

}//派生类需要在成员初始化列表中加入父类初始化

void Mylabel::paintEvent(QPaintEvent *event)
{
    QLabel::paintEvent(event);
    QPainter painter(this);


    QPixmap pix;
    //pix.load("D:/QT_Project/build-showimage-Qt4_8_6-Debug/debug/images/reddot.png");
    pix.load(":/reddot.png");
    painter.drawPixmap(show_x,show_y,10,10,pix);
}

void showimageqt5Dialog::mousePressEvent(QMouseEvent *event) // 鼠标按下事件
{
    this->setMouseTracking(true);
    int x=event->x();//获取鼠标坐标值
    int y=event->y();

    //QLabel label;
    QString focal_x=ui->lineEdit_xfocal->text();
    double f_x=focal_x.toDouble();
    QString focal_y=ui->lineEdit_yfocal->text();
    double f_y=focal_y.toDouble();//获取输入焦距值

    float pitch=(float)(atan((y-get_pix_y/2)/f_x))*57.3;//结算俯仰角和方向角
    float head=(float)(atan((x-get_pix_x/2)/f_y))*57.3;
    //float head=(float)(atan(x/1333.0))*57.3;

    QString str_deadpoint;
    QString str_pitchangle;
    QString str_headangle;
    QString str_imagesize;
    str_deadpoint = QString("%1 , %2").arg(x).arg(y);
    str_pitchangle = QString("%1").arg(pitch);
    str_headangle = QString("%1").arg(head);
    str_imagesize = QString("%1 , %2").arg(get_pix_x).arg(get_pix_y);

    ui->lineEdit_deadpoint_2->setText(str_deadpoint);
    ui->lineEdit_pitchangle_2->setText(str_pitchangle);
    ui->lineEdit_headangle_2->setText(str_headangle);
    ui->lineEdit_imagesize_2->setText(str_imagesize);
}


