//
// Created by Gularx on 2024/6/14.
//

#include "General_page.h"

General_page::General_page(Mysql *mysql) {
    this->mysql = mysql;

//TODO:创建主页面
    this->setFixedSize(400,500);
    this->setWindowTitle("Administrative_page");

    Export = new QPushButton("导出");
    Export->setParent(this);
    Export->setFixedSize(120, 50);
    Export->move(140, 60);

    Equipment = new QPushButton("查询仪器表");
    Equipment->setParent(this);
    Equipment->setFixedSize(120, 50);
    Equipment->move(140, 150);

    Administer = new QPushButton("查询管理人员表");
    Administer->setParent(this);
    Administer->setFixedSize(120, 50);
    Administer->move(140, 240);

    Purchaser = new QPushButton("查询购入人员表");
    Purchaser->setParent(this);
    Purchaser->setFixedSize(120, 50);
    Purchaser->move(140, 330);

    Equipment_display();
    Administer_display();
    Purchaser_display();

    connect(Export,&QPushButton::clicked,this,[=] {
        ExportDataToExcel();
    });

    connect(Equipment,&QPushButton::clicked,this,[=] {
        Equipment_tableWidget->show();
    });

    connect(Administer,&QPushButton::clicked,this,[=] {
        Administer_update->show();
    });

    connect(Purchaser,&QPushButton::clicked,this,[=] {
        Purchaser_update->show();
    });
}

