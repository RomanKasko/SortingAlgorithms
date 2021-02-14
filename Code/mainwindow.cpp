#include "mainwindow.h"
#include "ui_mainwindow.h"

#define MODE 0

QElapsedTimer timer1,timer2,timer3,timer4,timer5,timer6;
QTableWidgetItem *item;
vector<int> vect;
QVector<int> vectSizes(7);
int Size = 0;
QElapsedTimer timeArr[6];

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    if(!MODE) ui->tableWidget_ResultArray->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void DoPrintVector(Ui::MainWindow *ui)
{
 QString number;
 for(int j = 0; j < vect.size(); ++j)
 {
     number = QString::number(vect.at(j));
     item = new QTableWidgetItem(number);
     ui->tableWidget_ResultArray->setItem(0, j, item);
 }
}

void DoSwapElements(int *value1, int *value2)
{
    int tmp;
    tmp = *value1;
    *value1 = *value2;
    *value2 = tmp;
}

bool ShouldArrayBeSorted(vector<int> vect)
{
    for(int i = 0; i < vect.size()-1; ++i)
        if(vect.at(i+1) < vect.at(i))
            return false;
    return true;
}

void DoBubbleSort(vector<int> vect)
{
    for(int i = 0; i < vect.size(); ++i)
    {
      bool flag = false;
      for(int j = 0; j < vect.size()-i-1; ++j)
      {
          if(vect.at(j+1) < vect.at(j))
          {
              flag = true;
              DoSwapElements(&vect.at(j),&vect.at(j+1));
          }
      }
      if(!flag) break;
   }
}

void DoSelectionSort(vector<int> vect)
{
    int i, j, minIndex;
    for (i = 0; i < vect.size()-1; i++)
    {
        minIndex = i;
        for (j = i+1; j < vect.size(); j++)
        if (vect[j] < vect[minIndex])
            minIndex = j;
        DoSwapElements(&vect[minIndex], &vect[minIndex]);
    }
}

void DoShellSort(vector<int> vect)
{
    for (int gap = vect.size()/2; gap > 0; gap /= 2)
    {
       for (int i = gap; i < vect.size(); i += 1)
      {
        int temp = vect.at(i);
        int j;
        for (j = i; j >= gap && vect[j - gap] > temp; j -= gap)
            vect[j] = vect[j - gap];
        vect[j] = temp;
      }
   }
}

void DoMerge(vector<int> *arr, int left, int mid, int right)
{
    int subSize1 = mid - left + 1;
    int subSize2 = right - mid;
    vector<int> subArrL(subSize1), subArrR(subSize2);
    for(int i = 0; i < subSize1; i++) /// перша половина у підмасив L
        subArrL[i] = (*arr).at(left + i);

    for(int j = 0; j < subSize2; j++) /// перша половина у підмасив R
        subArrR[j] = (*arr).at(mid + 1 + j);

    int i = 0, j = 0;
    int resIdx = left;

    while (i < subSize1 && j < subSize2)
    {
        if (subArrL[i] <= subArrR[j])
        {
            (*arr).at(resIdx) = subArrL[i];
            ++i;
        }
        else
        {
            (*arr).at(resIdx) = subArrR[j];
            ++j;
        }
        ++resIdx;
    }

    while (i < subSize1)
    {
        (*arr).at(resIdx) = subArrL[i];
        ++i;
        ++resIdx;
    }

    while (j < subSize2)
    {
        (*arr).at(resIdx) = subArrR[j];
        ++j;
        ++resIdx;
    }
}

void DoMergeSort(vector<int> *arr, int left, int right)
{
    if (left < right)
    {
        int mid = (right + left) / 2;
        DoMergeSort(arr, left, mid);
        DoMergeSort(arr, mid + 1, right);
        DoMerge(arr, left, mid, right);
    }
}

