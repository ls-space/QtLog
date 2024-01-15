#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "spdLoger.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    testLog();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::testLog()
{
    logger = new SpdLoger(this);
}

//daily test
void MainWindow::on_pushButton_clicked()
{
    QString strData = ui->lineEdit->text();
    logger->handleLog(strData,0,1);
}

void MainWindow::on_pushButton_2_clicked()
{
    QString strData = ui->lineEdit->text();
    logger->handleLog(strData,1,1);
}

void MainWindow::on_pushButton_3_clicked()
{
    QString strData = ui->lineEdit->text();
    logger->handleLog(strData,2,1);
}

void MainWindow::on_pushButton_4_clicked()
{
    QString strData = ui->lineEdit->text();
    logger->handleLog(strData,3,1);
}

//Rotat test
void MainWindow::on_pushButton_8_clicked()
{
    QString strData = ui->lineEdit->text();
    logger->handleLog(strData,0,0);
}

void MainWindow::on_pushButton_6_clicked()
{
    QString strData = ui->lineEdit->text();
    logger->handleLog(strData,1,0);
}

void MainWindow::on_pushButton_5_clicked()
{
    QString strData = ui->lineEdit->text();
    logger->handleLog(strData,2,0);
}

void MainWindow::on_pushButton_7_clicked()
{
    QString strData = ui->lineEdit->text();
    logger->handleLog(strData,3,0);
}

//all test
void MainWindow::on_pushButton_9_clicked()
{
    QString strData = ui->lineEdit->text();
    logger->handleLog(strData,0,2);
}

void MainWindow::on_pushButton_10_clicked()
{
    QString strData = ui->lineEdit->text();
    logger->handleLog(strData,1,2);
}

void MainWindow::on_pushButton_11_clicked()
{
    QString strData = ui->lineEdit->text();
    logger->handleLog(strData,2,2);
}

void MainWindow::on_pushButton_12_clicked()
{
    QString strData = ui->lineEdit->text();
    logger->handleLog(strData,3,2);
}
