#include "sql.h"

sql* sql::sp=nullptr;
sql::sql(QWidget *parent) : QWidget(parent)
{
    qDebug()<<sizeof(int *);
    qDebug()<<QSqlDatabase::drivers();
   //添加mysql数据库
    QSqlDatabase db=QSqlDatabase::addDatabase("QMYSQL");
    //链接数据库
    db.setHostName("127.0.0.1");
    db.setUserName("root");
    db.setPassword("123");
    db.setDatabaseName("music");
    if(!db.open())
    {
        QMessageBox::warning(this,"错误",db.lastError().text());
        return;
    }
    else
    {
        qDebug()<<"连接成功"<<endl;
    }
}
