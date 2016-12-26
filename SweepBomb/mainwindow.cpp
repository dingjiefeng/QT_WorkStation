#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    gameRow = game->getRow();
    gameCol = game->getCol();
    level = EASY;
    setFixedSize(gameCol * blockSize + offsetX * 2, gameRow * blockSize + offsetY * 2 + spaceY);
    connect(ui->actionEasy,SIGNAL(triggered(bool)),this,SLOT(startEasyGame()));
    connect(ui->actionMedium,SIGNAL(triggered(bool)),this,SLOT(startMediumGame()));
    connect(ui->actionHard,SIGNAL(triggered(bool)),this,SLOT(startHardGame()));
    connect(ui->actionQuit,SIGNAL(triggered(bool)),this,SLOT(close()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::restart(int theRow, int theCol, int theTotalBomb)
{
    delete game;
    game = new block(theRow,theCol,theTotalBomb);
    gameRow = theRow;gameCol = theCol;
    update();
}



void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPixmap pngBlockDouble(":/block_double.png");
    QPixmap pngBlockNone(":/block_none.png");
    QPixmap pngRedFlag(":/redFlag.png");
    QPixmap pngBomb(":/bomb.png");
    QPixmap pngOne(":/数字1.png");QPixmap pngTwo(":/数字2.png");QPixmap pngThr(":/数字3.png");
    QPixmap pngFor(":/数字4.png");QPixmap pngFiv(":/数字5.png");QPixmap pngSix(":/数字6.png");
    QPixmap pngSvn(":/数字7.png");QPixmap pngEight(":/数字8.png");
    pngBlockDouble = pngBlockDouble.scaled(QSize(blockSize,blockSize));
    pngBlockNone = pngBlockNone.scaled(QSize(blockSize,blockSize));
    pngRedFlag = pngRedFlag.scaled(QSize(blockSize,blockSize));
    pngBomb = pngBomb.scaled(QSize(blockSize,blockSize));
    pngOne = pngOne.scaled(QSize(blockSize,blockSize));
    pngTwo = pngTwo.scaled(QSize(blockSize,blockSize));
    pngThr = pngThr.scaled(QSize(blockSize,blockSize));
    pngFor = pngFor.scaled(QSize(blockSize,blockSize));
    pngFiv = pngFiv.scaled(QSize(blockSize,blockSize));
    pngSix = pngSix.scaled(QSize(blockSize,blockSize));
    pngSvn = pngSvn.scaled(QSize(blockSize,blockSize));
    pngEight = pngEight.scaled(QSize(blockSize,blockSize));

    for(int i=0;i<gameRow;++i)
    {
        for(int j=0;j<gameCol;++j)
        {
            unit &curUnit = game->map[i][j];
            switch(curUnit.curState)
            {
            case UNDIGGED:
                if(game->checkGame()==LOSE&&curUnit.isBomb==1)
                    painter.drawPixmap(j*blockSize+offsetX,i*blockSize+offsetY+spaceY,pngBomb);
                else
                    painter.drawPixmap(j*blockSize+offsetX,i*blockSize+offsetY+spaceY,pngBlockDouble);
                break;
            case DIGGED:
            {
                if(curUnit.isBomb==0)
                {
                    switch(curUnit.bombNum)
                    {
                    case 0:
                        painter.drawPixmap(j*blockSize+offsetX,i*blockSize+offsetY+spaceY,pngBlockNone);
                        break;
                    case 1:
                        painter.drawPixmap(j*blockSize+offsetX,i*blockSize+offsetY+spaceY,pngOne);
                        break;
                    case 2:
                        painter.drawPixmap(j*blockSize+offsetX,i*blockSize+offsetY+spaceY,pngTwo);
                        break;
                    case 3:
                        painter.drawPixmap(j*blockSize+offsetX,i*blockSize+offsetY+spaceY,pngThr);
                        break;
                    case 4:
                        painter.drawPixmap(j*blockSize+offsetX,i*blockSize+offsetY+spaceY,pngFor);
                        break;
                    case 5:
                        painter.drawPixmap(j*blockSize+offsetX,i*blockSize+offsetY+spaceY,pngFiv);
                        break;
                    case 6:
                        painter.drawPixmap(j*blockSize+offsetX,i*blockSize+offsetY+spaceY,pngSix);
                        break;
                    case 7:
                        painter.drawPixmap(j*blockSize+offsetX,i*blockSize+offsetY+spaceY,pngSvn);
                        break;
                    case 8:
                        painter.drawPixmap(j*blockSize+offsetX,i*blockSize+offsetY+spaceY,pngEight);
                        break;
                    }
                }
                else
                {
                    qDebug() << "you lose" << endl;
                    //QMessageBox::about(this,"warning","You lose!");
                    painter.drawPixmap(j*blockSize+offsetX,i*blockSize+offsetY+spaceY,pngBomb);
                }
            }
                break;
            case REDFLAG:
                painter.drawPixmap(j*blockSize+offsetX,i*blockSize+offsetY+spaceY,pngRedFlag);
                break;
            default:
                break;
            }
        }
    }

}

void MainWindow::mousePressEvent(QMouseEvent *event)
{

    if(game->checkGame()==PLAYING)
    {
        int px = event->x() - offsetX;int py = event->y() - offsetY - spaceY;
        int row = py/blockSize; int col = px/blockSize;
        switch(event->button())
        {
        case Qt::LeftButton:
            game->dig(row,col);
            qDebug() << "dig:"<<row<<" "<<col<<endl;
            update();
            break;
        case Qt::RightButton:
            game->mark(row,col);
            qDebug() << "mark:"<<row<<" "<<col<<endl;
            update();
            break;
        default:
            break;
        }
    }
}

void MainWindow::startEasyGame()
{
    restart(8,15,20);
    level = EASY;
    setFixedSize(gameCol * blockSize + offsetX * 2, gameRow * blockSize + offsetY * 2 + spaceY);
    qDebug() << "easy mode" << endl;
}

void MainWindow::startMediumGame()
{
    restart(20,25,80);
    level = MEDIUM;
    setFixedSize(gameCol * blockSize + offsetX * 2, gameRow * blockSize + offsetY * 2 + spaceY);
    qDebug() << "medium mode" << endl;
}

void MainWindow::startHardGame()
{
    restart(30,45,100);
    level = HARD;
    setFixedSize(gameCol * blockSize + offsetX * 2, gameRow * blockSize + offsetY * 2 + spaceY);
    qDebug() << "hard mode" << endl;
}




