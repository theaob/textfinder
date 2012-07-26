#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QtCore/QFile"
#include "QtCore/QTextStream"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    loadTextFile();
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

void MainWindow::loadTextFile()
{
    QFile inputFile(":/input.txt");
    inputFile.open(QIODevice::ReadOnly);

    QTextStream in(&inputFile);
    QString line = in.readAll();

    inputFile.close();

    ui->textEdit->setPlainText(line);

    QTextCursor cursor = ui->textEdit->textCursor();
    cursor.movePosition(QTextCursor::Start, QTextCursor::MoveAnchor, 1);

}
