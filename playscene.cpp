#include "playscene.h"
#include "chooselevalscene.h"
#include "dataconfig.h"
#include "mycoin.h"
#include "mypushbutton.h"
#include <QDebug>
#include <QLabel>
#include <QMenuBar>
#include <QPainter>
#include <QPropertyAnimation>
#include <QSound>
#include <QTimer>

playscene::playscene(int levelNum)
{

    this->levelIndex = levelNum;

    //初始化游戏场景
    this->setFixedSize(320, 588);
    //设置图标
    this->setWindowIcon(QPixmap(":/res/Coin0001.png"));
    //设置标题
    this->setWindowTitle(QStringLiteral("翻金币场景"));
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

    //添加音效资源
    //翻金币音效
    QSound* flipSound = new QSound(":/res/ConFlipSound.wav");
    //返回按钮音效
    QSound* backSound = new QSound(":/res/BackButtonSound.wav");
    //胜利按钮音效
    QSound* winSound = new QSound(":/res/LevelWinSound.wav");

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
        if (d == 0) {
            d = d + 1;
        }
        //音效
        backSound->play();
        QTimer::singleShot(300, this, [=]() {
            //发出返回信号
            emit this->chooseSceneBack();
        });
    });

    //显示当前关卡数
    QLabel* label = new QLabel;
    label->setParent(this);
    QFont font;
    font.setFamily("华文新魏");
    font.setPointSize(20);
    QString str1 = QString("Level: %1").arg(this->levelIndex);
    //将字体设置到标签控件中
    label->setFont(font);
    label->setText(str1);
    label->setGeometry(30, this->height() - 50, 160, 50);

    //    初始化每个关卡二维数组
    dataConfig config;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            this->gameArray[i][j] = config.mData[this->levelIndex][i][j];
        }
    }

    //显示胜利的图片
    QLabel* winLabel = new QLabel;
    QPixmap tmpPix;
    tmpPix.load(":/res/LevelCompletedDialogBg.png");
    winLabel->setGeometry(0, 0, tmpPix.width(), tmpPix.height());
    winLabel->setPixmap(tmpPix);
    winLabel->setParent(this);
    winLabel->move((this->width() - tmpPix.width()) * 0.5, -tmpPix.height());

    //显示金币背景图案
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            //绘制背景图片
            QPixmap pix = QPixmap(":/res/BoardNode(1).png");
            QLabel* label = new QLabel;
            label->setGeometry(0, 0, pix.width(), pix.height());
            label->setPixmap(pix);
            label->setParent(this);
            label->move(57 + i * 50, 200 + j * 50);

            //创建金币
            QString str;
            if (this->gameArray[i][j] == 1) {
                //显示金币
                str = ":/res/Coin0001.png";
            } else {
                str = ":/res/Coin0008.png";
            }
            mycoin* coin = new mycoin(str);
            coin->setParent(this);
            coin->move(59 + i * 50, 204 + j * 50);

            //给金币属性赋值
            coin->posx = i;
            coin->posy = j;
            //正反面
            coin->flag = this->gameArray[i][j];

            //将金币放入金币的二维数组 方便后期维护
            coinBtn[i][j] = coin;

            //点击金币 翻转
            connect(coin, &mycoin::clicked, [=]() {
                //判断是否胜利
                //            this->iswin = true;
                int cd = 0;
                for (int a = 0; a < 4; a++) {
                    for (int b = 0; b < 4; b++) {
                        if (this->gameArray[a][b] == 0) {
                            //                        this->iswin = false;
                            cd = 1;
                            //                            qDebug() << "qwqw";
                            //只要有一个反面就是失败
                            break;
                        }
                    }
                }
                if (cd == 0) {
                    this->iswin = true;
                } else {
                    this->iswin = false;
                }
                if (this->iswin == false) {
                    //音效
                    flipSound->play();
                    coin->changeflag();
                    this->gameArray[i][j] = this->gameArray[i][j] == 0 ? 1 : 0;
                    //翻转周围的金币 延时
                    QTimer::singleShot(300, this, [=]() {
                        //右侧
                        if (coin->posx + 1 <= 3) {
                            coinBtn[coin->posx + 1][coin->posy]->changeflag();
                            this->gameArray[coin->posx + 1][coin->posy] = this->gameArray[coin->posx + 1][coin->posy] == 0 ? 1 : 0;
                        }
                        //左侧
                        if (coin->posx - 1 >= 0) {
                            coinBtn[coin->posx - 1][coin->posy]->changeflag();
                            this->gameArray[coin->posx - 1][coin->posy] = this->gameArray[coin->posx - 1][coin->posy] == 0 ? 1 : 0;
                        }
                        //上侧
                        if (coin->posy - 1 >= 0) {
                            coinBtn[coin->posx][coin->posy - 1]->changeflag();
                            this->gameArray[coin->posx][coin->posy - 1] = this->gameArray[coin->posx][coin->posy - 1] == 0 ? 1 : 0;
                        }
                        //下侧
                        if (coin->posy + 1 <= 3) {
                            coinBtn[coin->posx][coin->posy + 1]->changeflag();
                            this->gameArray[coin->posx][coin->posy + 1] = this->gameArray[coin->posx][coin->posy + 1] == 0 ? 1 : 0;
                        }
                    });
                } else {
                    d = d - 1;
                    if (d == 0) {
                        //胜利音效
                        winSound->play();
                        //将胜利的图片下放
                        QPropertyAnimation* animation = new QPropertyAnimation(winLabel, "geometry");
                        //设置时间间隔
                        animation->setDuration(1000);
                        //设置开始位置
                        animation->setStartValue(QRect(winLabel->x(),
                            winLabel->y(),
                            winLabel->width(),
                            winLabel->height()));
                        //设置结束位置
                        animation->setEndValue(QRect(winLabel->x(),
                            winLabel->y() + 114,
                            winLabel->width(),
                            winLabel->height()));
                        //设置缓和曲线
                        animation->setEasingCurve(QEasingCurve::OutBounce);
                        //执行动画
                        animation->start();
                    }
                }
            });
        }
    }
}

void playscene::paintEvent(QPaintEvent*)
{
    //加载背景
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0, 0, this->width(), this->height(), pix);

    //加载标题
    pix.load(":/res/Title.png");
    pix = pix.scaled(pix.width() * 0.5, pix.height() * 0.5);
    painter.drawPixmap(10, 30, pix.width(), pix.height(), pix);
}