int DoSplit(vector<int> *arr, int low, int high)
{
    int base = arr->at(high);
    int i = low - 1;
    for(int j = low; j < high; ++j)
        if(arr->at(j) < base)
        {
            ++i;
            DoSwapElements(&arr->at(i),&arr->at(j));
        }
    DoSwapElements(&arr->at(i+1),&arr->at(high));
    return i+1;
}

void DoQuickSort(vector<int> *arr, int low, int high)
{
    if(low < high)
    {
       int x = DoSplit(arr, low, high);
       DoQuickSort(arr, low, x-1);
       DoQuickSort(arr, x+1, high);
    }
}

void DoCountingSort(vector<int> vect)
{
    vector<int> countVect, posVect;
    int max = (vect).at(0);

    for(int i = 0 ; i < (vect).size(); ++i)
    {
        if((vect).at(i) > max)
            max = (vect).at(i);
    }

    for(int i = 0; i < (vect).size(); ++i)
        posVect.push_back(0);

    for(int i = 0; i <= max; ++i)
        countVect.push_back(0);

    for(int i = 0; i < (vect).size(); ++i)
            countVect[(vect)[i]]++;

    for(int i = 1; i <= max; ++i)
       countVect[i] += countVect[i-1]; // сумую наст елем попередніми значеннями

    for(int i = 0; i <= (vect).size()-1; ++i)
    {
      posVect[countVect[(vect).at(i)]-1] = (vect).at(i);
      countVect[(vect).at(i)]--;
    }

    for(int i = 0; i < (vect).size(); ++i)
        (vect).at(i) = posVect[i];
}


void MainWindow::on_pushButton_Sort_clicked()
{
    string strSort = ui->comboBox_ChooseSort->currentText().toStdString();
    if(strSort == "Bubble")
    {
        timer1.start();
        DoBubbleSort(vect);
        ui->tableWidget_Info->setItem(0,1,new QTableWidgetItem(QString::number(timer1.nsecsElapsed()/1000000000.0) + " seconds"));
        //if(MODE) DoPrintVector(ui);
    }
    else if(strSort == "Selection")
    {
        timer2.start();
        DoSelectionSort(vect);
        ui->tableWidget_Info->setItem(0,3,new QTableWidgetItem(QString::number(timer2.nsecsElapsed()/1000000000.0) + " seconds"));
        //if(MODE) DoPrintVector(ui);
    }
    else if(strSort == "Shell")
    {
        timer3.start();
        DoShellSort(vect);
        ui->tableWidget_Info->setItem(0,5,new QTableWidgetItem(QString::number(timer3.nsecsElapsed()/1000000000.0) + " seconds"));
        //if(MODE) DoPrintVector(ui);
    }
    else if(strSort == "Merge")
    {
        vector<int> tmp(vect.size());
        for(int i = 0; i < vect.size(); ++i)
            tmp[i] = vect[i];
        timer4.start();
        DoMergeSort(&tmp,0,tmp.size()-1);
        ui->tableWidget_Info->setItem(0,7,new QTableWidgetItem(QString::number(timer4.nsecsElapsed()/1000000000.0) + " seconds"));
        //if(MODE) DoPrintVector(ui);
    }
    else if(strSort == "Quick")
    {
        vector<int> tmp(vect.size());
        for(int i = 0; i < vect.size(); ++i)
            tmp[i] = vect[i];
        timer5.start();
        DoQuickSort(&tmp,0,tmp.size()-1);
        ui->tableWidget_Info->setItem(0,9,new QTableWidgetItem(QString::number(timer5.nsecsElapsed()/1000000000.0) + " seconds"));
        //if(MODE) DoPrintVector(ui);
    }
    else if(strSort == "Counting")
    {
        timer6.start();
        DoCountingSort(vect);
        ui->tableWidget_Info->setItem(0,11,new QTableWidgetItem(QString::number(timer6.nsecsElapsed()/1000000000.0) + " seconds"));
        if(MODE) DoPrintVector(ui);
    }
}



