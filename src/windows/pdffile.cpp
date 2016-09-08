#include "pdffile.h"

#include<QDebug>

PdfFile::PdfFile(const QString & filePath)
{
    this->filepath = filePath;
    document = Poppler::Document::load(filepath);
    if (!document || document->isLocked())
    {
        delete document;
        throw "Can not find the pdf or the pdf is locked.";
    }
    getPdfInfo();
}

PdfFile::~PdfFile()
{
    delete document;
}

void PdfFile::setFilepath(const QString &filePath)
{
    if(document!=NULL)
    {
        delete document;
    }
    this->filepath = filePath;
    document = Poppler::Document::load(filepath);
    if (!document || document->isLocked())
    {
        delete document;
        throw "Can not find the pdf or the pdf is locked.";
    }
    getPdfInfo();
}

void PdfFile::getPdfInfo()
{
    pagenum = 0;
    pagenum = document->numPages();
}

PdfPage PdfFile::getPage(int num)
{
    PdfPage page;
    // Document starts at page 0
    Poppler::Page* pdfPage = document->page(num);
    if (pdfPage == NULL)
    {
        throw "page error";
    }
    //get page size
    page.size = pdfPage->pageSize();
    qDebug()<<page.size;
    // Generate a QImage of the rendered page
    page.img = pdfPage->renderToImage(page.size.width()/5.0, page.size.height()/5.0, -1, -1, -1, -1);
    if (page.img.isNull())
    {
        throw "image error";
    }


    // after the usage, the page must be deleted
    //ui->label->setPixmap(QPixmap::fromImage(image));
    delete pdfPage;
    return page;
}

