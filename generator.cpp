#include "generator.h"



Generator::Generator(QColor rtopColor,QColor ltopColor,QColor rbottColor,QColor lbottColor, int height, int width) : h(height), w(width)
{
    diagonal =  w * h;
    setMyColor(rtopColor,ltopColor,rbottColor,lbottColor);
}


QRectF Generator::boundingRect() const
{
    return QRectF(0,0,w,h);
}

void Generator::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    QRectF rec = boundingRect();

    int r,g,b;

    for( int i = 0; i < w; i++)
        for( int k = 0; k < h; k++)
        {
            r = color(k,i,0);
            g = color(k,i,1);
            b = color(k,i,2);

            painter->setPen(QColor::fromRgb(r,g,b));             // set blue pen, 0 pixel width
            painter->drawPoint(i,k);
        }
    painter->drawRect(rec);
}


inline double Generator::color(int col, int row, int rgb)  // rgb - 1 red | 2 green | 3 blue
{
    pltop = (h-col) * (w-row) ;
    prtop = (h-col) * row ;

    plbott = col * (w-row) ;
    prbott = col * row ;

    pltop /= diagonal;
    prtop /= diagonal;
    plbott/= diagonal;
    prbott/= diagonal;

    if(rgb == 0)
        return  ((ltop.red() * pltop) + (rtop.red() * prtop) +(lbott.red() * plbott) +(rbott.red() * prbott)) ;
    if(rgb == 1)
        return  ((ltop.green() * pltop) + (rtop.green() * prtop) +(lbott.green() * plbott) +(rbott.green() * prbott));
    if(rgb == 2)
        return  ((ltop.blue() * pltop) + (rtop.blue() * prtop) +(lbott.blue() * plbott) +(rbott.blue() * prbott));

    return -1;
}


void Generator::setcolor(QRgb kolor, int position)
{
    switch( position )
    {
    case 0:
        rtop = kolor;
        break;
    case 1:
        ltop = kolor;
        break;
    case 2:
        rbott = kolor;
        break;
    case 3:
        lbott = kolor;
        break;

    default:
          qDebug() << "Incorrect value!";
        break;
    }
}

void Generator::setMyColor(QColor rtopColor,QColor ltopColor,QColor rbottColor,QColor lbottColor)
{
    rtop = rtopColor;
    ltop = ltopColor;
    rbott = rbottColor;
    lbott = lbottColor;
}


bool Generator::saveFile(QString name, int quality, QString fileExtension)
{
    qDebug() << name << " Extension" << fileExtension;
    QColor rgbColor;
    QImage image(w,h, QImage::Format_ARGB32_Premultiplied);
    for( int i = 0; i < w; i++)
        for( int k = 0; k < h; k++)
        {
           rgbColor.setRgb(color(k,i,0),color(k,i,1),color(k,i,2));
           image.setPixel(i,k,rgbColor.rgb());
        }
    if(image.save(name,fileExtension.toLatin1(),quality))
        return true;
    return false;

  }

