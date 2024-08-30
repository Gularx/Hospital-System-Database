//
// Created by Gularx on 2024/6/12.
//

#include "Mysql.h"

Mysql::Mysql() {
    db = QSqlDatabase::addDatabase("QODBC");
    db.setHostName("127.0.0.1"); // 数据库服务器地址
    db.setDatabaseName("work_space");  // 数据库名
    db.setUserName("root");      // 用户名
    db.setPassword("123456");  // 密码
    bool ok = db.open();
    if (ok) {
        qDebug() << "链接数据库成功！";
    } else {
        qDebug() << "链接数据库失败：" << db.lastError().text();
    }
}
//查询ID和密码用于登录
bool Mysql::Login(QString ID, QString Password, int state) {
    bool exist = false;
    if(state == ASMINISTRATIVE){
        QString sql = "select ID,Password from administrative;";
        QSqlQuery result = this->db.exec(sql);
        while (result.next())
        {
            if(result.value(0).toString() == ID && result.value(1).toString() == Password)
            {
                exist = true;
            }
        }
    }
    else if(state == PURCHASER){
        QString sql = "select ID,Password from purchaser;";
        QSqlQuery result = this->db.exec(sql);
        while (result.next())
        {
            if(result.value(0).toString() == ID && result.value(1).toString() == Password)
            {
                exist = true;
            }
        }
    }
    else if(state == GENERAL_MANAGER){
        QString sql = "select ID,Password from general_manager;";
        QSqlQuery result = this->db.exec(sql);
        while (result.next())
        {
            if(result.value(0).toString() == ID && result.value(1).toString() == Password)
            {
                exist = true;
            }
        }
    }
    if(!exist) return false;
    else return true;
}

std::vector<equipment_t> Mysql::Equipment_Select() {
    std::vector<equipment_t> ALL_data;
    QSqlQuery result = this->db.exec("select * from equipment;");
    while (result.next()){
        equipment_t temp;
        // 结构体赋值
        temp.Name = result.value(0).toString();
        temp.Number = result.value(1).toString();
        temp.Production_date = result.value(2).toString();
        temp.Purchase_date = result.value(3).toString();
        temp.Purchaser = result.value(4).toString();
        temp.Status = result.value(5).toString();
        temp.User_name = result.value(6).toString();

        ALL_data.emplace_back(temp);
    }
    return ALL_data;
}

std::vector<person_t> Mysql::Administrative_Select() {
    std::vector<person_t> ALL_data;
    QSqlQuery result = this->db.exec("select * from administrative;");
    while (result.next()){
        person_t temp;
        // 结构体赋值
        temp.Name = result.value(0).toString();
        temp.ID = result.value(1).toString();
        temp.Password = result.value(2).toString();
        temp.Gender = result.value(3).toString();
        temp.Birthday = result.value(4).toString();
        temp.Date_of_employment = result.value(5).toString();
        ALL_data.emplace_back(temp);
    }
    return ALL_data;
}

std::vector<person_t> Mysql::Purchaser_Select() {
    std::vector<person_t> ALL_data;
    QSqlQuery result = this->db.exec("select * from purchaser;");
    while (result.next()){
        person_t temp;
        // 结构体赋值
        temp.Name = result.value(0).toString();
        temp.ID = result.value(1).toString();
        temp.Password = result.value(2).toString();
        temp.Gender = result.value(3).toString();
        temp.Birthday = result.value(4).toString();
        temp.Date_of_employment = result.value(5).toString();
        ALL_data.emplace_back(temp);
    }
    return ALL_data;
}

bool Mysql::Query_login(QString Number,equipment_t *data) {
    bool exist = false;
    QSqlQuery result = this->db.exec("select * from equipment;");
    while (result.next()) {
        if(result.value(1).toString() == Number){
            exist = true;
            data->Name = result.value(0).toString();
            data->Number = result.value(1).toString();
            data->Production_date = result.value(2).toString();
            data->Purchase_date = result.value(3).toString();
            data->Purchaser = result.value(4).toString();
            data->Status = result.value(5).toString();
            data->User_name = result.value(6).toString();
        }
    }
    if(!exist) return false;
    else return true;
}

bool Mysql::administrative_sql(QString Number,QString state, QString User_name) {
    QString sql = "update equipment set Status = '" + state + "' , User_name = '" + User_name + "' where Number = '" + Number + "';";
    QSqlQuery result = this->db.exec(sql);
    return true;
}

bool Mysql::purchaser_sql(QString *device) {
    QString sql = "INSERT INTO equipment VALUES ('" + device[0] + "','" + device[1] + "','" + device[2] + "','" + device[3] + "','" + device[4] + "','" + device[5] + "','无');";
    QSqlQuery result = this->db.exec(sql);
    return true;
}

bool Mysql::Administer_sql(QString *device) {
    QString sql = "INSERT INTO administrative VALUES ('" + device[0] + "','" + device[1] + "','123456','" + device[2] + "','" + device[3] + "','" + device[4] +"');";
    QSqlQuery result = this->db.exec(sql);
    return false;
}

bool Mysql::Administer_append_sql(QString ID) {
    QString sql = "DELETE FROM administrative WHERE ID = "+ ID +";";
//    qDebug() << sql;
    QSqlQuery result = this->db.exec(sql);
    return false;
}

bool Mysql::Purchaser_sql(QString *device) {
    QString sql = "INSERT INTO purchaser VALUES ('" + device[0] + "','" + device[1] + "','0123456','" + device[2] + "','" + device[3] + "','" + device[4] +"');";
    QSqlQuery result = this->db.exec(sql);
    return false;
}

bool Mysql::Purchaser_append_sql(QString ID) {
    QString sql = "DELETE FROM purchaser WHERE ID = "+ ID +";";
//    qDebug() << sql;
    QSqlQuery result = this->db.exec(sql);
    return false;
}