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
    QImage tmp = ui->label->pixmap()->toImage();
    QPainter painter(&tmp);
    QPen paintpen(Qt::red);

    QPolygon poly;

    for (int i=0; i<=10; i++){
        ncicli++;
        Foresta.advance();
    }
    ciclicVector<Vertex> polyFire = Foresta.getPolygon(0);

    for (int i=0; i<polyFire.size(); i++){
        //qDebug() << polyFire[i].x << polyFire[i].y;
        poly << QPoint(200-polyFire[i].x, 200-polyFire[i].y);
    }

    painter.setBrush(Qt::red);
    painter.setPen(QPen(Qt::red));
    painter.drawPolygon(poly);

    ui->label->setPixmap(QPixmap::fromImage(tmp));
    ui->label_2->setText(QString("Ciclo: ") + QString().number(ncicli));
}

void MainWindow::on_pushButton_2_clicked()
{
    Foresta.addFire(50, 50);
    ciclicVector<Vertex> polyFire = Foresta.getPolygon(0);

    /*for (int i=0; i<polyFire.size(); i++){
        qDebug() << polyFire[i].x << polyFire[i].y;
    }*/
}
