#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include "mycoin.h"
#include <QMainWindow>

class playscene : public QMainWindow {
    Q_OBJECT
public:
    //    explicit playscene(QWidget *parent = nullptr);
    playscene(int levelNum);
    //记录所选关卡
    int levelIndex;
    //重写paintEvenet事件
    void paintEvent(QPaintEvent*);
    //二维数组维护关卡数据
    int gameArray[4][4];

    mycoin* coinBtn[4][4];
    //胜利标志
    bool iswin;
    //胜利标志下放
    int d = 1;

signals:
    void chooseSceneBack();
};

#endif // PLAYSCENE_H
