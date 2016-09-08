#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->verticalScrollBar->hide();
    //设置文件路径
    pdfview.set("第11章 层叠样式表.pdf",ui->graphicsView->size());
    //绘制当前页
    scene.addPixmap(QPixmap::fromImage(pdfview.getImage(pdfview.curpage)));
    ui->graphicsView->setScene(&scene);
    //显示目前在第几页(注意加一)
    ui->lineEdit->setText(QString::number(pdfview.curpage+1));
    //显示总共多少页
    ui->label_2->setText("\\"+QString::number(pdfview.getPageNum()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::repaint()
{
    scene.clear();
    scene.addPixmap(QPixmap::fromImage(pdfview.getImage(pdfview.curpage)));
    ui->graphicsView->setScene(&scene);
}


void MainWindow::resizeEvent(QResizeEvent* e)
{
    pdfview.resize(ui->graphicsView->size());
    repaint();
}

void MainWindow::on_lineEdit_returnPressed()
{
    int check_temp=ui->lineEdit->text().toInt()-1;  //注意减一
    if(check_temp>=0&&check_temp<pdfview.getPageNum())
    {
        pdfview.curpage=check_temp;
    }
    else
    {
        //弹框，无效
    }
    repaint();
}

void MainWindow::on_spinBox_valueChanged(int arg1)
{
    pdfview.setScale(arg1/100.0);
    repaint();
}

void MainWindow::on_UpButton_clicked()
{
    if(pdfview.curpage>0)
        --pdfview.curpage;
    repaint();

}

void MainWindow::on_DownButton_clicked()
{

    if(pdfview.curpage<pdfview.getPageNum()-1)
        ++pdfview.curpage;
    repaint();
}
