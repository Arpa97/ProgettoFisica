#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    connect(advancingTimer, SIGNAL(timeout()), this, SLOT(updateAdvance()));
    ui->setupUi(this);
    original = ui->label->pixmap()->toImage();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateAdvance(){
    ncicli+=ADVANCE_DT;
    Foresta->advance(ADVANCE_DT);
    for (int i = 0; i != Foresta->wildfire.size(); i++){
        this->printFire(Foresta->getPolygon(i));
    }
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
    for (int i = 0; i != Foresta->wildfire.size(); i++){
        this->printFire(Foresta->getPolygon(i));
    }
}

void MainWindow::printFire(ciclicVector<Vertex> polyFire){
    QImage tmp = QPixmap::fromImage(original).toImage();
    QPainter painter(&tmp);
    QPen paintpen(Qt::red);
    QPolygon poly;

    for (int i=0; i<polyFire.size(); i++){
        poly << QPoint(polyFire[i].x, GRID_SIDE-polyFire[i].y);
        //qDebug() << polyFire[i].x << polyFire[i].y;
    }

    painter.setBrush(Qt::red);
    painter.setPen(QPen(Qt::red));
    painter.drawPoints(poly);

    ui->label->setPixmap(QPixmap::fromImage(tmp));
    ui->label_2->setText(QString("Time: ") + QString().number(ncicli) + QString("s"));
}

void MainWindow::on_pushButton_3_clicked()
{
    ui->pushButton_3->setText(advancingTimer->isActive() ? "Start" : "Stop");
    advancingTimer->isActive() ? advancingTimer->stop() : advancingTimer->start(1000);
}

void MainWindow::on_pushButton_4_clicked()
{
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
}
