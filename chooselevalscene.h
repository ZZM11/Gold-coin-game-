#ifndef CHOOSELEVALSCENE_H
#define CHOOSELEVALSCENE_H

#include "playscene.h"
#include <QMainWindow>

class ChooseLevalScene : public QMainWindow {
    Q_OBJECT
public:
    explicit ChooseLevalScene(QWidget* parent = 0);

    //重写绘图实现
    void paintEvent(QPaintEvent*);
    //游戏场景对象指针
    playscene* play = NULL;
signals:
    //写一个自定义信号 告诉场景 点击了返回
    void chooseSceneBack();
};

#endif // CHOOSELEVALSCENE_H
