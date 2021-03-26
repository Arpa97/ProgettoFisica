#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    // INITIALIZATION
    // ----------------------------- //

    // Setup timer
    connect(advancingTimer, SIGNAL(timeout()), this, SLOT(updateAdvance()));
    advancingTimer->setInterval(1000/400); // starting timer with 1/400 sec delay

    // Setup ui
    ui->setupUi(this);

    // Build and draw forest
    buildAndDraw();

    // Get fuel info
    fuelInfo = Foresta->getFuelInfo();

    for (Fuel* f : fuelInfo){
        fuelColors.push_back(0);
        if (f->name.compare("Nullo")){
            ui->fuelSelection->addItem(QString::fromUtf8(f->name.c_str()));
        }
    }
}

void MainWindow::buildAndDraw(){
    updateColors();
    buildForest();
    rescale = ui->mainPicture->width() / (GRID_SIDE + .0);
    original = drawOriginalgrid();
}

double MainWindow::getFuelIndex(QString fuelName){
    for (double i=0; i < fuelInfo.size();i++){
        qDebug() << QString().number(i);
        if (!fuelName.compare(QString::fromUtf8(fuelInfo[i]->name.c_str()))){
            return i;
        }
    }
    return -1;
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
            std::vector<double> toadd = {getFuelIndex(fuelsList.takeFirst()->text()), fraction};
            composizione.push_back(toadd);
        }
        Foresta = new Environment(composizione);
    }
}

void MainWindow::updateColors(){
    QList<QListWidgetItem*> fuelsList = ui->fuelList->findItems("*", Qt::MatchWildcard);
    int differentFuels = fuelsList.size();
    for (int idx = 0; idx < differentFuels; idx++){
        QListWidgetItem* item = fuelsList.takeFirst();
        int fuelIndex = getFuelIndex(item->text());
        fuelColors[fuelIndex] = idx+1;
        item->setForeground(getBrushColor(fuelIndex));
    }
}

QColor MainWindow::getBrushColor(int fuelNumber){
    int n = 0;
    if (int(fuelColors.size()) > fuelNumber){
        n = fuelColors[fuelNumber];
    }

    switch (n) {
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
    on_progressBar_advancing(Foresta);
    this->printFires();
    //qDebug() << Foresta->wildfire[0]->area;
}

void MainWindow::on_singleAdvanceButton_clicked()
{
    this->updateAdvance();
}

// MOUSE EVENTS
void MainWindow::mouseMoveEvent(QMouseEvent *event){
    if(ui->mainPicture->hasMouseTracking()){
        if(drawingFuels){
              drawFuel(event);
          }
    }
}

void MainWindow::mousePressEvent(QMouseEvent *event){
  if(ui->mainPicture->hasMouseTracking()){
      if(addingFires){
          int x = event->pos().x() - ui->mainPicture->x();
          int y = event->pos().y() - ui->mainPicture->y();
          if (0 < x && x < ui->mainPicture->width() && 0 < y && y < ui->mainPicture->height()){
              createNewFire((double)x, (double)y);
          }
      }
      else if(drawingFuels){
          drawFuel(event);
      }
    }
}

void MainWindow::drawFuel(QMouseEvent *event){
    double fuelNumber;
    int x = event->pos().x() - ui->mainPicture->x();
    int y = event->pos().y() - ui->mainPicture->y();
    if (0 < x && x < ui->mainPicture->width() && 0 < y && y < ui->mainPicture->height()){
        QListWidgetItem* current = ui->fuelList->currentItem();
        if(current){
           //current->text().toInt();
          fuelNumber = getFuelIndex(current->text());
          double xcell = x / rescale;
          double ycell = (GRID_SIDE - y / rescale);
          Foresta->setCellType(xcell, ycell, fuelNumber);
          original = drawOriginalgrid();
        }
    }
}

void MainWindow::on_addFireButton_clicked()
{

    if (ui->mainPicture->hasMouseTracking()){
        if (addingFires){
            ui->addFireButton->setText("Add fires");
            ui->mainPicture->setCursor(Qt::ArrowCursor);
            ui->mainPicture->setMouseTracking(false);
            ui->drawFuelButton->setDisabled(false);
            addingFires = false;
        }
    } else {
        ui->addFireButton->setText("Stop adding fires");
        ui->mainPicture->setCursor(cursorTarget);
        ui->mainPicture->setMouseTracking(true);
        ui->drawFuelButton->setDisabled(true);
        addingFires = true;
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
        for (int i = 0; i != int(polyFire.size()); i++)
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
    if (items.isEmpty() && ui->fuelList->count() < 5){
        ui->fuelList->addItem(selectedFuel);
        buildAndDraw();
    }
}

void MainWindow::on_removeFuel_clicked()
{
    QString selectedFuel = ui->fuelSelection->currentText();
    QList<QListWidgetItem*> items = ui->fuelList->findItems(selectedFuel, Qt::MatchExactly);
    if (!items.isEmpty()) {
        while (!items.isEmpty()){
            // remove item from the list using "takeItem" while setting its colour to 0
            fuelColors[getFuelIndex(ui->fuelList->takeItem(ui->fuelList->row(items.takeFirst()))->text())] = 0;
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
void MainWindow::on_drawFuelButton_clicked()
{

    if (ui->mainPicture->hasMouseTracking()){
        if (drawingFuels){
            ui->drawFuelButton->setText("Draw selected fuel");
            ui->addFireButton->setDisabled(false);
            ui->mainPicture->setCursor(Qt::ArrowCursor);
            ui->mainPicture->setMouseTracking(false);
            drawingFuels = false;
        }
    } else {
        ui->drawFuelButton->setText("Stop drawing fuels");
        ui->mainPicture->setCursor(Qt::UpArrowCursor);
        ui->mainPicture->setMouseTracking(true);
        ui->addFireButton->setDisabled(true);
        drawingFuels = true;
    }
}

//Progress Bar Functions
void MainWindow::on_progressBar_advancing(Environment* Forest){
  QProgressBar* bar = ui->progressBar;
  double Burned = Forest->getBurnedArea();
  double Total = GRID_SIDE*GRID_SIDE;
  double Val = (Burned/Total);
  double Percentage = Val*100;
  qDebug() << "Bruciato " << (int)(Percentage * 100);
  bar->setFormat(QString("%1%").arg(Percentage, 0, 'f', 2));
  bar->setValue((int)(Percentage*100));
}
