#ifndef SHOWIMAGEQT5DIALOG_H
#define SHOWIMAGEQT5DIALOG_H

#include <QDialog>

namespace Ui {
class showimageqt5Dialog;
}

class showimageqt5Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit showimageqt5Dialog(QWidget *parent = nullptr);
    ~showimageqt5Dialog();

private slots:
    void on_showimage_2_clicked();

    void on_show_deadpoint_2_clicked();

private:
    Ui::showimageqt5Dialog *ui;
protected:
    void mousePressEvent(QMouseEvent *event);
};

#endif // SHOWIMAGEQT5DIALOG_H
