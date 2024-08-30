//
// Created by Gularx on 2024/6/13.
//

#include "Administrative_page.h"

Administrative_page::Administrative_page(Mysql *mysql) {
    this->mysql = mysql;

//TODO:创建主页面
    this->setFixedSize(900,600);
    this->setWindowTitle("Administrative_page");

//TODO:创建管理员页面按钮
    Query_note = new QLabel("输入编号：");
    Query_note->setParent(this);
    Query_note->setFixedSize(100, 50);
    Query_note->move(550, 30);

    Query_input = new QLineEdit;
    Query_input->setParent(this);
    Query_input->setFixedSize(210, 30);
    Query_input->move(610, 40);

    Query = new QPushButton("查询");
    Query->setParent(this);
    Query->setFixedSize(60, 36);
    Query->move(830, 37);

    Equipment_display();

    connect(Query,&QPushButton::clicked,this,[=]{
        qDebug() << "查询页面";
        bool Query_login_OK = mysql->Query_login(Query_input->text(), &data);
        if(!Query_login_OK) {
            Fail_query();
        }
        else {
            Query_state = 1;
            Query_display();
            if(!Equipment_tableWidget->close()) Equipment_tableWidget->close();
            if(Query_tableWidget->close()) Query_tableWidget->show();
        }
    });
}

void Administrative_page::Equipment_display() {
    Equipment_tableWidget = new QTableWidget(1,9);
    Equipment_tableWidget->setParent(this);
    Equipment_tableWidget->setFixedSize(900,500);
    Equipment_tableWidget->move(0,100);
    Equipment_tableWidget->verticalHeader()->setVisible(false);
    Equipment_tableWidget->horizontalHeader()->setVisible(false);

    //TODO: 写入表头
    QString Text_login[7] = {"医疗设备名称","编号","生产日期","购买日期","购入人员名称","目前状态","使用人员名称"};
    for (int column = 0; column < 7; ++column) {
        QTableWidgetItem *item = new QTableWidgetItem(Text_login[column]);
        Equipment_tableWidget->setItem(0, column, item);
    }

    // 获取数据库的数据
    Data = mysql->Equipment_Select();

    // 在表格中添加数据 | 在数据库中读取
    for (int row = 1; row <= Data.size(); ++row) {
        int now_row = Equipment_tableWidget->rowCount(); // 获取当前行数
        Equipment_tableWidget->insertRow(now_row); // 插入新行
        QString Info[7];
        Info[0] = Data[row-1].Name;
        Info[1] = Data[row-1].Number;
        Info[2] = Data[row-1].Production_date;
        Info[3] = Data[row-1].Purchase_date;
        Info[4] = Data[row-1].Purchaser;
        Info[5] = Data[row-1].Status;
        Info[6] = Data[row-1].User_name;
        for (int column = 0; column < 9; ++column) {
            if(column < 7){
                QTableWidgetItem *item = new QTableWidgetItem(Info[column]);
                Equipment_tableWidget->setItem(row, column, item);
            }
            else if(column == 7){
                QPushButton *button = new QPushButton("出库");
                connect(button,&QPushButton::clicked,this,[=] {
                    mysql->administrative_sql(Info[1],"出库",UserName);
                    QTableWidgetItem *item0 = new QTableWidgetItem("出库");
                    Equipment_tableWidget->setItem(row, 5, item0);
                    QTableWidgetItem *item1 = new QTableWidgetItem(UserName);
                    Equipment_tableWidget->setItem(row, 6, item1);
                });
                Equipment_tableWidget->setCellWidget(row, column, button);
            }
            else if(column == 8){
                QPushButton *button = new QPushButton("入库");
                connect(button,&QPushButton::clicked,this,[=] {
                    mysql->administrative_sql(Info[1],"在库","无");
                    QTableWidgetItem *item = new QTableWidgetItem("在库");
                    Equipment_tableWidget->setItem(row, 5, item);
                    QTableWidgetItem *item1 = new QTableWidgetItem("无");
                    Equipment_tableWidget->setItem(row, 6, item1);
                });
                Equipment_tableWidget->setCellWidget(row, column, button);
            }
        }
    }
}

void Administrative_page::Query_display() {
    Query_tableWidget = new QTableWidget(2,9);
    Query_tableWidget->setParent(this);
    Query_tableWidget->setFixedSize(900,500);
    Query_tableWidget->move(0,100);
    Query_tableWidget->verticalHeader()->setVisible(false);
    Query_tableWidget->horizontalHeader()->setVisible(false);
    Query_tableWidget->close();

//TODO: 写入表头
    QString Text_login[7] = {"医疗设备名称","编号","生产日期","购买日期","购入人员名称","目前状态","使用人员名称"};
    for (int column = 0; column < 7; ++column) {
        QTableWidgetItem *item = new QTableWidgetItem(Text_login[column]);
        Query_tableWidget->setItem(0, column, item);
    }

    QString Info[7];
    Info[0] = data.Name;
    Info[1] = data.Number;
    Info[2] = data.Production_date;
    Info[3] = data.Purchase_date;
    Info[4] = data.Purchaser;
    Info[5] = data.Status;
    Info[6] = data.User_name;

    for (int column = 0; column < 9; ++column) {
        if(column < 7){
            QTableWidgetItem *item = new QTableWidgetItem(Info[column]);
            Query_tableWidget->setItem(1, column, item);
        }
        else if(column == 7){
            QPushButton *button = new QPushButton("出库");
            connect(button,&QPushButton::clicked,this,[=] {
                mysql->administrative_sql(Info[1],"出库",UserName);
                QTableWidgetItem *item0 = new QTableWidgetItem("出库");
                Query_tableWidget->setItem(1, 5, item0);
                QTableWidgetItem *item1 = new QTableWidgetItem(UserName);
                Query_tableWidget->setItem(1, 6, item1);
                Equipment_display();
            });
            Query_tableWidget->setCellWidget(1, column, button);
        }
        else if(column == 8){
            QPushButton *button = new QPushButton("入库");
            connect(button,&QPushButton::clicked,this,[=] {
                mysql->administrative_sql(Info[1],"在库","无");
                QTableWidgetItem *item0 = new QTableWidgetItem("在库");
                Query_tableWidget->setItem(1, 5, item0);
                QTableWidgetItem *item1 = new QTableWidgetItem("无");
                Query_tableWidget->setItem(1, 6, item1);
                Equipment_display();
            });
            Query_tableWidget->setCellWidget(1, column, button);
        }
    }
}

void Administrative_page::Fail_query() {
    Query_input->clear();

    QLabel *Query_fail = new QLabel("查询失败!");
    Query_fail->setParent(this);
    Query_fail->setFixedSize(100, 30);
    Query_fail->move(630,40);

    QTimer *timer = new QTimer;
    connect(timer, &QTimer::timeout, Query_fail, &QLabel::hide);
    timer->start(DELAYDE);         //启动定时器
    Query_fail->show();

    if(Query_state == 1) {
        Query_tableWidget->close();
        Equipment_tableWidget->show();
    }

    Query_state = 0;
}