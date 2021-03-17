#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    connect(advancingTimer, SIGNAL(timeout()), this, SLOT(updateAdvance()));
    advancingTimer->setInterval(1000); // starting timer with 1 sec delay

    ui->setupUi(this);

    buildAndDraw();

    //double pos[2]{ 75, 75 }, pos1[2]{ 50, 70 };

    //Foresta->addMountain(10, pos, 1000);
    //Foresta->addMountain(10, pos1, 100);
}

void MainWindow::buildAndDraw(){
    buildForest();
    rescale = ui->mainPicture->width() / (GRID_SIDE + .0);
    original = drawOriginalgrid();
}

void MainWindow::buildForest(){
    std::vector<std::vector<double>> composizione;
    QList<QListWidgetItem*> fuelsList = ui->fuelList->findItems("*", Qt::MatchWildcard);
    if (fuelsList.isEmpty()){
        Foresta = new Environment(composizione);
    }
    else {
        int differentFuels = fuelsList.size();
        double fraction = 1.0/differentFuels;
        for(int i = 0; i < differentFuels; i++){
            std::vector<double> toadd = {fuelsList.takeFirst()->text().toDouble(), fraction};
            composizione.push_back(toadd);
        }
        Foresta = new Environment(composizione);
    }
}

QColor MainWindow::getBrushColor(int fuelNumber){
    switch (fuelNumber) {
        case 1: return Qt::green;
        case 2: return Qt::darkGreen;
        case 3: return Qt::gray;
        case 4: return Qt::darkGray;
        case 5: return Qt::lightGray;
        default: return Qt::black;
    }
}

QImage MainWindow::drawOriginalgrid(){
     QImage tmp = ui->mainPicture->pixmap()->toImage();
     QPainter painter(&tmp);
     QPen paintpen(Qt::black);

     painter.setPen(paintpen);
     int step = GRID_SIDE / CELL_SIDE;
     double drawSize = CELL_SIDE * rescale;

     for (int i = 0; i != step; i++)
         {
             for (int j = 0; j != step; j++)
             {
                 painter.setBrush(getBrushColor(Foresta->grid[i][j]->fuelNumber));
                 painter.drawRect(i * drawSize, (GRID_SIDE * rescale) - (j + 1) * drawSize, drawSize, drawSize);
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
    //qDebug() << Foresta->wildfire[0]->area;
}

void MainWindow::on_singleAdvanceButton_clicked()
{
    this->updateAdvance();
}

void MainWindow::mousePressEvent(QMouseEvent *event){
  if(ui->mainPicture->hasMouseTracking()){
      int x = event->pos().x() - ui->mainPicture->x();
      int y = event->pos().y() - ui->mainPicture->y();
      if (0 < x && x < ui->mainPicture->width() && 0 < y && y < ui->mainPicture->height()){
          createNewFire((double)x, (double)y);
      }
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
    if (FIXED_FIRE)
    {
        //x = rescale * GRID_SIDE / 2;
        //y = rescale * GRID_SIDE / 2;
        x = rescale*5;
        y = rescale*5;
    }
    Foresta->addFire(x / rescale, (GRID_SIDE - y / rescale));
    this->printFires();
}

void MainWindow::printFires(){
    QImage canvas = QPixmap::fromImage(original).toImage();
    QPainter painter(&canvas);
    for (unsigned long long i = 0; i != Foresta->wildfire.size(); i++){
        ciclicVector<Vertex> polyFire = Foresta->getPolygon(i);
        QPen paintpen(Qt::red);
        QPolygon poly;
        
        QPoint* points = new QPoint[polyFire.size()];

        for (unsigned long long i=0; i<polyFire.size(); i++){
            points[i] = QPoint(polyFire[i].x * rescale, (GRID_SIDE - polyFire[i].y) * rescale);
            poly << points[i];
        }

        painter.setBrush(Qt::darkRed);
        painter.setPen(paintpen);
        painter.drawPolygon(poly);

        QPen linepen(Qt::black);
        linepen.setCapStyle(Qt::SquareCap);
        linepen.setWidth(8);
        
        painter.setPen(linepen);
        for (int i = 0; i != polyFire.size(); i++)
        {
            //if (i == 0)
            //{
            //    linepen.setColor(Qt::blue);
            //    painter.setPen(linepen);
            //    painter.drawPoint(points[i]);
            //    linepen.setColor(Qt::black);
            //    painter.setPen(linepen);
            //    continue;
            //}
            painter.drawPoint(points[i]);
        }
    }
    ui->mainPicture->setPixmap(QPixmap::fromImage(canvas));
    ui->labelInfoTime->setText(QString("Elapsed time: ") + QString().number(ncicli) + QString("s"));
}

void MainWindow::on_startButton_clicked()
{
  if (Foresta->wildfire.size()<1){
      qWarning() << "No fire added...";
      QMessageBox::warning(this, tr("Attention"),tr("You should add a fire before starting the simulation"));
    }
  else{
      ui->addFireButton->setText("Add fires");
      ui->mainPicture->setCursor(Qt::ArrowCursor);
      ui->mainPicture->setMouseTracking(false);
      ui->startButton->setText(advancingTimer->isActive() ? "Start" : "Stop");
      advancingTimer->isActive() ? advancingTimer->stop() : advancingTimer->start();
    }
}

void MainWindow::on_exitButton_clicked()
{
    this->close();
}

void MainWindow::on_windDir_valueChanged(int position)
{
    double newTheta = (double)position/100;
    ui->windDirLabel->setText(QString("Angle: ") + QString().number(newTheta) + QString(" rad"));
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
    if (advancingTimer->isActive()){
      ui->startButton->click();
    }
    ui->mainPicture->setPixmap(QPixmap::fromImage(original));
    //pulire vettore wildfire
    Foresta->wildfire.clear();
    //stoppare esecuzione
    ncicli=0;
    ui->labelInfoTime->setText(QString("Elapsed time: ") + QString().number(ncicli) + QString("s"));
}

void MainWindow::on_addFuel_clicked()
{
    QString selectedFuel = ui->fuelSelection->currentText();
    QList<QListWidgetItem*> items = ui->fuelList->findItems(selectedFuel, Qt::MatchExactly);
    if (items.isEmpty()){
        ui->fuelList->addItem(selectedFuel);
    }
    buildAndDraw();
}

void MainWindow::on_pushButton_clicked()
{
    QString selectedFuel = ui->fuelSelection->currentText();
    QList<QListWidgetItem*> items = ui->fuelList->findItems(selectedFuel, Qt::MatchExactly);
    if (!items.isEmpty()) {
        while (!items.isEmpty()){
            ui->fuelList->takeItem(ui->fuelList->row(items.takeFirst()));
        }
        buildAndDraw();
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    buildAndDraw();
}

void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    ui->simulationSpeedLabel->setText(QString("Simulation: ") + QString().number(value) + QString("x"));
    advancingTimer->setInterval(1000/value);
    qDebug() << "simSpeed" << value;
}

void MainWindow::on_pushButton_3_clicked()
{

}
