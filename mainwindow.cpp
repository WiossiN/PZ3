#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "stdlib.h"
#include "string.h"
#include <stdio.h>
#include <QMessageBox>
#include <QDesktopWidget>

int k; int sig=4; float **m1,**m2;
FILE *f;



//выделение памяти под матрицу
float** create_matr(int n)
{
        float **a;
        a=new float*[n+1];
        int i,j;
       for(i=0;i<n+1;i++)
           a[i]=new float[n+1];
        //инициализируем нулями
        for(i=0;i<n+1;i++)
        for(j=0;j<n+1;j++)
        a[i][j]=0;
        return a;
}//------------------------------------------

//освобождение памяти выделенной под матрицу
void free_matr(int n,float **a)
{
        for(int i=0;i<n;i++)
               // free(a[i]);
            delete a[i];
        delete a;
               // free(a);
}//------------------------------------------

//загрузить матрицу из файла
void Sozd_matr(int n,float **a)
{
        int i,j;
        for(i=0;i<n;i++)
        for(j=0;j<n;j++)
        fscanf(f,"%f",&a[i][j]) ;

    }
//------------------------------------------------------------

        //транспонирование матрицы
        void transp_matr(int n,float **a)
        {
          float d;
          for(int i=0;i<n;i++)
          for(int j=i+1;j<n;j++)
          {
            d=a[i][j];
            a[i][j]=a[j][i];
            a[j][i]=d;
          }
        }

//------------------------------------------------------------
        //копируем массив a в массив b
        void copy_matr(int n,float **a,float **b)
        {
          for(int i=0;i<n;i++)
          for(int j=0;j<n;j++)
            b[i][j]=a[i][j];
        }
 //------------------------------------------------------------
        //перемножение матриц a и b, результат помещается в матрицу c
        void Proiz_m1(int n,float **a,float **b, float **c)
        {
          for(int i=0;i<n;i++)
          for(int j=0;j<n;j++)
          {
            c[i][j]=0;
            for(int k=0;k<n;k++)
              c[i][j]=c[i][j]+a[i][k]*b[k][j];
          }
        }
//------------------------------------------------------------
        //Умножение матриц a и b, результат помещается в матрицу a
        void Proiz_m2(int n,float **a,float **b)
        {
          float **m;
          m=create_matr(n);
          Proiz_m1(n,a,b,m);
          copy_matr(n,m,a);
          free_matr(n,m);
        }
//------------------------------------------------------------
        //вычитание матриц: c=a-b
        void sub_matr(int n,float **a,float **b,float **c)
        {
          for(int i=0;i<n;i++)
          for(int j=0;j<n;j++)
           c[i][j]=a[i][j]-b[i][j];
        }

//------------------------------------------------------------
        //сложение матриц: c=a+b
        void sum_matr(int n,float **a,float **b,float **c)
        {
          for(int i=0;i<n;i++)
          for(int j=0;j<n;j++)
           c[i][j]=a[i][j]+b[i][j];
        }

//------------------------------------------------------------

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    int w = qApp->desktop()->width(); //ширина экрана
    w /= 2;
    w -= this->width()/2;
    int h = qApp->desktop()->height(); //высота экрана
    h /= 2;
    h -= this->height()/2;
    move(w, h);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionLoad_triggered()
{
    char s[50];
    f=fopen("D:\\MyDock\\Desktop\\SAOD\\PZ3\\INPUT.TXT","r");
    fscanf(f,"%s",s);
    fscanf(f,"%d",&k);
    m1=create_matr(k);
    Sozd_matr(k,m1);
    fscanf(f,"%s",s);
    m2=create_matr(k);
    Sozd_matr(k,m2);
    QMessageBox::information(NULL, QObject::tr("Загрузка данных"), QObject::tr("Данные загружены"));
}

void MainWindow::on_actionShow_triggered()
{
    ui->textBrowser->append(tr("Первая матрица"));
        int l=0;
        char *s1,s2[255]=""; int i,j;
        int ndig=sig;
        float x;
        s1=new char[sizeof(char)];
        for (i=0;i<k;i++){
        for (j=0;j<k;j++){
        x=m1[i][j];
        gcvt(x,ndig,s1);
        strcat(s2,s1);
        strcat(s2,"   ");
        }
        ui->textBrowser->append(s2);
        for (l=0;l<255;l++)
        s2[l]='\0';
        }

        ui->textBrowser->append(tr("Вторая матрица"));

        for (i=0;i<k;i++){
        for (j=0;j<k;j++){
        x=m2[i][j];
        gcvt(x,ndig,s1);
        strcat(s2,s1);
        strcat(s2,"   ");
        }
        ui->textBrowser->append(s2);
        for (l=0;l<255;l++)
        s2[l]='\0';
        }
        delete s1;
}

