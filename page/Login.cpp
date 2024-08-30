//
// Created by Gularx on 2024/6/12.
//

#include "Login.h"

Login::Login() {

//TODO:创建主页面
    this->setFixedSize(500,300);
    this->setWindowTitle("Login");

//TODO:创建第一个页面的按钮
    Administrative = new QPushButton("管理员");
    Administrative->setParent(this);
    Administrative->setFixedSize(100,50);
    Administrative->move(60,110);

    Purchaser = new QPushButton("采购员");
    Purchaser->setParent(this);
    Purchaser->setFixedSize(100, 50);
    Purchaser->move(200,110);

    General_manager = new QPushButton("负责人");
    General_manager->setParent(this);
    General_manager->setFixedSize(100, 50);
    General_manager->move(340,110);

//TODO:创建第二个页面的按钮
    Query_system = new QLabel("查询系统");
    Query_system->setParent(this);
    Query_system->setFixedSize(110, 50);
    Query_system->move(220,20);
    Query_system->close();

    login = new QPushButton("登录");
    login->setParent(this);
    login->setFixedSize(100, 50);
    login->move(200,200);
    login->close();

    User_name = new QLabel("账号：");
    User_name->setParent(this);
    User_name->setFixedSize(100, 30);
    User_name->move(110,80);
    User_name->close();

    User_name_input = new QLineEdit;
    User_name_input->setParent(this);
    User_name_input->setFixedSize(210, 30);
    User_name_input->move(150, 78);
    User_name_input->close();

    Password = new QLabel("密码：");
    Password->setParent(this);
    Password->setFixedSize(100, 30);
    Password->move(110,130);
    Password->close();

    Password_input = new QLineEdit;
    Password_input->setParent(this);
    Password_input->setFixedSize(210, 30);
    Password_input->move(150, 128);
    Password_input->close();

//TODO:实现第一个页面到第二个页面的跳转
    connect(Administrative,&QPushButton::clicked,this,[=]{
        qDebug() << "管理员";
        state = ASMINISTRATIVE;
        Switch();
    });

    connect(Purchaser,&QPushButton::clicked,this,[=]{
        qDebug() << "采购员";
        state = PURCHASER;
        Switch();
    });

    connect(General_manager,&QPushButton::clicked,this,[=]{
        qDebug() << "负责人";
        state = GENERAL_MANAGER;
        Switch();
    });

//TODO: 登录检索
    connect(login, &QPushButton::clicked, this, [=]{
        bool Login_OK = mysql->Login(User_name_input->text(), Password_input->text(), state);
        if(Login_OK) {
            qDebug() << "登录成功";
            Success_login();
            this->close();
        }
        else {
            qDebug() << "登录失败";
            Fail_login();
        }
    });
}

void Login::Switch() {
    Administrative->close();
    Purchaser->close();
    General_manager->close();

    Query_system->show();
    User_name->show();
    User_name_input->show();
    Password->show();
    Password_input->show();
    login->show();
}

void Login::Success_login() {
    if(state == ASMINISTRATIVE) {
        QString sql = "select Name from administrative where ID = "+User_name_input->text()+";";
        QSqlQuery result = mysql->db.exec(sql);
        while (result.next())
        {
            m->UserName = result.value(0).toString();
        }
        m->show();
        m->setWindowTitle(m->UserName);
    }
    else if(state == PURCHASER) {
        QString sql = "select Name from purchaser where ID = "+User_name_input->text()+";";
        QSqlQuery result = mysql->db.exec(sql);
        while (result.next())
        {
            p->UserName = result.value(0).toString();
        }
        p->show();
        p->setWindowTitle(p->UserName);
    }
    else if(state == GENERAL_MANAGER) {
        QString sql = "select Name from general_manager where ID = "+User_name_input->text()+";";
        QSqlQuery result = mysql->db.exec(sql);
        QString Username;
        while (result.next())
        {
            Username = result.value(0).toString();
        }
        g->show();
        g->setWindowTitle(Username);
    }
}

void Login::Fail_login() {
    User_name_input->clear();
    Password_input->clear();

    QLabel *Login_fail = new QLabel("登录失败!");
    Login_fail->setParent(this);
    Login_fail->setFixedSize(100, 30);
    Login_fail->move(225,165);

    QTimer *timer = new QTimer;
    connect(timer, &QTimer::timeout, Login_fail, &QLabel::hide);
    timer->start(DELAYDE);         //启动定时器
    Login_fail->show();
}