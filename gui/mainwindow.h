#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QDebug>
#include <QTimer>

#include "Environment.hxx"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    Environment Foresta;
    QTimer *advancingTimer = new QTimer();
    double ADVANCE_DT = 1;
    int ncicli = 0;
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void printFire(ciclicVector<Vertex>);

    void on_pushButton_3_clicked();

    void updateAdvance();

    void on_pushButton_4_clicked();

    void on_windSpeed_sliderMoved(int position);

    void on_windDir_sliderMoved(int position);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
