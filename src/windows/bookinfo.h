#ifndef BOOKINFO_H
#define BOOKINFO_H

#include<QString>
#include<QVector>
class BookInfo
{
public:
    BookInfo();
    QString name;
    QString hash;
    long long size;
    QVector<int> mark;
};

#endif // BOOKINFO_H
