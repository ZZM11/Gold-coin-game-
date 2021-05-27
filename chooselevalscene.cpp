#include "chooselevalscene.h"
#include "mypushbutton.h"
#include "playscene.h"
#include <QDebug>
#include <QLabel>
#include <QMenuBar>
#include <QPainter>
#include <QSound>
#include <QTimer>

ChooseLevalScene::ChooseLevalScene(QWidget* parent)
    : QMainWindow(parent)
{
    //配置选择关卡场景
    this->setFixedSize(320, 588);

    //设置图标
    this->setWindowIcon((QPixmap(":/res/Coin0001.png")));

    //设置标题
    this->setWindowTitle(QStringLiteral("选择关卡场景"));

    //创建菜单栏
    QMenuBar* bar = menuBar();
    setMenuBar(bar);

    //创建开始菜单
    QMenu* startMenu = bar->addMenu(QStringLiteral("开始"));

    //创建退出的菜单项
    QAction* quitAction = startMenu->addAction(QStringLiteral("退出"));

    //点击退出 实现退出游戏
    connect(quitAction, &QAction::triggered,
        [=]() {
            this->close();
        });

    //选择关卡音效
    QSound* chooseSound = new QSound(":/res/TapButtonSound.wav");

    //返回音效
    QSound* backSound = new QSound(":/res/BackButtonSound.wav");

    //返回按钮
    MyPushButton* backBtn = new MyPushButton(":/res/BackButton.png",
        ":/res/BackButtonSelected.png");

    backBtn->setParent(this);
    backBtn->move(this->width() - backBtn->width(),
        this->height() - backBtn->height());

    //点击返回
    connect(backBtn, &MyPushButton::clicked, [=]() {
        //        qDebug() << QStringLiteral("点击了返回按钮");
        //告诉主场景返回了
        //主场景监听返回按钮
        //延时返回
        //返回音效
        backSound->play();
        QTimer::singleShot(300, this, [=]() {
            //发出返回信号
            emit this->chooseSceneBack();
        });
    });

    //创建选择关卡的按钮
    for (int i = 0; i < 20; i++) {
        MyPushButton* menuBtn = new MyPushButton(":/res/LevelIcon.png");
        menuBtn->setParent(this);
        menuBtn->move(i % 4 * 70 + 25, i / 4 * 70 + 130);

        //监听每个按钮的点击事件
        connect(menuBtn, &MyPushButton::clicked, [=]() {
            //            qDebug() << i + 1;
            //进入到游戏场景
            //选关场景隐藏
            //播放音效
            chooseSound->play();
            this->hide();
            //创建游戏场景
            play = new playscene(i + 1);
            //设置游戏场景初始位置
            play->setGeometry(this->geometry());
            play->show();

            connect(play, &playscene::chooseSceneBack, [=]() {
                this->show();
                this->setGeometry(this->geometry());
                delete play;
                play = NULL;
            });
        });

        QLabel* label = new QLabel;
        label->setParent(this);
        label->setFixedSize(menuBtn->width(), menuBtn->height());
        label->setText(QString::number(i + 1));
        label->move(i % 4 * 70 + 25, i / 4 * 70 + 130);

        //设置文字对齐方式 水平居中和垂直居中
        label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        //设置让鼠标穿透 51号属性
        label->setAttribute(Qt::WA_TransparentForMouseEvents);
    }
}

void ChooseLevalScene::paintEvent(QPaintEvent*)
{
    //加载背景
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/OtherSceneBg.png");
    painter.drawPixmap(0, 0, this->width(), this->height(), pix);

    //加载标题
    pix.load(":/res/Title.png");
    painter.drawPixmap((this->width() - pix.width()) * 0.5, 30,
        pix.width(), pix.height(), pix);
}