void General_page::ExportDataToExcel() {
    QAxObject *excel = new QAxObject(this);

    // 尝试启动一个Excel实例
    excel->setControl("Excel.Application");
    excel->setProperty("Visible", false);

    // 创建一个新的工作簿
    QAxObject *workbooks = excel->querySubObject("Workbooks");
    QAxObject *workbook_1 = workbooks->querySubObject("Add");
    QAxObject *workbook_2 = workbooks->querySubObject("Add");
    QAxObject *workbook_3 = workbooks->querySubObject("Add");

    // 获取工作表
    QAxObject *worksheet_1 = workbook_1->querySubObject("Worksheets(int)", 1);
    QAxObject *worksheet_2 = workbook_2->querySubObject("Worksheets(int)", 1);
    QAxObject *worksheet_3 = workbook_3->querySubObject("Worksheets(int)", 1);

    // 选择一个区域进行数据填充，这里假设我们有一些数据要导出
    QString Text[7] = {"医疗设备名称","编号","生产日期","购买日期","购入人员名称","目前状态","使用人员名称"};
    for (int column = 1; column <= 7; ++column) {
        QAxObject *range = worksheet_1->querySubObject("Cells(int,int)", 1,column);
        range->dynamicCall("Value", Text[column-1]);
    }
    std::vector<equipment_t> equipment_t_Data = mysql->Equipment_Select();
    for (int i = 2; i < 2+equipment_t_Data.size(); ++i) {
        QAxObject *Name = worksheet_1->querySubObject("Cells(int,int)", i,1);
        Name->dynamicCall("Value", equipment_t_Data[i-2].Name);
        QAxObject *Number = worksheet_1->querySubObject("Cells(int,int)", i,2);
        Number->dynamicCall("Value", equipment_t_Data[i-2].Number);
        QAxObject *Production_date = worksheet_1->querySubObject("Cells(int,int)", i,3);
        Production_date->dynamicCall("Value", equipment_t_Data[i-2].Production_date);
        QAxObject *Purchase_date = worksheet_1->querySubObject("Cells(int,int)", i,4);
        Purchase_date->dynamicCall("Value", equipment_t_Data[i-2].Purchase_date);
        QAxObject *Purchaser = worksheet_1->querySubObject("Cells(int,int)", i,5);
        Purchaser->dynamicCall("Value", equipment_t_Data[i-2].Purchaser);
        QAxObject *Status = worksheet_1->querySubObject("Cells(int,int)", i,6);
        Status->dynamicCall("Value", equipment_t_Data[i-2].Status);
        QAxObject *User_name = worksheet_1->querySubObject("Cells(int,int)", i,7);
        User_name->dynamicCall("Value", equipment_t_Data[i-2].User_name);
    }

    QString Text_Administrative[5] = {"姓名","编号","性别","生日","入职日期"};
    for (int column = 1; column <= 5; ++column) {
        QAxObject *range = worksheet_2->querySubObject("Cells(int,int)", 1,column);
        range->dynamicCall("Value", Text_Administrative[column-1]);
    }
    std::vector<person_t> Administrative_Data = mysql->Administrative_Select();
    for (int i = 2; i < 2+Administrative_Data.size(); ++i) {
        QAxObject *Name = worksheet_2->querySubObject("Cells(int,int)", i,1);
        Name->dynamicCall("Value", Administrative_Data[i-2].Name);
        QAxObject *ID = worksheet_2->querySubObject("Cells(int,int)", i,2);
        ID->dynamicCall("Value", Administrative_Data[i-2].ID);
        QAxObject *Gender = worksheet_2->querySubObject("Cells(int,int)", i,3);
        Gender->dynamicCall("Value", Administrative_Data[i-2].Gender);
        QAxObject *Birthday = worksheet_2->querySubObject("Cells(int,int)", i,4);
        Birthday->dynamicCall("Value", Administrative_Data[i-2].Birthday);
        QAxObject *Date_of_employment = worksheet_2->querySubObject("Cells(int,int)", i,5);
        Date_of_employment->dynamicCall("Value", Administrative_Data[i-2].Date_of_employment);
    }

    QString Text_Purchaser[5] = {"姓名","编号","性别","生日","入职日期"};
    for (int column = 1; column <= 5; ++column) {
        QAxObject *range = worksheet_3->querySubObject("Cells(int,int)", 1,column);
        range->dynamicCall("Value", Text_Purchaser[column-1]);
    }
    std::vector<person_t> Purchaser_Data = mysql->Purchaser_Select();
    for (int i = 2; i < 2+Purchaser_Data.size(); ++i) {
        QAxObject *Name = worksheet_3->querySubObject("Cells(int,int)", i,1);
        Name->dynamicCall("Value", Purchaser_Data[i-2].Name);
        QAxObject *ID = worksheet_3->querySubObject("Cells(int,int)", i,2);
        ID->dynamicCall("Value", Purchaser_Data[i-2].ID);
        QAxObject *Gender = worksheet_3->querySubObject("Cells(int,int)", i,3);
        Gender->dynamicCall("Value", Purchaser_Data[i-2].Gender);
        QAxObject *Birthday = worksheet_3->querySubObject("Cells(int,int)", i,4);
        Birthday->dynamicCall("Value", Purchaser_Data[i-2].Birthday);
        QAxObject *Date_of_employment = worksheet_3->querySubObject("Cells(int,int)", i,5);
        Date_of_employment->dynamicCall("Value", Purchaser_Data[i-2].Date_of_employment);
    }

    // 导出工作表到一个文件
    QString filename_1 = "/equipment.xlsx";
    QString Path = QCoreApplication::applicationDirPath() + filename_1;
    worksheet_1->dynamicCall("SaveAs(const QString&)", QDir::toNativeSeparators(Path));
    // 导出工作表到一个文件
    QString filename_2 = "/administrative.xlsx";
    QString Path_2 = QCoreApplication::applicationDirPath() + filename_2;
    worksheet_2->dynamicCall("SaveAs(const QString&)", QDir::toNativeSeparators(Path_2));
    // 导出工作表到一个文件
    QString filename_3 = "/Purchaser.xlsx";
    QString Path_3 = QCoreApplication::applicationDirPath() + filename_3;
    worksheet_3->dynamicCall("SaveAs(const QString&)", QDir::toNativeSeparators(Path_3));

    // 清理资源
    workbook_1->dynamicCall("Close()");
    workbook_2->dynamicCall("Close()");
    workbook_3->dynamicCall("Close()");
    workbooks->dynamicCall("Close()");
    excel->dynamicCall("Quit()");

    workbook_1->setParent(0);
    workbook_2->setParent(0);
    workbook_3->setParent(0);
    worksheet_1->setParent(0);
    worksheet_2->setParent(0);
    worksheet_3->setParent(0);
    workbooks->setParent(0);
    excel->setParent(0);

    delete workbook_1;
    delete workbook_2;
    delete workbook_3;
    delete worksheet_1;
    delete worksheet_2;
    delete worksheet_3;
    delete workbooks;
    delete excel;
}

