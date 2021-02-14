#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidgetItem>
#include <QElapsedTimer>
#include <QVector>
#include <QColor>
#include <QPen>

#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_OkSize_clicked();

    void on_pushButton_Set_clicked();

    void on_pushButton_Sort_clicked();

    void on_pushButton_SortAll_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
