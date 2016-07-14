#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::start()
{
    while(text.length()>0 && started){
        text.remove(0,1);
        ui->label->setText(text);
        ui->progressBar->setValue(100-100*text.length()/textlength);
        QTime dieTime= QTime::currentTime().addMSecs(1000/bps);
        while (QTime::currentTime() < dieTime)
            QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }
    started = false;
    ui->Start->setText("Start!");
}

void MainWindow::on_action_ffnen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this,tr("Open lens system"), "", tr("TXT Files (*.txt)"));

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    while (!file.atEnd()){
        text = file.readAll();

        text.replace("\n"," ");
        while(text.contains("  "))
              text.replace("  "," ");

        ui->label->setText(text);
        textlength = text.length();
    }
}

void MainWindow::on_bps_valueChanged(int arg1)
{
    bps = arg1;
}

void MainWindow::on_Start_clicked()
{
    if(text.length()>0 && !started){
        started = true;
        ui->Start->setText("Pause");
        start();
    }
    else{
        started = false;
        ui->Start->setText("Start!");
    }
}

void MainWindow::on_lineEdit_editingFinished()
{
    text.clear();
    text.append(ui->lineEdit->text());
    text.replace("\n"," ");
    while(text.contains("  "))
          text.replace("  "," ");

    ui->label->setText(text);
    textlength = text.length();
}
