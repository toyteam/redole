#include "configreader.h"

ConfigReader::ConfigReader(const QString &filepath)
    :isRememberName(true),
      isRememberPass(true),
      bookNum(0),
        lastpage(0)
{
    configIni=NULL;
    
    configIni = new QSettings(filepath, QSettings::IniFormat);
    readAll();
    
}

ConfigReader::~ConfigReader()
{
    if(configIni!=NULL)
        delete configIni;
}

void ConfigReader::readAll()
{
    username=configIni->value("/login/name").toString();
    token=configIni->value("/login/token").toString();
    isRememberName=configIni->value("/login/isRemName").toBool();
    isRememberPass=configIni->value("/login/isRemPass").toBool();
    
    bookNum=configIni->value("/bookmark/num").toInt();
    
    lastbook=configIni->value("/lastsave/lastbook").toString();
    lastpage=configIni->value("/lastsave/lastpage").toInt();
}

void ConfigReader::writeAll()
{
    configIni->setValue("/login/name",username);
    configIni->setValue("/login/token",token);
    configIni->setValue("/login/isRemName",isRememberName);
    configIni->setValue("/login/isRemPass",isRememberPass);
    
    configIni->setValue("/bookmark/num",bookNum);
    
    configIni->setValue("/lastsave/lastbook",lastbook);
    configIni->setValue("/lastsave/lastpage",lastpage);
    
}
