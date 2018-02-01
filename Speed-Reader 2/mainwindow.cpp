#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":/SR.png"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::start()
{
    while(text.length()>0 && started){
        absCounter++;
        if(text.mid(36,10).contains("||")){
            text.remove(text.indexOf("||",36),2);
            absCounter-=2;
            ui->textLabel->setText(text);
            QTime dieTime= QTime::currentTime().addMSecs(newLineTime);
            while (QTime::currentTime() < dieTime)
                QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
        }
        else if(counter >= bps/10){
            text.remove(0,1+counter);
            counter = 0;
            QTextCursor tc = ui->textEdit->textCursor();
            tc.setPosition(absCounter);
            ui->textEdit->setTextCursor(tc);
        }
        else if(counter>text.length()){
            ui->textLabel->setText("");
            on_Start_clicked();
            ui->progressBar->setValue(100);
            break;
        }
        else
            counter++;

        ui->textLabel->setText(text);
        ui->progressBar->setValue(100-100*text.length()/textlength);
        ui->timeLabel->setText(toTime(text));
        QTime dieTime= QTime::currentTime().addMSecs(1000/bps);
        while (QTime::currentTime() < dieTime)
            QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }
    started = false;
    ui->Start->setText("Start!");
}

QString MainWindow::toTime(QString remainingText)
{
    int remLength = remainingText.length();
    double remSeconds = (double) remLength/bps;

    int newLineCounter = remainingText.count(" || ");

    remSeconds += newLineCounter*(double)newLineTime/1000;
    remSeconds += remSeconds/60;

    int minCounter = 0;
    while (remSeconds >= 60){
        remSeconds -= 60;
        minCounter++;
    }
    QString secString = QString::number(floor(remSeconds));
    if(remSeconds<10)
        secString = "0"+secString;

    return QString::number(minCounter)+":"+secString;
}

void MainWindow::on_action_ffnen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this,tr("Open text file"), "", tr("TXT Files (*.txt)"));

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    while (!file.atEnd()){
        text = QString(file.readAll());

        text.replace("\n"," ");
        while(text.contains("  "))
            text.replace("  "," ");

        ui->textLabel->setText(text);
        textlength = text.length();
    }
}

void MainWindow::on_bps_valueChanged(int arg1)
{
    bps = arg1*7/60;
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

void MainWindow::on_textEdit_textChanged()
{
    absCounter = 0;
    text.clear();
    text.append(ui->textEdit->toPlainText());
    text.replace("\n"," || ");
    while(text.contains("  "))
          text.replace("  "," ");

    ui->textLabel->setText(text);
    textlength = text.length();
}
