//
// Created by Gularx on 2024/6/12.
//

#ifndef CLASSIC_MYSQL_H
#define CLASSIC_MYSQL_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

#define DELAYDE 1500
enum STATE{ASMINISTRATIVE = 1,PURCHASER = 2,GENERAL_MANAGER = 3};

struct equipment_t{
    QString Name;
    QString Number;
    QString Production_date;
    QString Purchase_date;
    QString Purchaser;
    QString Status;
    QString User_name;
};

struct person_t{
    QString Name;
    QString ID;
    QString Password;
    QString Gender;
    QString Birthday;
    QString Date_of_employment;
};

class Mysql {
public:
    Mysql();

    //登录检索
    bool Login(QString ID, QString Password, int state);

    bool Query_login(QString Number, equipment_t *data);

    bool administrative_sql(QString Number, QString state, QString User_name);

    bool purchaser_sql(QString *device);

    bool Administer_sql(QString *device);

    bool Administer_append_sql(QString ID);

    bool Purchaser_sql(QString *device);

    bool Purchaser_append_sql(QString ID);

    //仪器库
    std::vector<equipment_t> Equipment_Select();
    //管理员
    std::vector<person_t> Administrative_Select();
    //购入员
    std::vector<person_t> Purchaser_Select();

    QSqlDatabase db;
};


#endif //CLASSIC_MYSQL_H
