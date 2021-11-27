#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void selectFilePath();
    void selectColor();
    void navigateFilePath();
    void navigateColor();

private:
    void initUI();
    void connectSignalSlots();
};
#endif // MAINWINDOW_H
