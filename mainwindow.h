#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QDebug>
#include <QTime>

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

private slots:
    void on_action_ffnen_triggered();

    void on_bps_valueChanged(int arg1);

    void on_Start_clicked();

    void on_lineEdit_editingFinished();

private:
    Ui::MainWindow *ui;
    QByteArray text;
    int bps = 10;
    int textlength;
    bool started = false;
};

#endif // MAINWINDOW_H
