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

    // Build empty forest
    buildForest();

    // Get fuel info
    fuelInfo = Foresta->getFuelInfo();

    for (Fuel* f : fuelInfo){
        fuelColors.push_back(0);
        if (f->name.compare("Nullo")){
            ui->fuelSelection->addItem(QString::fromUtf8(f->name.c_str()));
        }
    }

    // Set moisture to default value (also draws forest)
    ui->moistureSlider->setValue(DEFAULT_MOISTURE*10);
}

void MainWindow::addMountain(){
    // Test mountain
    double pos[2] = {200,200};
    int height = 10;
    int lar = 300;

    Foresta->addMountain(height, pos, lar);
}

void MainWindow::buildAndDraw(){
    if (ui->fuelList->findItems("*", Qt::MatchWildcard).isEmpty()){
         addSpecificFuel(DEFAULT_FUEL);
    }
    updateColors();
    buildForest();
    rescale = ui->mainPicture->width() / (GRID_SIDE + .0);
    original = drawOriginalgrid();
}

double MainWindow::getFuelIndex(QString fuelName){
    for (int i=0; i < int(fuelInfo.size()); i++){
        //qDebug() << QString().number(i);
        if (!fuelName.compare(QString::fromUtf8(fuelInfo[i]->name.c_str()))){
            return i;
        }
    }
    return -1;
}

