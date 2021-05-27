#include "mainscene.h"
#include "about.h"
#include "mypushbutton.h"
#include "ui_mainscene.h"
#include <QDebug>
#include <QPainter>
#include <QSound> //多媒体音效模块
#include <QTimer>

MainScene::MainScene(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainScene)
{
    ui->setupUi(this);

    //    配置主场

    //    设置固定大小
    setFixedSize(320, 588);

    //设置图标
    setWindowIcon(QIcon(":/res/Coin0001.png"));

    //设置标题
    setWindowTitle(QStringLiteral("翻金币主场景"));

    //退出按钮实现
    connect(ui->actionquit, &QAction::triggered, [=]() {
        this->close();
    });

    //about按钮
    //实例化baout场景
    about* about1 = new about;
    connect(ui->actionabout, &QAction::triggered, [=]() {
        about1->show();
    });

    //准备开始按钮音效
    QSound* startSound = new QSound(":/res/TapButtonSound.wav");
    //设置循环播放 -1即为无限循环
    //    startSound->setLoops(10);

    //开始按钮
    MyPushButton* startBtn = new MyPushButton(":/res/MenuSceneStartButton.png");

    //按钮放在界面上
    startBtn->setParent(this);
    startBtn->move(this->width() * 0.5 - startBtn->width() * 0.5,
        this->height() * 0.7);

    //实例化选择关卡场景
    chooseScene = new ChooseLevalScene;

    //监听选择关卡的返回信号
    connect(chooseScene, &ChooseLevalScene::chooseSceneBack,
        this, [=]() {
            //设置返回场景的位置
            this->setGeometry(chooseScene->geometry());
            //隐藏选择关卡场景
            chooseScene->hide();
            //重新显示主场景
            this->show();
        });

    connect(startBtn, &MyPushButton::clicked, [=]() {
        //        qDebug() << QStringLiteral("点击了开始");
        //播放音效资源
        startSound->play();
        startBtn->zoom1();
        startBtn->zoom2();

        //延时
        QTimer::singleShot(500, this, [=]() {
            //设置场景的位置
            chooseScene->setGeometry(this->geometry());
            //进入选择场景界面
            //自身隐藏
            this->hide();
            //显示选择关卡场景
            chooseScene->show();
        });
    });
}

void MainScene::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/OtherSceneBg.png");
    painter.drawPixmap(0, 0, this->width(), this->height(), pix);

    //画背景上图标
    pix.load(":/res/Title.png");
    pix.scaled(pix.width() * 0.5, pix.height() * 0.5);
    painter.drawPixmap(10, 30, pix);
}

MainScene::~MainScene()
{
    delete ui;
}
