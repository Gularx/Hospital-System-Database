//
// Created by Gularx on 2024/6/13.
//

#ifndef CLASSIC_PURCHASER_PAGE_H
#define CLASSIC_PURCHASER_PAGE_H

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

class Purchaser_page : public QWidget{
public:
    Mysql *mysql;
    Purchaser_page() = default;
    Purchaser_page(Mysql *mysql);   // 使用数据库

    void Equipment_login(); // 展示购买人员所有设备页面
    void Fail_submit();     // 提交失败标签展示
    void Success_submit();  // 提交成功标签展示

    QPushButton *Append;    // 添加按钮
    QPushButton *Submit;    // 提交按钮

    bool status;            // 判断输入是否正确的状态
    QString UserName;       // 当前购入者名字

    std::vector<equipment_t> Data;      // 获取数据库的数据
    QTableWidget *Login_tableWidget;    // 创建登录表格
};


#endif //CLASSIC_PURCHASER_PAGE_H
