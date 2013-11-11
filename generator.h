#ifndef GENERATOR_H
#define GENERATOR_H
#include <QGraphicsItem>
#include <QPainter>
#include <QRgb>
#include <QMessageBox>
#include <QDebug>
#include <QGraphicsObject>

class Generator : public QGraphicsPixmapItem
{
public:
    Generator(QColor rtopColor,QColor ltopColor,QColor rbottColor,QColor lbottColor, int height = 100, int width = 100);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    void setcolor(QRgb kolor, int position);
    void setMyColor(QColor rtopColor, QColor ltopColor, QColor rbottColor, QColor lbottColor);
    bool saveFile(QString name, int quality, QString fileExtension);

private:
    int h,w;
    QColor rtop,ltop,rbott,lbott;
    double color(int col, int row, int rgb);
    int diagonal;
    double pltop, prtop, plbott, prbott;
};

#endif // GENERATOR_H
