#ifndef SQL_H
#define SQL_H
#include <QSqlDatabase>
#include <QDebug>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlQuery>
#include <QWidget>

class sql : public QWidget
{
    Q_OBJECT
public:
    //单例模式
    static sql* sp;
    static sql* getsql()
    {
        if(sp==nullptr) sp=new sql;
        return sp;
    }

signals:

public slots:
private:
    explicit sql(QWidget *parent = nullptr);
};

#endif // SQL_H