void General_page::Equipment_display() {
    Equipment_tableWidget = new QTableWidget(1,7);
    Equipment_tableWidget->setFixedSize(700,500);
    Equipment_tableWidget->move(100,100);
    Equipment_tableWidget->verticalHeader()->setVisible(false);
    Equipment_tableWidget->horizontalHeader()->setVisible(false);

    //TODO: 写入表头
    QString Text_login[7] = {"医疗设备名称","编号","生产日期","购买日期","购入人员名称","目前状态","使用人员名称"};
    for (int column = 0; column < 7; ++column) {
        QTableWidgetItem *item = new QTableWidgetItem(Text_login[column]);
        Equipment_tableWidget->setItem(0, column, item);
    }

    // 获取数据库的数据
    Equipment_data = mysql->Equipment_Select();

    // 在表格中添加数据 | 在数据库中读取
    for (int row = 1; row <= Equipment_data.size(); ++row) {
        int now_row = Equipment_tableWidget->rowCount(); // 获取当前行数
        Equipment_tableWidget->insertRow(now_row); // 插入新行
        QString Info[7];
        Info[0] = Equipment_data[row-1].Name;
        Info[1] = Equipment_data[row-1].Number;
        Info[2] = Equipment_data[row-1].Production_date;
        Info[3] = Equipment_data[row-1].Purchase_date;
        Info[4] = Equipment_data[row-1].Purchaser;
        Info[5] = Equipment_data[row-1].Status;
        Info[6] = Equipment_data[row-1].User_name;
        for (int column = 0; column < 7; ++column) {
            QTableWidgetItem *item = new QTableWidgetItem(Info[column]);
            Equipment_tableWidget->setItem(row, column, item);
        }
    }
    Equipment_tableWidget->close();
}

