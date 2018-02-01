#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QDebug>
#include <QTime>
#include <QRegularExpression>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void start();
    QString toTime(QString remainingText);

private slots:
    void on_action_ffnen_triggered();

    void on_bps_valueChanged(int arg1);

    void on_Start_clicked();

    void on_textEdit_textChanged();

private:
    Ui::MainWindow *ui;
    QString text;
    int bps = 50;
    int newLineTime = 500;
    int textlength;
    bool started = false;
    int counter = 0, absCounter = 0;
};

#endif // MAINWINDOW_H
