#include <QApplication>
#include <QWidget>
#include <QDebug>

#include <Login.h>
#include <Mysql.h>
#include <Administrative_page.h>
#include <Purchaser_page.h>
#include <General_page.h>
int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    Mysql *mysql = new Mysql;
    Login *l = new Login;
    l->mysql = mysql;

    Administrative_page *m = new Administrative_page(mysql);
    m->mysql = mysql;
    Purchaser_page *p = new Purchaser_page(mysql);
    p->mysql = mysql;
    General_page *g = new General_page(mysql);
    g->mysql = mysql;

    l->m = m;
    l->p = p;
    l->g = g;
    l->show();

    qDebug() << "Hello World";
    return QCoreApplication::exec();
}
