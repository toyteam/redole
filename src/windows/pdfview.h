#ifndef PDFVIEW_H
#define PDFVIEW_H
#include"pdffile.h"
#include<QString>
#include<QVector>
#include<QMap>
#include<QImage>

class PdfView
{
public:
    PdfView(){}
    PdfView(const QString & filePath,QSize size);
    void set(const QString & filePath,QSize size);
    void resize(QSize size);
    void setScale(double s){scale=s;}
    int getPos(){return curpage;}
    QImage getImage(int pagenum);
    int getPageNum(){return pdffile.getPageNum();}
    int curpage;
private:
    PdfFile pdffile;
    QMap<int,PdfPage> cachedPage;
    double scale;
    QSize winSize;
    QImage image;
};

#endif // PDFVIEW_H
