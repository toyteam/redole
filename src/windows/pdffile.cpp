#include "pdffile.h"

#include<QDebug>
#include<QFile>
#include<QCryptographicHash>
PdfFile::PdfFile(const QString & filePath)
{
    //空路径不处理
    this->filepath = filePath;
    if(filePath.length()==0)
    {
        document=NULL;
        return;
    }
    //判断文件是否存在
    QFile pdffile(filepath);
    if(!pdffile.exists())
    {
        return;
    }
    //计算MD5
    //加载
    document = Poppler::Document::load(filepath);
    if (!document || document->isLocked())
    {
        delete document;
        document=NULL;
        return;
    }
    //图像反走样
    document->setRenderHint(Poppler::Document::TextAntialiasing);
    getPdfInfo();
}


PdfFile::~PdfFile()
{
    delete document;
}

PdfFile::PdfFile()
{
    document=NULL;
    filepath=QString("");
}

bool PdfFile::setFilepath(const QString &filePath)
{
    if(document!=NULL)
    {
        delete document;
        document=NULL;
    }
    //空路径不处理
    this->filepath = filePath;
    if(filePath.length()==0)
    {
        return false;
    }
    //判断文件是否存在
    QFile pdffile(filepath);
    if(!pdffile.exists())
    {
        return false;
    }
    //计算MD5
    QFile file_md5(filepath);
    file_md5.open(QIODevice::ReadWrite);
    unsigned char* fpr = file_md5.map(0, file_md5.size());
    
    if(fpr)
    {
        QCryptographicHash hash(QCryptographicHash::Md5);
        hash.addData((char *)fpr,file_md5.size());
        hashresult=hash.result();
        file_md5.unmap(fpr);
    }
    else
    {
        qDebug()<<"文件内存映射失败，无法计算md5";
    }
    file_md5.close();
    //加载
    document = Poppler::Document::load(filepath);
    if (!document || document->isLocked())
    {
        delete document;
        document=NULL;
        return false;
    }
    //图像反走样
    document->setRenderHint(Poppler::Document::TextAntialiasing,true);
    getPdfInfo();
    return true;
}

void PdfFile::getPdfInfo()
{
    pagenum = 0;
    pagenum = document->numPages();
}

PdfPage PdfFile::getPage(int num)
{
    PdfPage page;
    //空路径处理
    if(filepath.length()==0)
    {
        page.img=QImage();
        page.size=QSize(100,100);
        return page;
    }
    // Document starts at page 0
    Poppler::Page* pdfPage = document->page(num);
    if (pdfPage == NULL)
    {
        delete pdfPage;
        return page;
    }
    //get page size
    page.size = pdfPage->pageSize();
    qDebug()<<QString("page:");
    qDebug()<<page.size;
    // Generate a QImage of the rendered page
    /*
    if(page.size.height()<1000)
    {
        page.img = pdfPage->renderToImage(page.size.width()/4.0, page.size.height()/4.0, -1, -1, -1, -1);
        qDebug()<<"<1000";
    }
    else if(page.size.height()<2000)
    {
        page.img = pdfPage->renderToImage(page.size.width()/8.0, page.size.height()/8.0, -1, -1, -1, -1);
        qDebug()<<"<2000&&>1000";
    }
    else
    {
        page.img = pdfPage->renderToImage(page.size.width()/25.0, page.size.height()/25.0, -1, -1, -1, -1);
        qDebug()<<">2000";
    }
    */
    //100是dpi
    page.img = pdfPage->renderToImage(100.0, page.size.height()*100.0/page.size.width(), -1, -1, -1, -1);
    qDebug()<<QString("image:");
    qDebug()<<page.img.size();
    if (page.img.isNull())
    {
        delete pdfPage;
        return page;
    }

    // after the usage, the page must be deleted
    //ui->label->setPixmap(QPixmap::fromImage(image));
    delete pdfPage;
    return page;
}

