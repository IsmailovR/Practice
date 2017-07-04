#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QHeaderView"
#include "QtMath"
#include "QDate"
#include "QTableWidgetItem"

MainWindow::MainWindow(QWidget *parent) :QMainWindow(parent),ui(new Ui::MainWindow){
    ui->setupUi(this);
    ui->mainDertTabl->setColumnWidth(0, 80);
    ui->mainDertTabl->setColumnWidth(1, 160);
    ui->mainDertTabl->setColumnWidth(2, 160);
    ui->interestChargesTab->setColumnWidth(0, 237);
    ui->interestChargesTab->setColumnWidth(1, 237);
    ui->interestChargesTab->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->interestChargesTab->setSelectionMode(QAbstractItemView::NoSelection);
    position1();
}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::on_pushButton_1_clicked()
{
    position1();
}

void MainWindow::on_pushButton_2_clicked()
{
    position2();
}

void MainWindow::on_pushMultiply_clicked(){
    action();
    operation="*";
    addElemaentNumer();
}

void MainWindow::on_pushDivide_clicked(){
    action();
    operation="/";
    addElemaentNumer();
}

void MainWindow::on_pushRoot_clicked(){
    action();
    operation="^(1/2)";
    addElemaentNumer();
}

void MainWindow::on_pushDelete_clicked(){
    answer=answer.left(answer.length()-1);
    addElemaentNumer();
}

void MainWindow::on_pushPlus_clicked(){
    action();
    operation="+";
    addElemaentNumer();
}

void MainWindow::on_pushMinus_clicked(){
    action();
    operation="-";
    addElemaentNumer();
}

void MainWindow::on_pushdot_clicked(){
    addElemaentNumer(".",true);
}

void MainWindow::on_pushEqually_clicked(){
    action();
    operation="=";
    action();
    addElemaentNumer();
}

void MainWindow::on_push1_clicked(){
    addElemaentNumer("1", true);
}

void MainWindow::on_push2_clicked(){
    addElemaentNumer("2", true);
}

void MainWindow::on_push3_clicked(){
    addElemaentNumer("3", true);
}

void MainWindow::on_push4_clicked(){
    addElemaentNumer("4", true);
}

void MainWindow::on_push5_clicked(){
    addElemaentNumer("5", true);
}

void MainWindow::on_push6_clicked(){
    addElemaentNumer("6", true);
}

void MainWindow::on_push7_clicked(){
    addElemaentNumer("7", true);
}

void MainWindow::on_push8_clicked(){
    addElemaentNumer("8", true);
}

void MainWindow::on_push9_clicked(){
    addElemaentNumer("9", true);
}

void MainWindow::on_push0_clicked(){
    addElemaentNumer("0", true);
}

void MainWindow::on_totals_clicked(){
    double amountRepayments=0.00;
    double amountReceipts=0.00;
    bool step=true;
    for(int i=0;i<ui->mainDertTabl->rowCount();i++){
        if(ui->mainDertTabl->item(i,2)==0 && ui->mainDertTabl->item(i,1)==0){
            ui->mainDertTabl->removeRow(i);
            i--;
            continue;
        }
        if(ui->mainDertTabl->item(i,1)!=0)
            amountRepayments+=ui->mainDertTabl->item(i,1)->text().toDouble();
        if(ui->mainDertTabl->item(i,2)!=0)
            amountReceipts+=ui->mainDertTabl->item(i,2)->text().toDouble();
    }
    if (amountRepayments==amountReceipts && step) {
        cleenInterestChargesTab();
        double totalAmount=0.00;
        double chargesCurrentPeriod=0.00;
        QDate iteratorDate=QDate();
        for (int i=1;i<ui->mainDertTabl->rowCount();i++){
            QList <QString> date;
            date=ui->mainDertTabl->item(i-1,0)->text().split(".");
            QString t2=date[2];
            QString t1=date[1];
            QString t0=date[0];
            iteratorDate=QDate(t2.toInt(),t1.toInt(),t0.toInt());
            iteratorDate=iteratorDate.addDays(1);
            if(ui->mainDertTabl->item(i-1,1)!=0)
                totalAmount+=ui->mainDertTabl->item(i-1,1)->text().toDouble();
            if(ui->mainDertTabl->item(i-1,2)!=0)
                totalAmount-=ui->mainDertTabl->item(i-1,2)->text().toDouble();
            date=ui->mainDertTabl->item(i,0)->text().split(".");
            QDate helpDate;
            t2=date[2];
            t1=date[1];
            t0=date[0];
            helpDate=QDate(t2.toInt(),t1.toInt(),t0.toInt());
            while( iteratorDate<=helpDate){
                chargesCurrentPeriod+=totalAmount*ui->percent->value()/(100*iteratorDate.daysInYear());
                if(  iteratorDate.day()==ui->days->value()){
                    ui->interestChargesTab->insertRow(ui->interestChargesTab->rowCount());
                    ui->interestChargesTab->setItem(ui->interestChargesTab->rowCount()-1,0,new QTableWidgetItem(iteratorDate.toString("dd.MM.yyyy")));
                    ui->interestChargesTab->setItem(ui->interestChargesTab->rowCount()-1,1,new QTableWidgetItem(QString::number(chargesCurrentPeriod)));
                    chargesCurrentPeriod=0.00;
                }
                if  ((iteratorDate.day()> iteratorDate.addDays(1).day()) && (iteratorDate.day()< ui->days->value())){
                    ui->interestChargesTab->insertRow(ui->interestChargesTab->rowCount());
                    ui->interestChargesTab->setItem(ui->interestChargesTab->rowCount()-1,0,new QTableWidgetItem(iteratorDate.toString("dd.MM.yyyy")));
                    ui->interestChargesTab->setItem(ui->interestChargesTab->rowCount()-1,1,new QTableWidgetItem(QString::number(chargesCurrentPeriod)));
                    chargesCurrentPeriod=0.00;
                }
                iteratorDate=iteratorDate.addDays(1);
            }
        }
        if  (iteratorDate.day()!=ui->days->value()){

            ui->interestChargesTab->insertRow(ui->interestChargesTab->rowCount());
            ui->interestChargesTab->setItem(ui->interestChargesTab->rowCount()-1,0,new QTableWidgetItem(iteratorDate.addDays(-1).toString("dd.MM.yyyy")));
            ui->interestChargesTab->setItem(ui->interestChargesTab->rowCount()-1,1,new QTableWidgetItem(QString::number(chargesCurrentPeriod)));
        }
        //cleenMainDertTabl();
    }else{
        (new QErrorMessage(this))->showMessage("Сумма поступлений не равна сумме погашений или не верно введена дата!");
    }

}

