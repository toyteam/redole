#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QGraphicsScene>
#include <QResizeEvent>
#include<QCloseEvent>
#include<QPaintEvent>
#include"pdfview.h"
#include"configreader.h"
#include"bookmarkreader.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    //重绘窗口
    void repaint();
    //缩放窗口
    void resizeEvent(QResizeEvent* e);
    //绘制窗口
    void paintEvent(QPaintEvent *e);
    //关闭窗口
    void closeEvent(QCloseEvent *e);
    //打开一个文件
    void openFile(const QString &filePath);
private slots:
    void on_lineEdit_returnPressed();

    void on_spinBox_valueChanged(int arg1);

    void on_UpButton_clicked();

    void on_DownButton_clicked();

    void on_actionOpen_triggered();
    
    void on_comboBox_currentIndexChanged(int index);
    
    void on_action_3_triggered();
    
    void on_action_5_triggered();
    
    void on_bookmark_clicked();
    
private:
    Ui::MainWindow *ui;
    PdfView pdfview;
    ConfigReader *config_reader;
    BookmarkReader *bookmark_reader;
    
    QGraphicsScene scene;
    bool isOpenAnyPdf;
    int fitStyle;//0 自动缩放,1 适合页宽,2 适合页高,3 自定义
    double scale;
};

#endif // MAINWINDOW_H