void MainWindow::on_actionFree_triggered()
{
    free_matr(k,m1);
        free_matr(k,m2);
        fclose(f);
        QMessageBox::information(NULL, QObject::tr("Освобождение памяти"), QObject::tr("Память освобождена"));
    }

void MainWindow::on_actionClear_triggered()
{
    ui->textBrowser->clear();
       ui->textBrowser_2->clear();
       ui->label_3->setText(tr("Результат"));
}

void MainWindow::on_actionSum_triggered()
{
    float **m3;
       ui->label_3->setText(tr("Сумма матриц"));
       ui->textBrowser_2->clear();
       m3=create_matr(k);
       sum_matr(k,m1,m2,m3);
       ui->textBrowser_2->append(tr("Сумма матриц"));
       int l=0;
       char *s1,s2[255]=""; int i,j;
       int ndig=sig;
       float x;
       s1=new char[sizeof(char)];
       for (i=0;i<k;i++){
       for (j=0;j<k;j++){
       x=m3[i][j];
       gcvt(x,ndig,s1);
       strcat(s2,s1);
       strcat(s2,"   ");
       }
       ui->textBrowser_2->append(s2);
       for (l=0;l<255;l++)
       s2[l]='\0';
       }
       delete s1;
}

void MainWindow::on_actionSub_triggered()
{
    float **m3;
        ui->label_3->setText(tr("Разность матриц"));
        ui->textBrowser_2->clear();
        m3=create_matr(k);
        sub_matr(k,m1,m2,m3);
        ui->textBrowser_2->append(tr("Разность матриц"));
        int l=0;
        char *s1,s2[255]=""; int i,j;
        int ndig=sig;
        float x;
        s1=new char[sizeof(char)];
        for (i=0;i<k;i++){
        for (j=0;j<k;j++){
        x=m3[i][j];
        gcvt(x,ndig,s1);
        strcat(s2,s1);
        strcat(s2,"   ");
        }
        ui->textBrowser_2->append(s2);
        for (l=0;l<255;l++)
        s2[l]='\0';
        }
        delete s1;
        free_matr(k,m3);
}

void MainWindow::on_actionProz_triggered()
{
    float **m3;
        ui->label_3->setText(tr("Произведение матриц"));
        ui->textBrowser_2->clear();
        m3=create_matr(k);
        Proiz_m1(k,m1,m2,m3);
        ui->textBrowser_2->append(tr("Произведение матриц"));
        int l=0;
        char *s1,s2[255]=""; int i,j;
        int ndig=sig;
        float x;
        s1=new char[sizeof(char)];
        for (i=0;i<k;i++){
        for (j=0;j<k;j++){
        x=m3[i][j];
        gcvt(x,ndig,s1);
        strcat(s2,s1);
        strcat(s2,"   ");
        }
        ui->textBrowser_2->append(s2);
        for (l=0;l<255;l++)
        s2[l]='\0';
        }
        delete s1;
        free_matr(k,m3);
}

void MainWindow::on_actionTrans_triggered()
{
    ui->label_3->setText(tr("Транспонирование матриц"));
        ui->textBrowser_2->clear();
        transp_matr(k,m1);
        ui->textBrowser_2->append(tr("Транспонированная матрица А"));
        int l=0;
        char *s1,s2[255]=""; int i,j;
        int ndig=sig;
        float x;
        s1=new char[sizeof(char)];
        for (i=0;i<k;i++){
        for (j=0;j<k;j++){
        x=m1[i][j];
        gcvt(x,ndig,s1);
        strcat(s2,s1);
        strcat(s2,"   ");
        }
        ui->textBrowser_2->append(s2);
        for (l=0;l<255;l++)
        s2[l]='\0';
        }
        for (l=0;l<255;l++)
        s2[l]='\0';
        transp_matr(k,m2);
        ui->textBrowser_2->append(tr("Транспонированная матрица Б"));
        for (i=0;i<k;i++){
        for (j=0;j<k;j++){
        x=m2[i][j];
        gcvt(x,ndig,s1);
        strcat(s2,s1);
        strcat(s2,"   ");
        }
        ui->textBrowser_2->append(s2);
        for (l=0;l<255;l++)
        s2[l]='\0';
        }
        delete s1;
}
