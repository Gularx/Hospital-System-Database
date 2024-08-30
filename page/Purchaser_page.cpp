//
// Created by Gularx on 2024/6/13.
//

#include "Purchaser_page.h"

Purchaser_page::Purchaser_page(Mysql *mysql) {
    this->mysql = mysql;

//TODO:创建主页面
    this->setFixedSize(700,500);
    this->setWindowTitle("Purchaser_page");

    // 展示查询数据
    Equipment_login();

    // 填写添加按钮
    Append = new QPushButton("添加");
    Append->setParent(this);
    Append->setFixedSize(60, 40);
    Append->move(150, 20);

    // 填写提交按钮
    Submit = new QPushButton("提交");
    Submit->setParent(this);
    Submit->setFixedSize(60, 40);
    Submit->move(350, 20);
    Submit->close();

    connect(Append,&QPushButton::clicked,this,[=] {
        Append->close();
        Submit->show();
        int now_row = Login_tableWidget->rowCount(); // 获取当前行数
        int now_column = Login_tableWidget->columnCount();// 获取当前列数
        Login_tableWidget->insertRow(now_row); // 插入新行
        QTableWidgetItem *item0 = new QTableWidgetItem(UserName);
        Login_tableWidget->setItem(now_row, now_column - 2, item0);
        QTableWidgetItem *item1 = new QTableWidgetItem("入库");
        Login_tableWidget->setItem(now_row, now_column - 1, item1);
    });

    connect(Submit,&QPushButton::clicked,this,[=] {
        status = true;
        Submit->close();
        Append->show();
        int now_row = Login_tableWidget->rowCount(); // 获取当前行数
        int now_column = Login_tableWidget->columnCount();// 获取当前列数

        // 遍历读取数据
        for (int column = 0; column < now_column; ++column) {
            if(Login_tableWidget->item(now_row-1, column) == nullptr){
                Login_tableWidget->removeRow(now_row - 1);
                status = false;
                break;
            }
        }

        if(status) {
            Success_submit();
            QString device[now_column];
            for (int column = 0; column < now_column; ++column) {
                QTableWidgetItem *item = Login_tableWidget->item(now_row - 1, column);
                device[column] = item->text();
            }
            mysql->purchaser_sql(device);
        }
        else if(!status) Fail_submit();
    });
}

void Purchaser_page::Equipment_login() {
    Login_tableWidget = new QTableWidget(1,6);
    Login_tableWidget->setParent(this);
    Login_tableWidget->setFixedSize(600,500);
    Login_tableWidget->move(50, 70);
    Login_tableWidget->verticalHeader()->setVisible(false);
    Login_tableWidget->horizontalHeader()->setVisible(false);

    //TODO: 写入表头
    QString Text_login[6] = {"医疗设备名称","编号","生产日期","购买日期","购入人员名称","目前状态"};
    for (int column = 0; column < 6; ++column) {
        QTableWidgetItem *item = new QTableWidgetItem(Text_login[column]);
        Login_tableWidget->setItem(0, column, item);
    }

    // 获取数据库的数据
    Data = mysql->Equipment_Select();

    // 在表格中添加数据 | 在数据库中读取
    for (int row = 1; row <= Data.size(); ++row) {
        int now_row = Login_tableWidget->rowCount(); // 获取当前行数
        Login_tableWidget->insertRow(now_row); // 插入新行
        QString Info[6];
        Info[0] = Data[row-1].Name;
        Info[1] = Data[row-1].Number;
        Info[2] = Data[row-1].Production_date;
        Info[3] = Data[row-1].Purchase_date;
        Info[4] = Data[row-1].Purchaser;
        Info[5] = Data[row-1].Status;
        for (int column = 0; column < 6; ++column) {
                QTableWidgetItem *item = new QTableWidgetItem(Info[column]);
                Login_tableWidget->setItem(row, column, item);
        }
    }
}

void Purchaser_page::Fail_submit() {
    QLabel *Submit_fail = new QLabel("提交失败!");
    Submit_fail->setParent(this);
    Submit_fail->setFixedSize(100, 30);
    Submit_fail->move(250,25);

    QTimer *timer = new QTimer;
    connect(timer, &QTimer::timeout, Submit_fail, &QLabel::hide);
    timer->start(DELAYDE);         //启动定时器
    Submit_fail->show();
}

void Purchaser_page::Success_submit() {
    QLabel *Submit_success = new QLabel("添加成功!");
    Submit_success->setParent(this);
    Submit_success->setFixedSize(100, 30);
    Submit_success->move(250,25);

    QTimer *timer = new QTimer;
    connect(timer, &QTimer::timeout, Submit_success, &QLabel::hide);
    timer->start(DELAYDE);         //启动定时器
    Submit_success->show();
}