void MainWindow::on_addTabl_clicked(){
    ui->mainDertTabl->insertRow(ui->mainDertTabl->rowCount());
}

void MainWindow::position1(){
    ui->push0->show();
    ui->push1->show();
    ui->push2->show();
    ui->push3->show();
    ui->push4->show();
    ui->push5->show();
    ui->push6->show();
    ui->push7->show();
    ui->push8->show();
    ui->push9->show();
    ui->pushDelete->show();
    ui->pushDivide->show();
    ui->pushdot->show();
    ui->pushEqually->show();
    ui->pushMinus->show();
    ui->pushMultiply->show();
    ui->pushPlus->show();
    ui->pushRoot->show();
    ui->label->show();
    ui->addTabl->hide();
    ui->interestCharges->hide();
    ui->interestChargesTab->hide();
    ui->mainDert->hide();
    ui->mainDertTabl->hide();
    ui->labelDay->hide();
    ui->labelPercent->hide();
    ui->percent->hide();
    ui->days->hide();
    ui->totals->hide();
    ui->test1->hide();
    ui->test2->hide();
}

void MainWindow::position2(){
    ui->push0->hide();
    ui->push1->hide();
    ui->push2->hide();
    ui->push3->hide();
    ui->push4->hide();
    ui->push5->hide();
    ui->push6->hide();
    ui->push7->hide();
    ui->push8->hide();
    ui->push9->hide();
    ui->pushDelete->hide();
    ui->pushDivide->hide();
    ui->pushdot->hide();
    ui->pushEqually->hide();
    ui->pushMinus->hide();
    ui->pushMultiply->hide();
    ui->pushPlus->hide();
    ui->pushRoot->hide();
    ui->label->hide();
    ui->addTabl->show();
    ui->interestCharges->show();
    ui->interestChargesTab->show();
    ui->mainDert->show();
    ui->mainDertTabl->show();
    ui->labelDay->show();
    ui->labelPercent->show();
    ui->percent->show();
    ui->days->show();
    ui->totals->show();
    ui->test1->show();
    ui->test2->show();
}

void MainWindow::addElemaentNumer(QString numerElement, bool type){
    if (type)
        if (answer[0]!="0" && numerElement!=0)
            answer+=numerElement;
        else
            answer=numerElement;
    if (operation=="")
        ui->label->setText("\n"+answer);
    else
        ui->label->setText(numer+operation+"\n"+answer);
}

void MainWindow::action(){
    if(operation=="+"){
        double d =numer.toDouble();
        double k =answer.toDouble();
        answer=QString::number(d+k);
    }
    if(operation=="-"){
        double d =numer.toDouble();
        double k =answer.toDouble();
        answer=QString::number(d-k);
    }
    if(operation=="*"){
        double d =numer.toDouble();
        double k =answer.toDouble();
        answer=QString::number(d*k);
    }
    if(operation=="/"){
        double d =numer.toDouble();
        double k =answer.toDouble();
        if (k!=0)
            answer=QString::number(d/k);
        else{
            (new QErrorMessage(this))->showMessage("Деление на 0!");
            answer=QString::number(d);
        }
    }
    if(operation=="^(1/2)"){
        double d =numer.toDouble();
        answer=QString::number(qSqrt(d));
    }


    if(operation=="="){
        answer=numer;
        numer="";
        operation="";
    }else{
        numer=answer;
        answer="";
    }
}

