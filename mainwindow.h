#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionLoad_triggered();

    void on_actionShow_triggered();

    void on_actionFree_triggered();

    void on_actionClear_triggered();

    void on_actionSum_triggered();

    void on_actionSub_triggered();

    void on_actionProz_triggered();

    void on_actionTrans_triggered();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
