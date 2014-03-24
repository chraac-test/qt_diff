#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "maindata.h"
#include <qfiledialog>



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow()),
    mainData(new MainData(this))
{
    ui->setupUi(this);

    connect(ui->openButtonLeft, SIGNAL(clicked()), this, SLOT(onClickedLeftOpen()));
    connect(ui->openButtonRight, SIGNAL(clicked()), this, SLOT(onClickedRightOpen()));


    connect(ui->lineEditLeft,
            SIGNAL(textChanged(const QString &)),
            mainData,
            SLOT(changeLeftFile(const QString &)));

    connect(ui->lineEditRight,
            SIGNAL(textChanged(const QString &)),
            mainData,
            SLOT(changeRightFile(const QString &)));


    connect(mainData,
            SIGNAL(leftFileTextChanged(const QString &)),
            ui->plainTextEditLeft,
            SLOT(setPlainText(const QString &)));

    connect(mainData,
            SIGNAL(rightFileTextChanged(const QString &)),
            ui->plainTextEditRight,
            SLOT(setPlainText(const QString &)));

    connect(mainData,
            SIGNAL(diffTextChanged(const QString &)),
            ui->plainTextEditDiff,
            SLOT(setPlainText(const QString &)));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::onClickedLeftOpen()
{
    emit ui->lineEditLeft->setText(QFileDialog::getOpenFileName(this, tr("Open")));
}

void MainWindow::onClickedRightOpen()
{
    emit ui->lineEditRight->setText(QFileDialog::getOpenFileName(this, tr("Open")));
}
