#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include "sql.h"
#include "widget.h"
namespace Ui {
class login;
}

class login : public QWidget
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = nullptr);
    ~login();

private slots:
    void on_p_login_clicked();

    void on_p_register_clicked();

private:
    Ui::login *ui;
    sql* msql=sql::getsql();
    QSqlQuery q;
    Widget w;
};

#endif // LOGIN_H
