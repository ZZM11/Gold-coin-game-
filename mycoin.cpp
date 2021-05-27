#include "mycoin.h"

mycoin::mycoin(QString btnImg)
{
    QPixmap pix;
    pix.load(btnImg);
    this->setFixedSize(pix.width(), pix.height());
    this->setStyleSheet("QPushButton{border:0px;}");
    this->setIcon(pix);
    this->setIconSize((QSize(pix.width(), pix.height())));

    //初始化定时器对象
    timer1 = new QTimer(this);
    timer2 = new QTimer(this);

    //监听正面翻反面的信号
    connect(timer1, &QTimer::timeout, [=]() {
        QPixmap pix;
        QString str3 = QString(":/res/Coin000%1").arg(this->min++);
        pix.load(str3);
        this->setFixedSize(pix.width(), pix.height());
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(), pix.height()));
        //判断 是否翻完了 重置
        if (this->min > this->max) {
            this->min = 1;
            //停止做动画
            isanimation = false;
            timer1->stop();
        }
    });

    //监听反面翻正面
    connect(timer2, &QTimer::timeout, [=]() {
        QPixmap pix;
        QString str3 = QString(":/res/Coin000%1").arg(this->max--);
        pix.load(str3);
        this->setFixedSize(pix.width(), pix.height());
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(), pix.height()));
        //判断 是否翻完了 重置
        if (this->min > this->max) {
            this->max = 8;
            //停止做动画
            isanimation = false;
            timer2->stop();
        }
    });
}

//重写按下
void mycoin::mousePressEvent(QMouseEvent* e)
{
    if (this->isanimation) {
        return;
    } else {
        QPushButton::mousePressEvent(e);
    }
}

void mycoin::changeflag()
{
    //如果是正面 翻成反面
    if (this->flag) {
        //开始定时器
        timer1->start(30);
        //开始做动画
        isanimation = true;
        this->flag = false;
    } else {
        //反面翻正面
        timer2->start(30);
        //开始做动画
        isanimation = true;
        this->flag = true;
    }
}
