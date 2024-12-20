#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , you(true)
    , first(true)
{
    ui->setupUi(this);
    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::OnSendButton);
    connect(ui->otherButton, &QPushButton::clicked, this, &MainWindow::OnOtherButton);
    connect(ui->youButton, &QPushButton::clicked, this, &MainWindow::OnYouButton);
    OnYouButton();
    ui->textEdit->setStyleSheet("QTextEdit { padding-left: 50px; padding-right: 15%; padding-top: 50px; padding-down: 50px}");
    ui->textEdit->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::OnSendButton()
{
    QString speaker;
    if (you == true)
    {
        speaker = "Vous";
    }
    else
    {
        speaker = "Autre";
    }
    if (ui->textEdit->toPlainText() != "")
    {
        ui->label->setText(ui->label->toPlainText() + "" + speaker + " : " + ui->textEdit->toPlainText() + "\n\n");
        ui->textEdit->setPlainText("");
        repaint();
    }
    first = false;
}

void MainWindow::OnYouButton()
{
    you = true;
    ui->youButton->setStyleSheet("background-color:#babaf5");
    ui->otherButton->setStyleSheet("background-color:#f5f5f5");
}

void MainWindow::OnOtherButton()
{
    you = false;
    ui->youButton->setStyleSheet("background-color:#f5f5f5");
    ui->otherButton->setStyleSheet("background-color:#babaf5");
}
