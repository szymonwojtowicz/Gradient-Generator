#include "author.h"
#include "ui_author.h"

Author::Author(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Author)
{
    ui->setupUi(this);
    ui->labelAuthor->setStyleSheet("background-image: url(://Images/Face_.png);");
    QPixmap pix("://Images/Face_.png");
   pix = pix.scaled(150,300,Qt::KeepAspectRatio,Qt::SmoothTransformation);
    ui->labelAuthor->setPixmap(pix);
    ui->textBrowser->setText("Hi! <br /><br /> Application is use in LGPL license. Fell free in develop app, but please remember about author name.<br /> Thanks for using!<br /><br /> Szymon Wójtowicz <br /><br /> you can visit me on <br /> <font color=\"blue\">www.szymonwojtowicz.pl");
}

Author::~Author()
{
    delete ui;
}

void Author::on_pushButton_clicked()
{
    close();
}