void MainWindow::buildForest(){
    // set elapsed time to 0
    ncicli = 0;
    ui->labelInfoTime->setText(QString("Elapsed time: ") + QString().number(ncicli) + QString("s"));

    // build forest
    std::vector<std::vector<double>> composizione;
    QList<QListWidgetItem*> fuelsList = ui->fuelList->findItems("*", Qt::MatchWildcard);
    if (fuelsList.isEmpty()){
        Foresta = new Environment(composizione, ui->moistureSlider->value()/10.0);
    }
    else {
        int differentFuels = fuelsList.size();
        double fraction = 1.0/differentFuels;
        for(int i = 0; i < differentFuels; i++){
            std::vector<double> toadd = {getFuelIndex(fuelsList.takeFirst()->text()), fraction};
            composizione.push_back(toadd);
        }
        Foresta = new Environment(composizione, ui->moistureSlider->value()/10.0);
    }
    // Method to add single predefined mountain
    addMountain();
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

double MainWindow::getOpacity(double height){
    if (ui->invertCheckBox->isChecked()){
        return height/MAX_HEIGHT;
    } else {
        return 1-height/MAX_HEIGHT;
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

     // clears previous drawings
     painter.setBrush(Qt::white);
     painter.setOpacity(1);
     painter.drawRect(0, 0, GRID_SIDE, GRID_SIDE);

     int step = GRID_SIDE / CELL_SIDE;
     double drawSize = CELL_SIDE * rescale;

     for (int i = 0; i != step; i++)
     {
         for (int j = 0; j != step; j++)
         {
             // draw new square
             painter.setBrush(getBrushColor(Foresta->grid[i][j]->fuelNumber));
             painter.setOpacity(getOpacity(Foresta->grid[i][j]->height));
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
        stopAddingFires();
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
      stopAddingFires();
      toggleFuelsPanel();
      advancingTimer->isActive() ? ui->moistureSlider->setDisabled(false) : ui->moistureSlider->setDisabled(true);
      advancingTimer->isActive() ? advancingTimer->stop() : advancingTimer->start();
    }
}

void MainWindow::toggleFuelsPanel(){
    stopDrawingFuel();
    ui->addFuel->isEnabled() ? ui->addFuel->setEnabled(false) : ui->addFuel->setEnabled(true);
    ui->removeFuel->isEnabled() ? ui->removeFuel->setEnabled(false) : ui->removeFuel->setEnabled(true);
    ui->removeAllFuels->isEnabled() ? ui->removeAllFuels->setEnabled(false) : ui->removeAllFuels->setEnabled(true);
    ui->drawFuelButton->isEnabled() ? ui->drawFuelButton->setEnabled(false) : ui->drawFuelButton->setEnabled(true);
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
    //qDebug() << "winDir" << QString().number(newTheta);
}

void MainWindow::on_windSpeed_valueChanged(int value)
{
  double newSpeed = (double)value*MAXWINDSPEED/100;
  ui->windSpeedLabel->setText(QString("Speed: ") + QString().number(newSpeed) + QString(" m/s"));
  ui->Wind_Description->setText(getWindClassification(newSpeed));
  Foresta->setU(newSpeed);
  //qDebug() << "winSpeed" << newSpeed;
}

QString MainWindow::getWindClassification(double speed){
  if (speed >= 0 && speed < 0.5) return "Calm:\nSmoke rises vertically";
  else if (speed >= 0.5 && speed <= 1.5) return "Light Air:\nSmoke drifts with air,\nweather vanes inactive";
  else if (speed > 1.5 && speed <= 3) return "Light Breeze:\nWeather vanes active,\nwind felt on face, leaves rustle";
  else if (speed > 3 && speed <= 5) return "Gentle Breeze:\nLeaves & small twigs move,\nlight flags extend";
  else if (speed > 5 && speed <= 8) return "Moderate Breeze:\nSmall branches sway,\ndust & loose paper blows about";
  else if (speed > 8 && speed <= 10.5) return "Fresh Breeze:\nSmall trees sway,\nwaves break on inland waters";
  else if (speed > 10.5 && speed <= 13.5) return "Strong Breeze:\nLarge branches sway,\numbrellas difficult to use";
  else if (speed > 13.5 && speed <= 16.5) return "Moderate Gale:\nWhole trees sway,\ndifficult to walk against wind";
  else if (speed > 16.5 && speed <= 20) return "Fresh Gale:\nTwigs broken off trees,\nwalking against wind very difficult";
  else if (speed > 20 && speed <= 23.5) return "Strong Gale:\nSlight damage to buildings,\nshingles blown off roof";
  else if (speed > 23.5 && speed <= 27.5) return "Whole Gale:\nTrees uprooted,\nconsiderable damage to buildings";
  else if (speed > 27.5 && speed <= 31.5) return "Storm:\nWidespread damage,\nvery rare occurrence";
  else if (speed > 31.5) return "Hurricane:\nViolent destruction";
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

void MainWindow::addSpecificFuel(QString selectedFuel){
    QList<QListWidgetItem*> items = ui->fuelList->findItems(selectedFuel, Qt::MatchExactly);
    if (items.isEmpty() && ui->fuelList->count() < 5){
        ui->fuelList->addItem(selectedFuel);
        buildAndDraw();
    }
}

void MainWindow::on_addFuel_clicked()
{
    addSpecificFuel(ui->fuelSelection->currentText());
}

void MainWindow::on_removeFuel_clicked()
{
    //QString selectedFuel = ui->fuelSelection->currentText();
    //QList<QListWidgetItem*> items = ui->fuelList->findItems(selectedFuel, Qt::MatchExactly);
    QListWidgetItem* current = ui->fuelList->currentItem();
    if (current) {
        // remove item from the list using "takeItem" while setting its colour to 0
        fuelColors[getFuelIndex(ui->fuelList->takeItem(ui->fuelList->row(current))->text())] = 0;
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
    //qDebug() << "simSpeed" << value;
}

void MainWindow::on_drawFuelButton_clicked()
{
    if (ui->mainPicture->hasMouseTracking()){
        stopDrawingFuel();
    } else {
        ui->drawFuelButton->setText("Stop drawing fuels");
        ui->mainPicture->setCursor(Qt::UpArrowCursor);
        ui->mainPicture->setMouseTracking(true);
        ui->addFireButton->setDisabled(true);
        drawingFuels = true;
    }
}

void MainWindow::stopDrawingFuel(){
    if (drawingFuels){
        ui->drawFuelButton->setText("Draw selected fuel");
        ui->mainPicture->setCursor(Qt::ArrowCursor);
        ui->mainPicture->setMouseTracking(false);
        ui->addFireButton->setDisabled(false);
        drawingFuels = false;
    }
}

void MainWindow::stopAddingFires(){
    if (addingFires){
        ui->addFireButton->setText("Add fires");
        ui->mainPicture->setCursor(Qt::ArrowCursor);
        ui->mainPicture->setMouseTracking(false);
        if(!advancingTimer->isActive()){
            ui->drawFuelButton->setDisabled(false);
        }
        addingFires = false;
    }
}

//Progress Bar Functions
void MainWindow::on_progressBar_advancing(Environment* Forest){
  QProgressBar* bar = ui->progressBar;
  double Burned = Forest->getBurnedArea();
  double Total = GRID_SIDE*GRID_SIDE;
  double Val = (Burned/Total);
  double Percentage = Val*100;
  //qDebug() << "Bruciato " << (int)(Percentage * 100);
  //bar->setFormat(QString("%1%").arg(Percentage, 0, 'f', 2));
  bar->setFormat(QString("%1 ha").arg(Burned*1e-4, 0, 'f', 2));     //m2 to hectares
  bar->setValue((int)(Percentage*100));
}

void MainWindow::on_removeAllFuels_clicked()
{
    QList<QListWidgetItem*> fuelsList = ui->fuelList->findItems("*", Qt::MatchWildcard);
    if (!fuelsList.isEmpty()) {
        while (!fuelsList.isEmpty()){
            // remove item from the list using "takeItem" while setting its colour to 0
            fuelColors[getFuelIndex(ui->fuelList->takeItem(ui->fuelList->row(fuelsList.takeFirst()))->text())] = 0;
        }
        buildAndDraw();
    }
}

void MainWindow::on_moistureSlider_valueChanged(int value)
{
    ui->moistureSlider->setDisabled(true);
    ui->moistureLabelValue->setText(QString("Moisture: ") + QString().number(value/10.0));
    buildAndDraw();
    ui->moistureSlider->setDisabled(false);
}

void MainWindow::on_invertCheckBox_stateChanged(int arg1)
{
    original = drawOriginalgrid();
}
