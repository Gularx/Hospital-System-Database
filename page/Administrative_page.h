//
// Created by Gularx on 2024/6/13.
//

#ifndef CLASSIC_ADMINISTRATIVE_PAGE_H
#define CLASSIC_ADMINISTRATIVE_PAGE_H

#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QTableWidget>
#include <QHeaderView>
#include <QMessageBox>
#include <QTimer>

#include <vector>
#include <Mysql.h>


class Administrative_page : public QWidget {
public:
    Mysql *mysql;
    Administrative_page() = default;
    Administrative_page(Mysql *mysql);  // 使用数据库

    void Equipment_display();// 展示管理员所有设备页面
    void Query_display();    // 更新管理员查询设备页面
    void Fail_query();       // 查询失败

    QLabel *Query_note;     // 编号标签
    QLineEdit *Query_input; // 编号输入
    QPushButton *Query;     // 编号查询按钮

    equipment_t data;       // 查询数据
    QString UserName;       // 当前管理员名字

    std::vector<equipment_t> Data;      // 获取数据库的数据
    QTableWidget *Equipment_tableWidget;// 创建登录表格
    QTableWidget *Query_tableWidget;    // 创建查询表格

    int Query_state = 0;
};


#endif //CLASSIC_ADMINISTRATIVE_PAGE_H