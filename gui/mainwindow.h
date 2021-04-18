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

# include <iostream>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    std::vector<Fuel*> fuelInfo;
    std::vector<int> fuelColors;
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

    // get the brush color corresponding to a fuel index
    QColor getBrushColor(int fuelNumber);

    // builds the forest
    void buildForest();

    // builds the forest and draw it on the canvas
    void buildAndDraw();

    // gets the index from the fuel name
    double getFuelIndex(QString fuelName);
    // update colors used to draw fuels
    void updateColors();

    // toggle fuels panel, allowing or not changes
    void toggleFuelsPanel();

    // if fuel drawing is enabled, stop it
    void stopDrawingFuel();

    // if fires adding is enabled, disables it
    void stopAddingFires();

    //add specific fuel to the list
    void addSpecificFuel(QString selectedFuel);

    // mouse events
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void drawFuel(QMouseEvent *event);

    // events
    void on_singleAdvanceButton_clicked();
    void on_addFireButton_clicked();
    void on_startButton_clicked();
    void on_exitButton_clicked();
    void on_windDir_valueChanged(int position);
    void on_windSpeed_valueChanged(int value);
    void on_clearButton_clicked();
    void on_addFuel_clicked();
    void on_removeFuel_clicked();
    void on_pushButton_2_clicked();
    void on_horizontalSlider_valueChanged(int value);
    void on_drawFuelButton_clicked();
    void on_progressBar_advancing(Environment* Forest);

    void on_removeAllFuels_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
