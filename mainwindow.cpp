#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene = new QGraphicsScene;

    ui->graphicsView->setScene(scene);
    generator = NULL;

    connect(&kolorki, SIGNAL(colorSelected(QColor)), this, SLOT(zmianaKoloru(QColor)));

    connect(ui->pushButtonLT, SIGNAL(clicked()), this, SLOT(getColorDialog()));
    connect(ui->pushButtonRT, SIGNAL(clicked()), this, SLOT(getColorDialog()));
    connect(ui->pushButtonLB, SIGNAL(clicked()), this, SLOT(getColorDialog()));
    connect(ui->pushButtonRB, SIGNAL(clicked()), this, SLOT(getColorDialog()));

    connect(ui->horizontalSlider, SIGNAL(valueChanged(int)), this, SLOT(zmianaJakosci(int)));

    connect(ui->spinBoxHeight, SIGNAL(editingFinished()),this,  SLOT(showPrieview()));
    connect(ui->spinBoxWidth, SIGNAL(editingFinished()),this,  SLOT(showPrieview()));

    connect(ui->spinBoxRTR, SIGNAL(editingFinished()),this,  SLOT(showPrieview()));
    connect(ui->spinBoxRTB, SIGNAL(editingFinished()),this,  SLOT(showPrieview()));
    connect(ui->spinBoxRTG, SIGNAL(editingFinished()),this,  SLOT(showPrieview()));

    connect(ui->spinBoxLTR, SIGNAL(editingFinished()),this,  SLOT(showPrieview()));
    connect(ui->spinBoxLTG, SIGNAL(editingFinished()),this,  SLOT(showPrieview()));
    connect(ui->spinBoxLTB, SIGNAL(editingFinished()),this,  SLOT(showPrieview()));

    connect(ui->spinBoxRBR, SIGNAL(editingFinished()),this,  SLOT(showPrieview()));
    connect(ui->spinBoxRBG, SIGNAL(editingFinished()),this,  SLOT(showPrieview()));
    connect(ui->spinBoxRBB, SIGNAL(editingFinished()),this,  SLOT(showPrieview()));

    connect(ui->spinBoxLBR, SIGNAL(editingFinished()),this,  SLOT(showPrieview()));
    connect(ui->spinBoxLBG, SIGNAL(editingFinished()),this,  SLOT(showPrieview()));
    connect(ui->spinBoxLBB, SIGNAL(editingFinished()),this,  SLOT(showPrieview()));
    uncheckedAllButtons();
    showPrieview();
}

MainWindow::~MainWindow()
{
    if(generator != NULL)
        delete generator;
    delete ui;
}

void MainWindow::getColorDialog()  // przycisk schowany wyboru koloru
{
    kolorki.show();
    showPrieview();
}

void MainWindow::zmianaKoloru(QColor kolor)
{
    if(ui->pushButtonLT->isChecked())
    {
        ltop = kolor;
        ui->spinBoxLTR->setValue(kolor.red());
        ui->spinBoxLTB->setValue(kolor.blue());
        ui->spinBoxLTG->setValue(kolor.green());
    }
    else if(ui->pushButtonRT->isChecked() )
    {
        rtop = kolor;
        ui->spinBoxRTR->setValue(kolor.red());
        ui->spinBoxRTB->setValue(kolor.blue());
        ui->spinBoxRTG->setValue(kolor.green());
    }
    else if(ui->pushButtonRB->isChecked() )
    {
        rbott = kolor;
        ui->spinBoxRBR->setValue(kolor.red());
        ui->spinBoxRBB->setValue(kolor.blue());
        ui->spinBoxRBG->setValue(kolor.green());
    }
    else if(ui->pushButtonLB->isChecked())
    {
        lbott = kolor;
        ui->spinBoxLBR->setValue(kolor.red());
        ui->spinBoxLBB->setValue(kolor.blue());
        ui->spinBoxLBG->setValue(kolor.green());
    }
    showPrieview();
}



