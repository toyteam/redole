#ifndef PDFFILE_H
#define PDFFILE_H
#include<QString>
#include<QImage>
#include<QByteArray>
#include "poppler/poppler-qt5.h"
#include"pdfpage.h"
class PdfFile
{
public:
    PdfFile();
    PdfFile(const QString & filePath);
    ~PdfFile();
    bool setFilepath(const QString & filePath);
    //读取文档信息
    void getPdfInfo();
    //获取某一页
    PdfPage getPage(int num);
    //获取总页数
    int getPageNum(){return pagenum;}
    //获取文件路径
    QString getFilePath(){return filepath;}
    //获取hash值
    QByteArray getHash(){return hashresult;}
private:
    Poppler::Document* document;
    QString filepath;
    QByteArray hashresult;
    //info
    int pagenum;
};

#endif // PDFFILE_H
