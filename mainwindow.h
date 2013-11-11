#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QColorDialog>
#include <QFileDialog>
#include <QStandardPaths>
#include <QImageReader>

#include "generator.h"
#include "author.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QColorDialog kolorki;

public slots:
    void zmianaKoloru(QColor kolor);
  //  void changeSpinColor();
    void zmianaJakosci(int value);
    void showPrieview();

private slots:

    void getColorDialog();
    void on_pushButton_clicked();
    void on_pushButtonLT_clicked();
    void on_pushButtonRT_clicked();
    void on_pushButtonLB_clicked();
    void on_pushButtonRB_clicked();

    void filterName(QString fileExtension);
    void on_actionO_Programie_triggered();

    void on_actionO_Autorze_triggered();

private:
    QGraphicsScene * scene;
    Generator *generator;
    Generator *gradientTemp;
    QColor rtop,ltop,rbott,lbott;
    void uncheckedAllButtons();
    Author author;

    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
