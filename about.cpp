#include "about.h"
#include <QLabel>
#include <QMainWindow>
#include <QPixmap>

about::about(QWidget* parent)
    : QMainWindow(parent)
{
    //配置选择关卡场景
    this->setFixedSize(600, 250);

    //设置图标
    this->setWindowIcon((QPixmap(":/res/Coin0001.png")));

    //设置标题
    this->setWindowTitle(QStringLiteral("软件信息"));

    QLabel* label = new QLabel;
    label->setParent(this);
    label->setFixedSize(600, 250);
    label->move(10, 5);
    QFont font;
    font.setFamily("华文新魏");
    font.setPointSize(15);
    label->setFont(font);
    label->setText(QStringLiteral("翻金币游戏\n"
                                  "作者：zzm\n"
                                  "时间：2021.5.27\n"
                                  "邮箱：2108935363@qq.com\n"
                                  "运行环境：QT 5.9.9 MSVC2015 64bit\n"
                                  "本游戏在传智教育的教学视频指导下完成，\n"
                                  "详情了解:\n"
                                  "https://www.bilibili.com/video/BV1g4411H78N"));
}
