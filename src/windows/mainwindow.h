#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QGraphicsScene>
#include <QResizeEvent>

#include"pdffile.h"
#include"pdfview.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void repaint();
    void resizeEvent(QResizeEvent* e);
private slots:
    void on_lineEdit_returnPressed();

    void on_spinBox_valueChanged(int arg1);

    void on_UpButton_clicked();

    void on_DownButton_clicked();

private:
    Ui::MainWindow *ui;
    PdfView pdfview;
    QGraphicsScene scene;
};

#endif // MAINWINDOW_H
