#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <chrono>
#include <iostream>
#include <vector>
#include <Fire.hxx>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    connect(advancingTimer, SIGNAL(timeout()), this, SLOT(updateAdvance()));
    ui->setupUi(this);
    original = drawOriginalgrid();
}

QImage MainWindow::drawOriginalgrid(){
     QImage tmp = ui->label->pixmap(Qt::ReturnByValue).toImage();
     QPainter painter(&tmp);
     QPen paintpen(Qt::black);

     painter.setPen(paintpen);
     int step = GRID_SIDE / CELL_SIDE;
     double drawSize = CELL_SIDE * ui->label->width() / GRID_SIDE;

     for (int i = 0; i != step; i++)
         {
             for (int j = 0; j != step; j++)
             {
                 if (Foresta->grid[i][j]->fuelIndex == 1) painter.setBrush(Qt::green);
                 else if (Foresta->grid[i][j]->fuelIndex == 13) painter.setBrush(Qt::darkGreen);
                 else if (Foresta->grid[i][j]->fuelIndex == 7) painter.setBrush(Qt::gray);
                 else painter.setBrush(Qt::gray);
                 painter.drawRect(i * drawSize, j * drawSize, drawSize, drawSize);
             }
         }

     ui->label->setPixmap(QPixmap::fromImage(tmp));
     return tmp;
}

MainWindow::~MainWindow()
{
    delete ui;
}

std::chrono::steady_clock::time_point begin;
void MainWindow::updateAdvance(){
    ncicli+=ADVANCE_DT;
    Foresta->advance(ADVANCE_DT);
    //Foresta->advance_withoutHeap();
    for (unsigned long long i = 0; i != Foresta->wildfire.size(); i++){
        this->printFire(Foresta->getPolygon(i));
    }
    //std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    //std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << std::endl;
    //std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count() << "[ns]" << std::endl;
}

void MainWindow::on_pushButton_clicked()
{
    this->updateAdvance();
}

void MainWindow::on_pushButton_2_clicked()
{
    int x = ui->xfire->text().toDouble();
    int y = ui->yfire->text().toDouble();
    Foresta->addFire(x, y);
    for (unsigned long long i = 0; i != Foresta->wildfire.size(); i++){
        this->printFire(Foresta->getPolygon(i));
    }
}

void MainWindow::printFire(ciclicVector<Vertex> polyFire){
    QImage tmp = QPixmap::fromImage(original).toImage();
    QPainter painter(&tmp);
    QPen paintpen(Qt::red);
    QPolygon poly;

    QPen linepen(Qt::black);
    linepen.setCapStyle(Qt::RoundCap);
    linepen.setWidth(5);


    double rescale = ui->label->width() / (GRID_SIDE + .0);
    static std::vector<QPoint*> points;
    static int iteration = 0;
    points.push_back(new QPoint[polyFire.size()]);

    for (unsigned long long i=0; i<polyFire.size(); i++){
        points[iteration][i] = QPoint(polyFire[i].x * rescale, (GRID_SIDE - polyFire[i].y) * rescale);
        poly << points[iteration][i];
        //qDebug() << polyFire[i].x * rescale << (GRID_SIDE - polyFire[i].y) * rescale;
    }

    painter.setBrush(Qt::darkRed);
    painter.setPen(paintpen);
    //painter.drawPoints(poly);
    painter.drawPolygon(poly);

    painter.setPen(linepen);
    for (int i = 0; i != polyFire.size(); i++)
    {   
        for (int j = 1+iteration-1; j != iteration+1; j++)
        {
            painter.drawPoint(points[j][i]);
        }
    }
    iteration++;

    ui->label->setPixmap(QPixmap::fromImage(tmp));
    ui->label_2->setText(QString("Time: ") + QString().number(ncicli) + QString("s"));
}

void MainWindow::on_pushButton_3_clicked()
{
    begin = std::chrono::steady_clock::now();
    if (Foresta->wildfire.empty())
    {
        on_pushButton_2_clicked();
    }
    ui->pushButton_3->setText(advancingTimer->isActive() ? "Start" : "Stop");
    advancingTimer->isActive() ? advancingTimer->stop() : advancingTimer->start();
}

void MainWindow::on_pushButton_4_clicked()
{
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << std::endl;
    this->close();
}

/*
void MainWindow::on_windSpeed_sliderMoved(int position)
{
    double newSpeed = (double)position*MAXWINDSPEED/100;
    ui->windSpeedLabel->setText(QString("Speed: ") + QString().number(newSpeed) + QString(" m/s"));
    Foresta->setU(newSpeed);
    qDebug() << "winSpeed" << newSpeed;
}
*/
void MainWindow::on_windDir_valueChanged(int position)
{
    double newTheta = (double)position/100;
    ui->windDirLabel->setText(QString("Angle: ") + QString().number(newTheta) + QString(" radianti"));
    Foresta->setTheta(newTheta);
    qDebug() << "winDir" << QString().number(newTheta);
}

void MainWindow::on_windSpeed_valueChanged(int value)
{
  double newSpeed = (double)value*MAXWINDSPEED/100;
  ui->windSpeedLabel->setText(QString("Speed: ") + QString().number(newSpeed) + QString(" m/s"));
  Foresta->setU(newSpeed);
  qDebug() << "winSpeed" << newSpeed;
}

void MainWindow::on_pushButton_5_clicked()
{
    ui->label->setPixmap(QPixmap::fromImage(original));
    Foresta->wildfire = std::vector<Fire*>();
}
