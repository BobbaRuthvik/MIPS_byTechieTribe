#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>
#include <utility>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void edit(QString s);
    void showMessage(QString s);
    void showStalls_1(std::pair<std::vector<int>, std::pair<int, double>> p);
    void showStalls_2(std::pair<std::vector<int>, std::pair<int, double>> p);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_checkBox_stateChanged(int arg1);

protected:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H

