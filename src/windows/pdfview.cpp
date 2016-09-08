#include "pdfview.h"
#include<QPainter>
PdfView::PdfView(const QString &filePath, QSize size)
{
    curpage=0;
    winSize=size;
    scale=1.0;

    pdffile.setFilepath(filePath);

    cachedPage.clear();
    //缓存
    for(int i=curpage;i<curpage+10;++i)
    {
        if(!cachedPage.contains(i))
        {
            cachedPage[i]=pdffile.getPage(i);
        }
    }


}

void PdfView::set(const QString &filePath, QSize size)
{

    curpage=0;
    winSize=size;
    scale=1.0;

    pdffile.setFilepath(filePath);

    cachedPage.clear();
    //缓存
    if(pdffile.getPageNum()<=10)
    {
        for(int i=curpage;i<pdffile.getPageNum();++i)
        {
            if(!cachedPage.contains(i))
            {
                cachedPage[i]=pdffile.getPage(i);
            }
        }
    }

}

void PdfView::resize(QSize size)
{
    winSize=size;
}



QImage PdfView::getImage(int pagenum)
{
    QImage tempImg;
    int w,h;
    //缓存
    if(pagenum>=10&&pagenum<pdffile.getPageNum()-10)
    {
        for(int i=pagenum-10;i<pagenum+10;++i)
        {
            if(!cachedPage.contains(i))
            {
                cachedPage[i]=pdffile.getPage(i);
            }
        }
    }

    if(cachedPage.contains(pagenum))
    {
        tempImg=cachedPage[pagenum].img;
        h=tempImg.height()*scale;
        w=tempImg.width()*scale;
        //return tempImg.scaled(w,h,Qt::KeepAspectRatio,Qt::SmoothTransformation);
        return tempImg.scaled(w,h);
        //return tempImg.scaled(w,h,Qt::KeepAspectRatioByExpanding,Qt::SmoothTransformation);
    }
    else
    {
        tempImg=pdffile.getPage(pagenum).img;
        h=tempImg.height()*scale;
        w=tempImg.width()*scale;
        //return tempImg.scaled(w,h,Qt::KeepAspectRatio,Qt::SmoothTransformation);
        return tempImg.scaled(w,h);
        //return tempImg.scaled(w,h,Qt::KeepAspectRatioByExpanding,Qt::SmoothTransformation);
    }

}
