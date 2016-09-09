#ifndef PDFVIEW_H
#define PDFVIEW_H
#include"pdffile.h"
#include<QString>
#include<QVector>
#include<QMap>
#include<QQueue>
#include<QImage>

class PdfView
{
public:
    PdfView();
    PdfView(const QString & filePath,QSize size);
    bool set(const QString & filePath,QSize size);
    //设置窗口大小
    void resize(QSize size);
    //设置缩放（暂不使用）
    void setScale(double s){scale=s;}
    //获取当前页
    int getPos(){return curpage;}
    //获取某一页
    QImage getImage(int pagenum);
    //获取总页数
    int getPageNum(){return pdffile.getPageNum();}
    //获取hash值
    QByteArray getHash(){return pdffile.getHash();}
    //当前页
    int curpage;
    //读取文件路径
    QString getFilePath(){return pdffile.getFilePath();}
private:
    PdfFile pdffile;
    QMap<int,PdfPage> cachedPage;
    QMap<int,QImage> thumbnail;
    double scale;
    QSize winSize;
    QImage image;
};

#endif // PDFVIEW_H
