#include "pdfview.h"
#include<QPainter>
PdfView::PdfView()
{

}

PdfView::PdfView(const QString &filePath, QSize size)
{
    curpage=0;
    winSize=size;
    scale=1.0;
    pdffile.setFilepath(filePath);
    cachedPage.clear();


}

bool PdfView::set(const QString &filePath, QSize size)
{
    winSize=size;
    scale=1.0;
    if(pdffile.setFilepath(filePath)==false)
    {
        return false;
    }

    cachedPage.clear();
    //缓存
    /*
    for(int i=curpage;i<pdffile.getPageNum();++i)
    {
        if(cachedPage.size()<queueLimit)
        {
            cachedPage[i]=pdffile.getPage(i);
        }
        else
        {
            break;
        }
    }
    */
    return true;
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
    /*
    for(int i=1;i<3;++i)
    {
        if(i+pagenum>=0&&i+pagenum<pdffile.getPageNum())
        {
            if(!cachedPage.contains(pagenum++))
            {
                cachedPage[i]=pdffile.getPage(i);
            }
        }
    }
    */

    if(cachedPage.contains(pagenum))
    {
        tempImg=cachedPage[pagenum].img;
        h=tempImg.height()*scale;
        w=tempImg.width()*scale;
        //return tempImg.scaled(w,h,Qt::KeepAspectRatio,Qt::SmoothTransformation);
        //return tempImg.scaled(w,h);
        //return tempImg.scaled(w,h,Qt::KeepAspectRatioByExpanding,Qt::SmoothTransformation);
        return tempImg;
    }
    else
    {
        tempImg=pdffile.getPage(pagenum).img;
        h=tempImg.height()*scale;
        w=tempImg.width()*scale;
        //return tempImg.scaled(w,h,Qt::KeepAspectRatio,Qt::SmoothTransformation);
        //return tempImg.scaled(w,h);
        //return tempImg.scaled(w,h,Qt::KeepAspectRatioByExpanding,Qt::SmoothTransformation);
        return tempImg;
    }

}
