//
// Created by Gularx on 2024/6/12.
//

#ifndef CLASSIC_LOGIN_H
#define CLASSIC_LOGIN_H

#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QTimer>
#include <QLineEdit>
#include <Mysql.h>

#include <Administrative_page.h>
#include <Purchaser_page.h>
#include <General_page.h>

class Login : public QWidget{
public:
    int state;              // 数据库选择
    Mysql *mysql;           // 数据库使用

    Login();                // 登录实现
    void Switch();          // 双按键跳转
    void Success_login();   // 登录成功页面链接
    void Fail_login();      // 登录失败提示

//TODO: 第一个页面
    QPushButton *Administrative;    // 管理员按键
    QPushButton *Purchaser;         // 购买者按键
    QPushButton *General_manager;   // 负责人按键

//TODO: 第二个页面
    QLabel    *Query_system;    // 主系统标签
    QLabel    *User_name;       // 登录者标签
    QLineEdit *User_name_input; // 登录者编号输入
    QLabel    *Password;        // 密码标签
    QLineEdit *Password_input;  // 密码输入
    QPushButton *login;         // 登录按键

    Administrative_page *m;     // 管理人员表
    Purchaser_page *p;          // 购入人员表
    General_page *g;            // 负责人员表
};


#endif //CLASSIC_LOGIN_H
