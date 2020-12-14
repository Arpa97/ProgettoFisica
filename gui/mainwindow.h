#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMessageBox>
#include <QMainWindow>
#include <QPainter>
#include <QDebug>
#include <QTimer>
#include <QCursor>
#include <QMouseEvent>
#include "Environment.hxx"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    double rescale;
    QImage original;
    QCursor cursorTarget = QCursor(QPixmap(":/cursortarget.png"));
    Environment* Foresta;
    QTimer *advancingTimer = new QTimer();
    double ADVANCE_DT = 1;
    int ncicli = 0;
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void mousePressEvent(QMouseEvent *event);
    void on_singleAdvanceButton_clicked();
    void on_addFireButton_clicked();
    void printFires();
    void on_startButton_clicked();
    void updateAdvance();
    void on_exitButton_clicked();
    //void on_windSpeed_sliderMoved(int position);
    void on_windDir_valueChanged(int position);
    void on_windSpeed_valueChanged(int value);
    void createNewFire(double x, double y);
    void on_clearButton_clicked();
    QImage drawOriginalgrid();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
