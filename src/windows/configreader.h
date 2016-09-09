#ifndef CONFIGREADER_H
#define CONFIGREADER_H

#include<QVector>
#include<QMap>
#include<QFile>
#include<QSettings>


class ConfigReader
{
public:
    ConfigReader(const QString &filepath);
    ~ConfigReader();
    void readAll();
    void writeAll();
    
    QString username;
    QString token;
    bool isRememberName;
    bool isRememberPass;
    
    int bookNum;
    
    QString lastbook;
    int lastpage;
private:
    QSettings *configIni;
    
};

#endif // CONFIGREADER_H
