#include "mypushbutton.h"
#include <QComboBox>
#include <QDebug>
#include <QIcon>
#include <QPropertyAnimation>

MyPushButton::MyPushButton(QString normalImg, QString pressImg)
{
    this->normalImgPath = normalImg;
    this->pressImgPath = pressImg;

    QPixmap pix;
    bool ret = pix.load(normalImg);
    if (!ret) {
        qDebug() << "加载失败";
        return;
    }

    //设置图片固定大小
    this->setFixedSize(pix.width(), pix.height());

    //设置不规则图片样式
    this->setStyleSheet("QPushButton{border:0px;}");

    //设置图标
    this->setIcon(pix);

    //设置图标大小
    this->setIconSize(QSize(pix.width(), pix.height()));
}

//向下弹
void MyPushButton::zoom1()
{
    //创建动态对象
    QPropertyAnimation* animation = new QPropertyAnimation(this,
        "geometry");
    //设置时间间隔
    animation->setDuration(200);

    //起始位置
    animation->setStartValue(QRect(this->x(),
        this->y(),
        this->width(),
        this->height()));

    //结束位置
    animation->setEndValue(QRect(this->x(),
        this->y() + 10,
        this->width(),
        this->height()));
    //设置弹跳曲线
    animation->setEasingCurve(QEasingCurve::OutBounce);

    //执行动画
    animation->start();
}

//向上弹
void MyPushButton::zoom2()
{
    //创建动态对象
    QPropertyAnimation* animation = new QPropertyAnimation(this,
        "geometry");
    //设置时间间隔
    animation->setDuration(200);

    //起始位置
    animation->setStartValue(QRect(this->x(),
        this->y() + 10,
        this->width(),
        this->height()));

    //结束位置
    animation->setEndValue(QRect(this->x(),
        this->y(),
        this->width(),
        this->height()));
    //设置弹跳曲线
    animation->setEasingCurve(QEasingCurve::OutBounce);

    //执行动画
    animation->start();
}

//重写按钮 按下和释放特效
void MyPushButton::mousePressEvent(QMouseEvent* e)
{
    //传入图片不为空，切换图片
    if (this->pressImgPath != "") {
        QPixmap pix;
        bool ret = pix.load(this->pressImgPath);
        if (!ret) {
            qDebug() << "加载失败";
            return;
        }

        //设置图片固定大小
        this->setFixedSize(pix.width(), pix.height());

        //设置不规则图片样式
        this->setStyleSheet("QPushButton{border:0px;}");

        //设置图标
        this->setIcon(pix);

        //设置图标大小
        this->setIconSize(QSize(pix.width(), pix.height()));
    }

    //让父类执行其他内容
    return QPushButton::mousePressEvent(e);
}

void MyPushButton::mouseReleaseEvent(QMouseEvent* e)
{
    //传入图片不为空，切换图片
    if (this->pressImgPath != "") {
        QPixmap pix;
        bool ret = pix.load(this->normalImgPath);
        if (!ret) {
            qDebug() << "加载失败";
            return;
        }

        //设置图片固定大小
        this->setFixedSize(pix.width(), pix.height());

        //设置不规则图片样式
        this->setStyleSheet("QPushButton{border:0px;}");

        //设置图标
        this->setIcon(pix);

        //设置图标大小
        this->setIconSize(QSize(pix.width(), pix.height()));
    }

    //让父类执行其他内容
    return QPushButton::mouseReleaseEvent(e);
}
