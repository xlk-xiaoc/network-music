#include "login.h"
#include "ui_login.h"

login::login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_TranslucentBackground, false);
    QPalette pal=this->palette();
    pal.setBrush(QPalette::Background,QBrush(QPixmap(":/my-images/timg.jpg")));
    setPalette(pal);
}

login::~login()
{
    delete ui;
}

void login::on_p_login_clicked()
{
        QString username=ui->l_username->text();
        QString passwd=ui->l_password->text();
        q.exec(QObject::tr("select * from music_user where username='%1' and password='%2'").arg(username).arg(passwd));//查找
        if(q.next())
        {
           this->hide();
            w.setWindowTitle(username);
            w.show();
        }
        else{
            QMessageBox::about(this,"error","user is not exist");
        }
}

void login::on_p_register_clicked()
{
        QString username=ui->l_username->text();
        QString passwd=ui->l_password->text();
        q.exec(QObject::tr("select * from music_user where username=%1").arg(username));
        if(!q.next())
        {
           q.exec(QObject::tr("insert into  music_user  values('%1','%2')").arg(username).arg(passwd));//插入
           QMessageBox::about(this,"success","register true");

        }

        else QMessageBox::about(this,"false","user is exist");
}