void General_page::Administer_display() {
    Administer_update = new QWidget;
    Administer_update->setFixedSize(800,500);
    Administer_update->setWindowTitle("Administer_update");

    QPushButton *Append = new QPushButton("添加");
    Append->setParent(Administer_update);
    Append->setFixedSize(60,30);
    Append->move(50,20);

    QPushButton *Append_finish = new QPushButton("提交");
    Append_finish->setParent(Administer_update);
    Append_finish->setFixedSize(60,30);
    Append_finish->move(50,20);
    Append_finish->close();

    QPushButton *Delete = new QPushButton("删除");
    Delete->setParent(Administer_update);
    Delete->setFixedSize(60,30);
    Delete->move(250,20);

    QPushButton *Delete_finish = new QPushButton("删除完成");
    Delete_finish->setParent(Administer_update);
    Delete_finish->setFixedSize(60,30);
    Delete_finish->move(250,20);
    Delete_finish->close();

    Administer_tableWidget = new QTableWidget(1,6);
    Administer_tableWidget->setParent(Administer_update);
    Administer_tableWidget->setFixedSize(700,500);
    Administer_tableWidget->move(50,50);
    Administer_tableWidget->verticalHeader()->setVisible(false);
    Administer_tableWidget->horizontalHeader()->setVisible(false);

    //TODO: 写入表头
    QString Text_login[5] = {"管理人员名称","编号","性别","出生日期","就职日期"};
    for (int column = 0; column < 5; ++column) {
        QTableWidgetItem *item = new QTableWidgetItem(Text_login[column]);
        Administer_tableWidget->setItem(0, column, item);
    }

    // 获取数据库的数据
    Administer_data = mysql->Administrative_Select();

    // 在表格中添加数据 | 在数据库中读取
    for (int row = 1; row <= Administer_data.size(); ++row) {
        int now_row = Administer_tableWidget->rowCount(); // 获取当前行数
        Administer_tableWidget->insertRow(now_row); // 插入新行
        QString Info[5];
        Info[0] = Administer_data[row-1].Name;
        Info[1] = Administer_data[row-1].ID;
        Info[2] = Administer_data[row-1].Gender;
        Info[3] = Administer_data[row-1].Birthday;
        Info[4] = Administer_data[row-1].Date_of_employment;
        for (int column = 0; column < 5; ++column) {
                QTableWidgetItem *item = new QTableWidgetItem(Info[column]);
                Administer_tableWidget->setItem(row, column, item);
        }
    }

    connect(Append,&QPushButton::clicked,Administer_update,[=] {
        Append->close();
        Append_finish->show();
        int now_row = Administer_tableWidget->rowCount(); // 获取当前行数
        Administer_tableWidget->insertRow(now_row); // 插入新行
    });

    connect(Append_finish,&QPushButton::clicked,Administer_update,[=] {
        status = true;
        Append_finish->close();
        Append->show();

        int now_row = Administer_tableWidget->rowCount(); // 获取当前行数
        int now_column = Administer_tableWidget->columnCount();// 获取当前列数

        // 遍历读取数据
        for (int column = 0; column < now_column - 1; ++column) {
            if(Administer_tableWidget->item(now_row-1, column) == nullptr){
                Administer_tableWidget->removeRow(now_row - 1);
                status = false;
                break;
            }
        }

        if(status) {
            Success = new QLabel("添加成功!");
            Success->setParent(Administer_update);
            Submit_success();

            QString device[now_column - 1];
            for (int column = 0; column < now_column - 1; ++column) {
                QTableWidgetItem *item = Administer_tableWidget->item(now_row - 1, column);
                device[column] = item->text();
            }
            mysql->Administer_sql(device);
        }
        else if(!status) {
            Fail = new QLabel("添加失败!");
            Fail->setParent(Administer_update);
            Submit_fail();
        }
    });

    connect(Delete,&QPushButton::clicked,Administer_update,[=] {
        Delete->close();
        Delete_finish->show();
        // 获取数据库的数据
        Administer_data = mysql->Administrative_Select();
        // 在表格中添加数据 | 在数据库中读取
        for (int row = 1; row <= Administer_data.size(); ++row) {
            QPushButton *Delete_button = new QPushButton("删除");
            Administer_tableWidget->setCellWidget(row, 5, Delete_button);
            connect(Delete_button,&QPushButton::clicked, Administer_update,[=]{
                QString ID = Administer_tableWidget->item(row,1)->text();
                mysql->Administer_append_sql(ID);
                Administer_tableWidget->setCellWidget(row, 5, NULL);
            });
        }
    });

    connect(Delete_finish,&QPushButton::clicked,Administer_update,[=] {
        Success = new QLabel("删除完成!");
        Success->setParent(Administer_update);
        Delete_success();

        Delete_finish->close();
        Delete->show();
        int now_row = Administer_tableWidget->rowCount();
        while(now_row > 0) {
            // 删除当前行
            Administer_tableWidget->removeRow(now_row);
            now_row--;
        }
//        for (int row = 1; row < now_row; row++) {
//            Administer_tableWidget->setCellWidget(row, 5, NULL);
//        }
        // 获取数据库的数据
        Administer_data = mysql->Administrative_Select();
        // 在表格中添加数据 | 在数据库中读取
        for (int row = 1; row <= Administer_data.size(); ++row) {
            int now_row = Administer_tableWidget->rowCount();
            Administer_tableWidget->insertRow(now_row); // 插入新行
            QString Info[5];
            Info[0] = Administer_data[row-1].Name;
            Info[1] = Administer_data[row-1].ID;
            Info[2] = Administer_data[row-1].Gender;
            Info[3] = Administer_data[row-1].Birthday;
            Info[4] = Administer_data[row-1].Date_of_employment;
            for (int column = 0; column < 5; ++column) {
                QTableWidgetItem *item = new QTableWidgetItem(Info[column]);
                Administer_tableWidget->setItem(row, column, item);
            }
        }
    });

    Administer_update->close();
}

