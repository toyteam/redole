#include "bookmarkreader.h"
#include<QDebug>
BookmarkReader::BookmarkReader(const QString &filepath)
{
    
    configIni=NULL;
    
    configIni = new QSettings(filepath, QSettings::IniFormat);
    readAll();
}

BookmarkReader::~BookmarkReader()
{
    if(configIni!=NULL)
        delete configIni;
}

void BookmarkReader::readAll()
{
    QString bookName;
    QString bookHash;
    long long bookSize;
    QString markstr;
    
    
    
    bookNum=configIni->value("/begin/booknum").toInt();
    for(int i=0;i<bookNum;++i)
    {
        BookInfo info_temp;
        bookName=configIni->value("/"+QString::number(i)+"/bookname").toString();
        bookHash=configIni->value("/"+QString::number(i)+"/bookhash").toString();
        bookSize=configIni->value("/"+QString::number(i)+"/booksize").toInt();
        markstr=configIni->value("/"+QString::number(i)+"/bookmark").toString();
        QStringList lst=markstr.split(",");
        
        info_temp.name=bookName;
        info_temp.hash=bookHash;
        info_temp.size=bookSize;
        for(QString index:lst)
        {
            info_temp.mark.push_back(index.toInt());
        }
          
        bookmark[bookHash]=info_temp;
    }
}

void BookmarkReader::writeAll()
{
    configIni->setValue("/begin/booknum", bookmark.size()); 
    int i=0;
    for(QMap<QString,BookInfo>::iterator it=bookmark.begin();it!=bookmark.end();++it)
    {
        QString mark_merge;
        for(int j=0;j<it->mark.size();++j)
        {
            if(j!=0)
                mark_merge+=',';
            mark_merge+=QString::number(it->mark[j]);
        }
        configIni->setValue("/"+QString::number(i)+"/bookname",it->name);
        configIni->setValue("/"+QString::number(i)+"/bookhash",it->hash);
        configIni->setValue("/"+QString::number(i)+"/booksize",it->size);
        configIni->setValue("/"+QString::number(i)+"/bookmark",mark_merge);
        ++i;
    }
}