void MainWindow::cleenMainDertTabl(){
    ui->mainDertTabl->clearContents();
    ui->mainDertTabl->setColumnCount(3);
    ui->mainDertTabl->setRowCount(0);
}

void MainWindow::cleenInterestChargesTab(){
    ui->interestChargesTab->clearContents();
    ui->interestChargesTab->setColumnCount(2);
    ui->interestChargesTab->setRowCount(0);
}

void MainWindow::on_test1_clicked(){
    cleenInterestChargesTab();
    cleenMainDertTabl();

    ui->mainDertTabl->insertRow(ui->mainDertTabl->rowCount());
    ui->mainDertTabl->setItem(ui->mainDertTabl->rowCount()-1,0,new QTableWidgetItem("25.09.2015"));
    ui->mainDertTabl->setItem(ui->mainDertTabl->rowCount()-1,1,new QTableWidgetItem("700000"));

    ui->mainDertTabl->insertRow(ui->mainDertTabl->rowCount());
    ui->mainDertTabl->setItem(ui->mainDertTabl->rowCount()-1,0,new QTableWidgetItem("16.11.2015"));
    ui->mainDertTabl->setItem(ui->mainDertTabl->rowCount()-1,2,new QTableWidgetItem("160000"));

    ui->mainDertTabl->insertRow(ui->mainDertTabl->rowCount());
    ui->mainDertTabl->setItem(ui->mainDertTabl->rowCount()-1,0,new QTableWidgetItem("12.12.2015"));
    ui->mainDertTabl->setItem(ui->mainDertTabl->rowCount()-1,2,new QTableWidgetItem("100000"));

    ui->mainDertTabl->insertRow(ui->mainDertTabl->rowCount());
    ui->mainDertTabl->setItem(ui->mainDertTabl->rowCount()-1,0,new QTableWidgetItem("20.01.2016"));
    ui->mainDertTabl->setItem(ui->mainDertTabl->rowCount()-1,2,new QTableWidgetItem("440000"));

    ui->mainDertTabl->insertRow(ui->mainDertTabl->rowCount());
    ui->mainDertTabl->setItem(ui->mainDertTabl->rowCount()-1,0,new QTableWidgetItem("12.02.2016"));
    ui->mainDertTabl->setItem(ui->mainDertTabl->rowCount()-1,1,new QTableWidgetItem("50000"));

    ui->mainDertTabl->insertRow(ui->mainDertTabl->rowCount());
    ui->mainDertTabl->setItem(ui->mainDertTabl->rowCount()-1,0,new QTableWidgetItem("08.04.2016"));
    ui->mainDertTabl->setItem(ui->mainDertTabl->rowCount()-1,2,new QTableWidgetItem("50000"));

    ui->percent->setValue(13.0);
    ui->days->setValue(31);

}

void MainWindow::on_test2_clicked(){
    cleenInterestChargesTab();
    cleenMainDertTabl();

    ui->mainDertTabl->insertRow(ui->mainDertTabl->rowCount());
    ui->mainDertTabl->setItem(ui->mainDertTabl->rowCount()-1,0,new QTableWidgetItem("02.06.2016"));
    ui->mainDertTabl->setItem(ui->mainDertTabl->rowCount()-1,1,new QTableWidgetItem("100"));

    ui->mainDertTabl->insertRow(ui->mainDertTabl->rowCount());
    ui->mainDertTabl->setItem(ui->mainDertTabl->rowCount()-1,0,new QTableWidgetItem("02.10.2016"));
    ui->mainDertTabl->setItem(ui->mainDertTabl->rowCount()-1,2,new QTableWidgetItem("100000"));

    ui->mainDertTabl->insertRow(ui->mainDertTabl->rowCount());
    ui->mainDertTabl->setItem(ui->mainDertTabl->rowCount()-1,0,new QTableWidgetItem("14.11.2016"));
    ui->mainDertTabl->setItem(ui->mainDertTabl->rowCount()-1,2,new QTableWidgetItem("100000"));

    ui->mainDertTabl->insertRow(ui->mainDertTabl->rowCount());
    ui->mainDertTabl->setItem(ui->mainDertTabl->rowCount()-1,0,new QTableWidgetItem("27.12.2016"));
    ui->mainDertTabl->setItem(ui->mainDertTabl->rowCount()-1,2,new QTableWidgetItem("100"));

    ui->percent->setValue(13.0);
    ui->days->setValue(31);

}
