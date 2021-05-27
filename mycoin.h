#ifndef MYCOIN_H
#define MYCOIN_H

#include <QPushButton>
#include <QTimer>
//#include"playscene.h"

class mycoin : public QPushButton {
    Q_OBJECT
public:
    //    explicit mycoin(QWidget *parent = nullptr);
    //参数代表 传入的金币路径 银币路径
    mycoin(QString btnImg);
    //    金币的属性
    //    x坐标
    int posx;
    //y坐标
    int posy;
    //正反标示
    bool flag;
    //改变标志的方法
    void changeflag();
    //正面翻反面的定时器
    QTimer* timer1;
    //反面翻正面的定时器
    QTimer* timer2;
    int min = 1;
    int max = 8;

    //执行动画的标志
    bool isanimation = false;

    //重写按下
    void mousePressEvent(QMouseEvent* e);

    //是否胜利的标志
    //    bool iswin = false;

signals:
};

#endif // MYCOIN_H
