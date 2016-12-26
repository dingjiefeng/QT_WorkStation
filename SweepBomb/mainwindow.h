#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QPixmap>
#include <QSize>
#include <QDebug>
#include <QPainter>
#include "block.h"
#include <QMouseEvent>
#include <QTimer>
#include <QMessageBox>
using namespace std;
namespace Ui {
class MainWindow;
}

enum gameLevel{
    EASY,
    MEDIUM,
    HARD
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void restart(int theRow,int theCol,int theTotalBomb);
protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
protected:
    QLabel *label1 = new QLabel(this);
    QLabel *label2 = new QLabel(this);
    QPixmap *pix = new QPixmap;
    int gameRow;
    int gameCol;// = 15;
    int spaceY = 40;
    int blockSize = 30;
    int offsetX = 40;
    int offsetY = 20;
private:
    Ui::MainWindow *ui;
    block *game = new block;
    gameLevel level;
private slots:
    void startEasyGame();
    void startMediumGame();
    void startHardGame();
};

#endif // MAINWINDOW_H
