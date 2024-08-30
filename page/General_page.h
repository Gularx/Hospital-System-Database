//
// Created by Gularx on 2024/6/14.
//

#ifndef CLASSIC_GENERAL_PAGE_H
#define CLASSIC_GENERAL_PAGE_H

#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QTableWidget>
#include <QHeaderView>
#include <QMessageBox>
#include <QTimer>
#include <QAxObject>
#include <QDir>

#include <vector>
#include <Mysql.h>

class General_page : public QWidget{
public:
    Mysql *mysql;
    General_page() = default;
    General_page(Mysql *mysql);  // 使用数据库

    // 数据导出
    void ExportDataToExcel();

    // 数据展示
    void Equipment_display();
    void Administer_display();
    void Purchaser_display();

    // 操作完成提示
    void Submit_success();
    void Submit_fail();
    void Delete_success();

    bool status;

    QLabel *Success;
    QLabel *Fail;
    QTimer *timer;

    QWidget * Administer_update;// 管理员界面
    QWidget * Purchaser_update; // 购入员界面

    QPushButton *Export;        // 导出按钮
    QPushButton *Equipment;    // 查询仪器
    QPushButton *Administer;    // 查询管理人员
    QPushButton *Purchaser;      // 查询购入人员

//    QPushButton *Append;
//    QPushButton *Append_finish;
//    QPushButton *Delete;
//    QPushButton *Delete_finish;

    std::vector<equipment_t> Equipment_data;    // 获取数据库的数据
    std::vector<person_t> Administer_data;  // 获取数据库的数据
    std::vector<person_t> Purchaser_data;       // 获取数据库的数据

    QTableWidget *Equipment_tableWidget;        // 设备表格
    QTableWidget *Administer_tableWidget;       // 管理员表格
    QTableWidget *Purchaser_tableWidget;         // 购入员表格
};


#endif //CLASSIC_GENERAL_PAGE_H
