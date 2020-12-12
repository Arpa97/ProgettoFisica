#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    connect(advancingTimer, SIGNAL(timeout()), this, SLOT(updateAdvance()));
    ui->setupUi(this);
    original = drawOriginalgrid();
    rescale = ui->mainPicture->width() / (GRID_SIDE + .0);
}

QImage MainWindow::drawOriginalgrid(){
     QImage tmp = ui->mainPicture->pixmap(Qt::ReturnByValue).toImage();
     QPainter painter(&tmp);
     QPen paintpen(Qt::black);

     painter.setPen(paintpen);
     int step = GRID_SIDE / CELL_SIDE;
     double drawSize = CELL_SIDE * ui->mainPicture->width() / GRID_SIDE;

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

     ui->mainPicture->setPixmap(QPixmap::fromImage(tmp));
     return tmp;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateAdvance(){
    ncicli+=ADVANCE_DT;
    Foresta->advance(ADVANCE_DT);
    this->printFires();
}

void MainWindow::on_singleAdvanceButton_clicked()
{
    this->updateAdvance();
}

void MainWindow::mousePressEvent(QMouseEvent *event){
    int x = event->pos().x() - ui->mainPicture->x();
    int y = event->pos().y() - ui->mainPicture->y();
    if (0 < x && x < ui->mainPicture->width() && 0 < y && y < ui->mainPicture->height()){
        createNewFire((double)x, (double)y);
    }
}

void MainWindow::on_addFireButton_clicked()
{
    if (ui->mainPicture->hasMouseTracking()){
        ui->addFireButton->setText("Add fires");
        ui->mainPicture->setCursor(Qt::ArrowCursor);
        ui->mainPicture->setMouseTracking(false);
    } else {
        ui->addFireButton->setText("Stop adding fires");
        ui->mainPicture->setCursor(cursorTarget);
        ui->mainPicture->setMouseTracking(true);
    }
}

void MainWindow::createNewFire(double x, double y){
    Foresta->addFire(x * rescale, (GRID_SIDE - y) * rescale);
    this->printFires();
}

void MainWindow::printFires(){
    QImage canvas = QPixmap::fromImage(original).toImage();
    QPainter painter(&canvas);
    for (unsigned long long i = 0; i != Foresta->wildfire.size(); i++){
        ciclicVector<Vertex> polyFire = Foresta->getPolygon(i);
        QPen paintpen(Qt::red);
        QPolygon poly;

        for (unsigned long long i=0; i<polyFire.size(); i++){
            poly << QPoint(polyFire[i].x * rescale, (GRID_SIDE - polyFire[i].y) * rescale);
        }

        painter.setBrush(Qt::darkRed);
        painter.setPen(paintpen);
        painter.drawPolygon(poly);
     }
    ui->mainPicture->setPixmap(QPixmap::fromImage(canvas));
    ui->labelInfoTime->setText(QString("Time: ") + QString().number(ncicli) + QString("s"));
}

void MainWindow::on_startButton_clicked()
{
    ui->startButton->setText(advancingTimer->isActive() ? "Start" : "Stop");
    advancingTimer->isActive() ? advancingTimer->stop() : advancingTimer->start(10);
}

void MainWindow::on_exitButton_clicked()
{
    this->close();
}

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

void MainWindow::on_clearButton_clicked()
{
    ui->mainPicture->setPixmap(QPixmap::fromImage(original));
}