void MainWindow::on_pushButton_OkSize_clicked()
{
    int minSize = 1024;
    for(int i = 0; i < 7; ++i)
    {
        vectSizes[i] = minSize * 4;
        minSize *= 4;
    }
    int size = ui->comboBox_Size->currentText().toInt();
    ui->tableWidget_Array->setRowCount(1);
    ui->tableWidget_Array->setColumnCount(size);
    Size = size;
    ui->tableWidget_Array->verticalHeader()->setVisible(false);
    ui->tableWidget_Array->horizontalHeader()->setVisible(false);

    ui->tableWidget_ResultArray->setRowCount(1);
    ui->tableWidget_ResultArray->setColumnCount(size);
    ui->tableWidget_ResultArray->verticalHeader()->setVisible(false);
    ui->tableWidget_ResultArray->horizontalHeader()->setVisible(false);

    ui->tableWidget_Info->setRowCount(6);
    ui->tableWidget_Info->setColumnCount(2);
    ui->tableWidget_Info->setHorizontalHeaderItem(0, new QTableWidgetItem("SORTING NAME"));
    ui->tableWidget_Info->setHorizontalHeaderItem(1, new QTableWidgetItem("TIME"));
    ui->tableWidget_Info->setItem(0,0,new QTableWidgetItem("BUBBLE"));
    ui->tableWidget_Info->setItem(1,0,new QTableWidgetItem("SELECTION"));
    ui->tableWidget_Info->setItem(2,0,new QTableWidgetItem("SHELL"));
    ui->tableWidget_Info->setItem(3,0,new QTableWidgetItem("MERGE"));
    ui->tableWidget_Info->setItem(4,0,new QTableWidgetItem("QUICK"));
    ui->tableWidget_Info->setItem(5,0,new QTableWidgetItem("COUNTING"));
}


void MainWindow::on_pushButton_Set_clicked()
{
    vect.clear();

    for(int i = 0; i < Size; ++i)
    {
        QTableWidgetItem* itm = ui->tableWidget_Array->item(0,i);
        if (!itm || itm->text().isEmpty())
        {
            int element = rand();
            vect.push_back(element);

            QString number;
            number = QString::number(vect.at(i));
            item = new QTableWidgetItem(number);
            ui->tableWidget_Array->setItem(0, i, item);
        }
        else
        {
           int el = ui->tableWidget_Array->item(0,i)->text().toInt();
           vect.push_back(el);
        }
   }
}

void MainWindow::on_pushButton_SortAll_clicked()
{
    timer1.start();
    DoBubbleSort(vect);
    ui->tableWidget_Info->setItem(0,1,new QTableWidgetItem(QString::number(timer1.nsecsElapsed()/1000000000.0) + " seconds"));
    timer2.start();
    DoSelectionSort(vect);
    ui->tableWidget_Info->setItem(0,3,new QTableWidgetItem(QString::number(timer2.nsecsElapsed()/1000000000.0) + " seconds"));
    timer3.start();
    DoShellSort(vect);
    ui->tableWidget_Info->setItem(0,5,new QTableWidgetItem(QString::number(timer3.nsecsElapsed()/1000000000.0) + " seconds"));

    vector<int> tmp(vect.size()),tmp2(vect.size());
    for(int i = 0; i < vect.size(); ++i)
    {
        tmp[i] = vect[i];
         tmp2[i] = vect[i];
    }
    timer4.start();
    DoMergeSort(&tmp,0,tmp.size()-1);
    ui->tableWidget_Info->setItem(0,7,new QTableWidgetItem(QString::number(timer4.nsecsElapsed()/1000000000.0) + " seconds"));
    timer5.start();
    DoQuickSort(&tmp2,0,tmp2.size()-1);
    ui->tableWidget_Info->setItem(0,9,new QTableWidgetItem(QString::number(timer5.nsecsElapsed()/1000000000.0) + " seconds"));
    timer6.start();
    DoCountingSort(vect);
    ui->tableWidget_Info->setItem(0,11,new QTableWidgetItem(QString::number(timer6.nsecsElapsed()/1000000000.0) + " seconds"));
}