void General_page::Purchaser_display() {
    Purchaser_update = new QWidget;
    Purchaser_update->setFixedSize(800,500);
    Purchaser_update->setWindowTitle("Purchaser_update");

    QPushButton *Append = new QPushButton("添加");
    Append->setParent(Purchaser_update);
    Append->setFixedSize(60,30);
    Append->move(50,20);

    QPushButton *Append_finish = new QPushButton("提交");
    Append_finish->setParent(Purchaser_update);
    Append_finish->setFixedSize(60,30);
    Append_finish->move(50,20);
    Append_finish->close();

    QPushButton *Delete = new QPushButton("删除");
    Delete->setParent(Purchaser_update);
    Delete->setFixedSize(60,30);
    Delete->move(250,20);

    QPushButton *Delete_finish = new QPushButton("删除完成");
    Delete_finish->setParent(Purchaser_update);
    Delete_finish->setFixedSize(60,30);
    Delete_finish->move(250,20);
    Delete_finish->close();

    Purchaser_tableWidget = new QTableWidget(1,6);
    Purchaser_tableWidget->setParent(Purchaser_update);
    Purchaser_tableWidget->setFixedSize(700,500);
    Purchaser_tableWidget->move(50,50);
    Purchaser_tableWidget->verticalHeader()->setVisible(false);
    Purchaser_tableWidget->horizontalHeader()->setVisible(false);

    //TODO: 写入表头
    QString Text_login[5] = {"管理人员名称","编号","性别","出生日期","就职日期"};
    for (int column = 0; column < 5; ++column) {
        QTableWidgetItem *item = new QTableWidgetItem(Text_login[column]);
        Purchaser_tableWidget->setItem(0, column, item);
    }

    // 获取数据库的数据
    Purchaser_data = mysql->Purchaser_Select();

    // 在表格中添加数据 | 在数据库中读取
    for (int row = 1; row <= Purchaser_data.size(); ++row) {
        int now_row = Purchaser_tableWidget->rowCount(); // 获取当前行数
        Purchaser_tableWidget->insertRow(now_row); // 插入新行
        QString Info[5];
        Info[0] = Purchaser_data[row-1].Name;
        Info[1] = Purchaser_data[row-1].ID;
        Info[2] = Purchaser_data[row-1].Gender;
        Info[3] = Purchaser_data[row-1].Birthday;
        Info[4] = Purchaser_data[row-1].Date_of_employment;
        for (int column = 0; column < 5; ++column) {
            QTableWidgetItem *item = new QTableWidgetItem(Info[column]);
            Purchaser_tableWidget->setItem(row, column, item);
        }
    }

    connect(Append,&QPushButton::clicked,Purchaser_update,[=] {
        Append->close();
        Append_finish->show();
        int now_row = Purchaser_tableWidget->rowCount(); // 获取当前行数
        Purchaser_tableWidget->insertRow(now_row); // 插入新行
    });

    connect(Append_finish,&QPushButton::clicked,Purchaser_update,[=] {
        status = true;
        Append_finish->close();
        Append->show();

        int now_row = Purchaser_tableWidget->rowCount(); // 获取当前行数
        int now_column = Purchaser_tableWidget->columnCount();// 获取当前列数

        // 遍历读取数据
        for (int column = 0; column < now_column - 1; ++column) {
            if(Purchaser_tableWidget->item(now_row-1, column) == nullptr){
                Purchaser_tableWidget->removeRow(now_row - 1);
                status = false;
                break;
            }
        }

        if(status) {
            Success = new QLabel("添加成功!");
            Success->setParent(Purchaser_update);
            Submit_success();

            QString device[now_column - 1];
            for (int column = 0; column < now_column - 1; ++column) {
                QTableWidgetItem *item = Purchaser_tableWidget->item(now_row - 1, column);
                device[column] = item->text();
            }
            mysql->Purchaser_sql(device);
        }
        else if(!status) {
            Fail = new QLabel("添加失败!");
            Fail->setParent(Purchaser_update);
            Submit_fail();
        }
    });

    connect(Delete,&QPushButton::clicked,Purchaser_update,[=] {
        Delete->close();
        Delete_finish->show();
        // 获取数据库的数据
        Purchaser_data = mysql->Purchaser_Select();
        // 在表格中添加数据 | 在数据库中读取
        for (int row = 1; row <= Purchaser_data.size(); ++row) {
            QPushButton *Delete_button = new QPushButton("删除");
            Purchaser_tableWidget->setCellWidget(row, 5, Delete_button);
            connect(Delete_button,&QPushButton::clicked, Purchaser_update,[=]{
                QString ID = Purchaser_tableWidget->item(row,1)->text();
                mysql->Purchaser_append_sql(ID);
                Purchaser_tableWidget->setCellWidget(row, 5, NULL);
            });
        }
    });

    connect(Delete_finish,&QPushButton::clicked,Purchaser_update,[=] {
        Success = new QLabel("删除完成!");
        Success->setParent(Purchaser_update);
        Delete_success();

        Delete_finish->close();
        Delete->show();
        int now_row = Purchaser_tableWidget->rowCount();
        while(now_row > 0) {
            // 删除当前行
            Purchaser_tableWidget->removeRow(now_row);
            now_row--;
        }
        // 获取数据库的数据
        Purchaser_data = mysql->Purchaser_Select();
        // 在表格中添加数据 | 在数据库中读取
        for (int row = 1; row <= Purchaser_data.size(); ++row) {
            int now_row = Purchaser_tableWidget->rowCount();
            Purchaser_tableWidget->insertRow(now_row); // 插入新行
            QString Info[5];
            Info[0] = Purchaser_data[row-1].Name;
            Info[1] = Purchaser_data[row-1].ID;
            Info[2] = Purchaser_data[row-1].Gender;
            Info[3] = Purchaser_data[row-1].Birthday;
            Info[4] = Purchaser_data[row-1].Date_of_employment;
            for (int column = 0; column < 5; ++column) {
                QTableWidgetItem *item = new QTableWidgetItem(Info[column]);
                Purchaser_tableWidget->setItem(row, column, item);
            }
        }
    });
    Purchaser_update->close();
}

void General_page::Submit_success() {
//    Success = new QLabel("添加成功!");
//    Success->setParent(Administer_update);
    Success->setFixedSize(100, 30);
    Success->move(150,20);

    timer = new QTimer;
    connect(timer, &QTimer::timeout, Success, &QLabel::hide);
    timer->start(DELAYDE);         //启动定时器
    Success->show();
}

void General_page::Submit_fail() {
//    Fail = new QLabel("添加失败!");
//    Fail->setParent(Administer_update);
    Fail->setFixedSize(100, 30);
    Fail->move(150,20);

    timer = new QTimer;
    connect(timer, &QTimer::timeout, Fail, &QLabel::hide);
    timer->start(DELAYDE);         //启动定时器
    Fail->show();
}

void General_page::Delete_success() {
//    Success = new QLabel("删除完成!");
//    Success->setParent(Administer_update);
    Success->setFixedSize(100, 30);
    Success->move(350,20);

    timer = new QTimer;
    connect(timer, &QTimer::timeout, Success, &QLabel::hide);
    timer->start(DELAYDE);         //启动定时器
    Success->show();
}