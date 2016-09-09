#ifndef BOOKMARKREADER_H
#define BOOKMARKREADER_H

#include<QString>
#include<QSettings>
#include"bookinfo.h"
class BookmarkReader
{
public:
    BookmarkReader(const QString &filepath);
    ~BookmarkReader();
    void readAll();
    void writeAll();
    
    QMap<QString,BookInfo> bookmark;
    int bookNum;
private:
    QSettings *configIni;
    
};

#endif // BOOKMARKREADER_H
