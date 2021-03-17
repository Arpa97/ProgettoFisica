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
    bool addingFires = false;
    bool drawingFuels = false;
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // custom methods
    void printFires();
    void updateAdvance();
    void createNewFire(double x, double y);
    QImage drawOriginalgrid();
    QColor getBrushColor(int fuelNumber);
    void buildForest();
    void buildAndDraw();

    // events
    void mousePressEvent(QMouseEvent *event);
    void on_singleAdvanceButton_clicked();
    void on_addFireButton_clicked();
    void on_startButton_clicked();
    void on_exitButton_clicked();
    void on_windDir_valueChanged(int position);
    void on_windSpeed_valueChanged(int value);
    void on_clearButton_clicked();
    void on_addFuel_clicked();
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_horizontalSlider_valueChanged(int value);
    void on_drawFuelButton_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
