#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTimer>
#include<QUrl>
#include <QObject>
#include<QMediaPlaylist>
#include <QMediaPlayer>
#include<QPaintEvent>
#include<QNetworkAccessManager>
#include<QNetworkReply>
#include<QNetworkRequest>
#include<QJsonValue>
#include<QJsonArray>
#include<QJsonDocument>
#include<QJsonObject>
#include<QJsonParseError>
#include<map>
#include<vector>
#include<QFile>
#include<QMessageBox>
#include<queue>
#include<QFileDialog>
#include<iostream>
#include<thread>
#include<QDir>
using namespace std;
namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();
    void get_albumid_hash_ape(QString);
    void get_url_lyrics(QString);
    void deal_lyrics(QString);//解析歌词
    void init();
private slots:
    void on_p_search_clicked();
    void deal_network_finished(QNetworkReply*);
    void deal_network_finished2(QNetworkReply*);


    void on_p_play_clicked();

    void on_p_left_clicked();

    void deal_duration(qint64);
    void deal_hslider(qint64);

    void on_p_add_clicked();
    void thread_do_search();

    void on_p_right_clicked();

private:
    Ui::Widget *ui;
    QNetworkAccessManager* nmanager;
    QNetworkRequest*  qrequest;
    QNetworkAccessManager* nmanager2;
    QNetworkRequest*  qrequest2;
    int singerid;
    QString singername;
    int AlbumiD;
    QString hash;
    map<int,vector<QString>> mp;
    //获取url与歌词
    QString url;
    QString lyrics;
    //播放列表
    QMediaPlayer player;
    QMediaPlaylist playlist;
    bool isPlay=false;
    //歌词处理
    deque<pair<int,QString>> que;
    QString filename;
    QTimer m_tim;
signals:
    void thread_signals();

};

#endif // WIDGET_H
