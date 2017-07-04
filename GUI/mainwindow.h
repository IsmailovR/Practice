#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "QString"
#include "QErrorMessage"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushMultiply_clicked();
    void on_pushDivide_clicked();
    void on_push6_clicked();
    void on_pushRoot_clicked();
    void on_pushDelete_clicked();
    void on_push7_clicked();
    void on_push8_clicked();
    void on_push9_clicked();
    void on_pushMinus_clicked();
    void on_push4_clicked();
    void on_push5_clicked();
    void on_pushPlus_clicked();
    void on_push3_clicked();
    void on_push2_clicked();
    void on_push1_clicked();
    void on_push0_clicked();
    void on_pushdot_clicked();
    void on_pushEqually_clicked();
    void on_pushButton_1_clicked();
    void on_pushButton_2_clicked();
    void on_totals_clicked();
    void on_addTabl_clicked();
    void on_test1_clicked();
    void on_test2_clicked();

private:
    Ui::MainWindow *ui;
    QString numer="0";
    QString answer="";
    QString operation="";
    void position1();
    void position2();
    void addElemaentNumer(QString numerElement="0", bool type=false);
    void action();
    void cleenMainDertTabl();
    void cleenInterestChargesTab();

};

#endif // MAINWINDOW_H
