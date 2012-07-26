#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QtCore/QFile"
#include "QtCore/QTextStream"
#include "QSystemTrayIcon"
#include "QIcon"
#include "QIconEngine"
#include "QFileDialog"
#include "QMessageBox"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //loadTextFile();
    //QSystemTrayIcon tray = new QSystemTrayIcon();
    //tray.showMessage("Hello","World");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_findButton_clicked()
{
    QString searchString = ui->lineEdit->text();

    if(!ui->textEdit->find(searchString, QTextDocument::FindWholeWords))
    {
        ui->textEdit->find(searchString, QTextDocument::FindBackward);
    }
}

void MainWindow::loadTextFile(const QString *name)
{
    QFile inputFile(*name);
    inputFile.open(QIODevice::ReadOnly);

    QTextStream in(&inputFile);
    QString line = in.readAll();

    inputFile.close();

    ui->textEdit->setPlainText(line);

    QTextCursor cursor = ui->textEdit->textCursor();
    cursor.movePosition(QTextCursor::Start, QTextCursor::MoveAnchor, 1);

}

void MainWindow::on_pushButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("Text Files (*.txt);;C++ Files (*.cpp *.h);;All Files (*.*)"));
    if (fileName != "")
    {
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly)) {
            QMessageBox::critical(this, tr("Error"), tr("Could not open file"));
            return;
        }
        loadTextFile(&fileName);
    }
}
