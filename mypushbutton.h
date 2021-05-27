#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QIcon>
#include <QPushButton>
#include <QWidget>

class MyPushButton : public QPushButton {
    Q_OBJECT
public:
    //    explicit MyPushButon(QWidget *parent = nullptr)
    MyPushButton(QString normalImg, QString pressImg = "");
    QString normalImgPath;
    QString pressImgPath;

    //弹跳特效
    void zoom1(); //向下跳
    void zoom2(); // 向上跳

    //重写按钮 按下和释放事件
    void mousePressEvent(QMouseEvent* e);
    void mouseReleaseEvent(QMouseEvent* e);

signals:
};

#endif // MYPUSHBUTTON_H
