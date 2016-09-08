#ifndef PDFFILE_H
#define PDFFILE_H
#include<QString>
#include<QImage>
#include "poppler/poppler-qt5.h"
#include"pdfpage.h"
class PdfFile
{
public:
    PdfFile(){}
    ~PdfFile();
    PdfFile(const QString & filePath);
    void setFilepath(const QString & filePath);
    void getPdfInfo();
    PdfPage getPage(int num);
    int getPageNum(){return pagenum;}
private:
    Poppler::Document* document;
    QString filepath;
    //info
    int pagenum;
};

#endif // PDFFILE_H
