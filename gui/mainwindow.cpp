#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    ncicli+=TIMESTEP;
    Foresta.advance();
    this->printFire(Foresta.getPolygon(0));
}

void MainWindow::on_pushButton_2_clicked()
{
    Foresta.addFire(50, 50);
    this->printFire(Foresta.getPolygon(0));
}

void MainWindow::printFire(ciclicVector<Vertex> polyFire){
    QImage tmp = ui->label->pixmap()->toImage();
    QPainter painter(&tmp);
    QPen paintpen(Qt::red);
    QPolygon poly;

    for (int i=0; i<polyFire.size(); i++){
        poly << QPoint(polyFire[i].x, GRID_SIDE-polyFire[i].y);
    }

    painter.setBrush(Qt::red);
    painter.setPen(QPen(Qt::red));
    painter.drawPoints(poly);

    ui->label->setPixmap(QPixmap::fromImage(tmp));
    ui->label_2->setText(QString("Ciclo: ") + QString().number(ncicli));
}
