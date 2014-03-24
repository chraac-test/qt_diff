#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include "codeeditor.h"



namespace Ui {
class MainWindow;
}

class MainData;


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void onClickedLeftOpen();
    void onClickedRightOpen();
    void onClickedDiffSave();


private:
    Ui::MainWindow *ui;
    MainData *mainData;
};

#endif // MAINWINDOW_H
