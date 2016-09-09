#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QMessageBox>
#include<QFileDialog>
#include<QPrintDialog>
#include<QDebug>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->verticalScrollBar->hide();
    //初始化缩放
    scale=1.0;
    //设置页面大小
    fitStyle=0;
    //图像反走样
    //ui->graphicsView->setRenderHint(QPainter::TextAntialiasing);//TextAntialiasing
    //配置读写
    config_reader=new ConfigReader("config.ini");
    bookmark_reader=new BookmarkReader("bookmark.ini");
    //设置上次读到哪一页
    pdfview.curpage=config_reader->lastpage;
    
    

}

MainWindow::~MainWindow()
{
    delete ui;
    delete config_reader;
    delete bookmark_reader;
}

void MainWindow::repaint()
{
    scene.clear();
    scene.addPixmap(
                QPixmap::fromImage(
                    pdfview.getImage(pdfview.curpage)
                    )
                );
    ui->graphicsView->setScene(&scene);
    ui->graphicsView->resetMatrix();
    switch(fitStyle)
    {
    case 0:
        ui->graphicsView->scale(ui->graphicsView->height()/scene.height()*2.0,ui->graphicsView->height()/scene.height()*2.0);
        break;
    case 1:
        ui->graphicsView->scale(ui->graphicsView->height()/scene.height(),ui->graphicsView->height()/scene.height());
        break;
    case 2:
        ui->graphicsView->scale(ui->graphicsView->width()/scene.width(),ui->graphicsView->width()/scene.width());
        break;
    case 3:
        ui->graphicsView->scale(ui->graphicsView->height()/scene.height()*scale,ui->graphicsView->height()/scene.height()*scale);
        break;
    }
    //画收藏标志
    QVector<int> & vec=bookmark_reader->bookmark[pdfview.getHash()].mark;
    ui->bookmark->setText("☆");
    for(int i=0;i<vec.size();++i)
    {
        if(vec[i]==pdfview.curpage)
        {
           ui->bookmark->setText("★"); 
        }
    }
      

}


void MainWindow::resizeEvent(QResizeEvent* e)
{
    //通知大小改变
    pdfview.resize(ui->graphicsView->size());
    repaint();
}

void MainWindow::paintEvent(QPaintEvent *e)
{
    //执行部分窗口初始化后才进行的操作
    static bool isfirst=true;
    if(isfirst==true)
    {
        openFile(config_reader->lastbook);
        isfirst=false;
    }
    
}

void MainWindow::openFile(const QString &filePath)
{
    
    //设置文件路径
    if(pdfview.set(filePath,ui->graphicsView->size())==true)
    {
        //绘制当前页
        //scene.addPixmap(QPixmap::fromImage(pdfview.getImage(pdfview.curpage)));
        //ui->graphicsView->setScene(&scene);
        //显示目前在第几页(注意加一)
        ui->lineEdit->setText(QString::number(pdfview.curpage+1));
        //显示总共多少页
        ui->label_2->setText("\\"+QString::number(pdfview.getPageNum()));
        //qDebug()<<pdfview.getPageNum();
        //设置书签按钮样式
        ui->bookmark->setText("☆");
        //回到页顶
        ui->graphicsView->verticalScrollBar()->setValue(0);
        isOpenAnyPdf=true;
        //将书名写入文件
        if(!bookmark_reader->bookmark.contains(pdfview.getHash()))
        {
            BookInfo info;
            info.hash=QString(pdfview.getHash());
            info.name=pdfview.getFilePath();
            info.size=0;    //TODO 获取文件大小
            bookmark_reader->bookmark[info.hash]=info;
        }
        repaint();
    }
    else
    {
        QMessageBox warning;
        warning.warning(this,QString("找不到文件"),QString("无法找到文件")+pdfview.getFilePath());
        pdfview.set("",ui->graphicsView->size());
        QImage temp_img;
        temp_img.fill(Qt::lightGray);
        //绘制当前页
        scene.addPixmap(QPixmap::fromImage(temp_img));
        ui->graphicsView->setScene(&scene);
        //显示目前在第几页(注意加一)
        ui->lineEdit->setText(QString::number(0));
        //显示总共多少页
        ui->label_2->setText("\\"+QString::number(0));
        //设置书签按钮样式
        ui->bookmark->setText("☆");
        //回到页顶
        ui->graphicsView->verticalScrollBar()->setValue(0);
        isOpenAnyPdf=false;
    }
    
}
//手动指定页数跳转
void MainWindow::on_lineEdit_returnPressed()
{
    static int oldnum=1;
    if(isOpenAnyPdf==true)
    {
        int check_temp=ui->lineEdit->text().toInt()-1;  //注意减一
        if(check_temp>=0&&check_temp<pdfview.getPageNum())
        {
            pdfview.curpage=check_temp;
            oldnum=check_temp;
        }
        else
        {
            //弹框，无效
            ui->lineEdit->setText(QString::number(oldnum+1));
        }
        //检查是否有书签，然后改变button样式

        repaint();
    }
}

void MainWindow::on_spinBox_valueChanged(int arg1)
{

    //old
    //pdfview.setScale(arg1/100.0);
    //repaint();
    scale=arg1/100.0;
    repaint();
    //显示自定义模式
    ui->comboBox->setCurrentIndex(3);
    //ui->graphicsView->resetTransform();
}

void MainWindow::on_UpButton_clicked()
{
    if(isOpenAnyPdf==true)
    {
        //翻页
        if(pdfview.curpage>0)
            --pdfview.curpage;
        //检查是否有书签，然后改变button样式

        repaint();
        //设置页码显示
        ui->lineEdit->setText(QString::number(pdfview.curpage+1));  //注意显示的时候加一
        //回到页顶
        ui->graphicsView->verticalScrollBar()->setValue(0);
    }
}

void MainWindow::on_DownButton_clicked()
{
    if(isOpenAnyPdf==true)
    {
        //翻页
        if(pdfview.curpage<pdfview.getPageNum()-1)
            ++pdfview.curpage;
        //检查是否有书签，然后改变button样式
        repaint();
        //设置页码显示
        ui->lineEdit->setText(QString::number(pdfview.curpage+1));  //注意显示的时候加一
        //回到页顶
        ui->graphicsView->verticalScrollBar()->setValue(0);
    }
}

void MainWindow::on_actionOpen_triggered()
{
    QFileDialog filedialog;
    QString filepath=filedialog.getOpenFileName(this,QString("打开文件"),QString("/"),QString("Pdf (*.pdf)"));
    openFile(filepath);
}


void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    fitStyle=index;
    repaint();
}

void MainWindow::on_action_3_triggered()
{
    QPrintDialog printdialog;
    printdialog.show();
}

void MainWindow::on_action_5_triggered()
{
    this->close();
}

void MainWindow::on_bookmark_clicked()
{
    //static bool isstared=false;
    QVector<int> & vec=bookmark_reader->bookmark[pdfview.getHash()].mark;
    int i=0;
    int s=vec.size();
    for(i=0;i<s;++i)
    {
        if(vec[i]==pdfview.curpage)
        {
            vec.remove(i);
            ui->bookmark->setText("☆");
            break;
        }
    }
    if(i==s)
    {
        vec.push_back(pdfview.curpage);
        ui->bookmark->setText("★");
    }
}
//关闭窗口
void MainWindow::closeEvent(QCloseEvent *e)
{
    //保存配置
    config_reader->lastbook=pdfview.getFilePath();
    config_reader->lastpage=pdfview.curpage;
    
    config_reader->writeAll();
    bookmark_reader->writeAll();
}