void MainWindow::showPrieview()
{
    if(generator != NULL)
        delete generator;
    ltop.setRgb(ui->spinBoxLTR->value(),ui->spinBoxLTG->value(),ui->spinBoxLTB->value());
    rtop.setRgb(ui->spinBoxRTR->value(),ui->spinBoxRTG->value(),ui->spinBoxRTB->value());
    lbott.setRgb(ui->spinBoxLBR->value(),ui->spinBoxLBG->value(),ui->spinBoxLBB->value());
    rbott.setRgb(ui->spinBoxRBR->value(),ui->spinBoxRBG->value(),ui->spinBoxRBB->value());

    ui->labelLT->setStyleSheet("background:" + ltop.name());
    ui->labelRT->setStyleSheet("background:" + rtop.name());
    ui->labelLB->setStyleSheet("background:" + lbott.name());
    ui->labelRB->setStyleSheet("background:" + rbott.name());

    double height, width;
    height = width = 250;
   if(ui->spinBoxHeight->value() < ui->spinBoxWidth->value())
         height = height*ui->spinBoxHeight->value()/ui->spinBoxWidth->value();
    else
        width = width * ui->spinBoxWidth->value()/ui->spinBoxHeight->value();

    generator = new Generator(rtop,ltop,rbott,lbott,height,width);
    scene->addItem(generator);
}

void MainWindow::on_pushButton_clicked()  // save
{
    if( ui->spinBoxWidth->value() < 1)
    {
        QMessageBox::information(this, "Tip", "The image width is to small!");
        return;
    }
    else if(ui->spinBoxHeight->value() < 1 )
    {
        QMessageBox::information(this, "Tip", "The image height is to small!");
        return;
    }
    QFileDialog saveFile;

    connect(&saveFile,SIGNAL(filterSelected(QString)),this, SLOT(filterName(QString)));
    QString filters, location;
    location.append(QStandardPaths::displayName(QStandardPaths::PicturesLocation));
    QList <QByteArray> listSuportedExtension =  QImageReader::supportedImageFormats();


    foreach (QByteArray array, listSuportedExtension)
        if(array != listSuportedExtension.last())
            filters.append(array + " (*" + array + ");;");
        else
            filters.append(array + " (*" + array + ")");



    Generator gradientTemp(rtop,ltop,rbott,lbott,ui->spinBoxHeight->value(),ui->spinBoxWidth->value());
#ifdef Q_OS_LINUX
    QString selectedFile(saveFile.getSaveFileName(this,"Save",location));
#else
    QString selectedFile(saveFile.getSaveFileName(this,"Save",location,filters.toUpper()));
#endif

    if(selectedFile.isEmpty())
         return;


    bool existExtension = true;
    foreach (QByteArray array, listSuportedExtension)
       if(selectedFile.endsWith(array, Qt::CaseInsensitive))
            existExtension = false;

    if(existExtension)
    {
         QMessageBox::warning(this, "Wrong file name", "You don't add extension to your file. File will be saved as PNG!");
         selectedFile.append(".png");
    }
    foreach (QByteArray array, listSuportedExtension)
       if(selectedFile.endsWith(array, Qt::CaseInsensitive))
            if(! gradientTemp.saveFile(selectedFile, ui->horizontalSlider->value(),array))
                QMessageBox::information(this, "Tip", "This file cannot be saved. Check support of this format or change extenion!");
}

void MainWindow::zmianaJakosci(int value)
{
    ui->labelQuality->setText("Quality: " + QString::number(value) + " %");
}


void MainWindow::uncheckedAllButtons()
{
    ui->pushButtonLT->setChecked(false);
    ui->pushButtonRT->setChecked(false);
    ui->pushButtonRB->setChecked(false);
    ui->pushButtonLB->setChecked(false);
}

void MainWindow::on_pushButtonLT_clicked()
{
    uncheckedAllButtons();
    ui->pushButtonLT->setChecked(true);
}
void MainWindow::on_pushButtonRT_clicked()
{
    uncheckedAllButtons();
    ui->pushButtonRT->setChecked(true);
}

void MainWindow::on_pushButtonLB_clicked()
{
    uncheckedAllButtons();
    ui->pushButtonLB->setChecked(true);
}

void MainWindow::on_pushButtonRB_clicked()
{
    uncheckedAllButtons();
    ui->pushButtonRB->setChecked(true);
}

void MainWindow::filterName(QString fileExtension)
{
    qDebug() << fileExtension;
}

void MainWindow::on_actionO_Programie_triggered()
{
    QMessageBox::information(this, "About application", "Program was produce in 2012. This is version 1.0");
}

void MainWindow::on_actionO_Autorze_triggered()
{
    author.show();
}
