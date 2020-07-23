#include "widget.h"
#include "ui_widget.h"
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    setWindowTitle("xiaoc");
    setAttribute(Qt::WA_TranslucentBackground, false);
       //绘图
    QPalette pal=this->palette();
    pal.setBrush(QPalette::Background,QBrush(QPixmap(":/my-images/timg.jpg")));
    setPalette(pal);
    nmanager=new QNetworkAccessManager();
    nmanager2=new QNetworkAccessManager();
    connect(nmanager,&QNetworkAccessManager::finished,this,&Widget::deal_network_finished);
    connect(nmanager2,&QNetworkAccessManager::finished,this,&Widget::deal_network_finished2);
    connect(&player,&QMediaPlayer::durationChanged,this,&Widget::deal_duration);
    connect(&player,&QMediaPlayer::positionChanged,this,&Widget::deal_hslider);
    connect(this,&Widget::thread_signals,this,&Widget::thread_do_search);
    connect(&m_tim,&QTimer::timeout,[=]{if(ui->horizontalSlider->value()==ui->horizontalSlider->maximum())
    on_p_right_clicked();m_tim.stop();});
    init();//初始化
}

Widget::~Widget()
{
    delete ui;
}
void Widget::init()//初始化界面控件
{
    player.setVolume(50);
    ui->verticalSlider->setValue(50);
    QDir dir("./");
    dir.mkdir("lyrics");
    //绘制播放键
    ui->p_play->setStyleSheet("QPushButton#p_play:hover{border-image: url(:/my-images/play5.png);}"
                                          "QPushButton#p_play:!hover{border-image: url(:/my-images/play4.png);}"
                                          "QPushButton#p_play:pressed{border-image: url(:/my-images/play5.png);}");
    //绘制上一曲键
    ui->p_left->setStyleSheet("QPushButton#p_left:hover{border-image: url(:/my-images/last1.png);}"
                              "QPushButton#p_left:!hover{border-image: url(:/my-images/last.png);}");
    //绘制下一曲键
    ui->p_right->setStyleSheet("QPushButton#p_right:hover{border-image: url(:/my-images/next1.png);}"
                              "QPushButton#p_right:!hover{border-image: url(:/my-images/next.png);}");
    //绘制添加键
    ui->p_add->setStyleSheet("QPushButton#p_add:hover{border-image: url(:/my-images/addmusic.png);}"
                              "QPushButton#p_add:!hover{border-image: url(:/my-images/add.png);}");
    //去边框
    ui->list_singer->setFrameShape(QListWidget::NoFrame);
    //绘音量键
    ui->label_vm->setStyleSheet("QLabel#label_vm:!hover{border-image: url(:/my-images/traysound1.png);}");


}

void Widget::on_p_search_clicked()//创建一个线程处理
{
    std::thread kkk([&]{emit thread_signals();});
    kkk.detach();
}
void Widget::deal_network_finished(QNetworkReply* reply)//对信号做处理
{
    //获取响应的信息，状态码为200表示正常
       QVariant status_code = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);

       //无错误返回
       if(reply->error() == QNetworkReply::NoError)
       {
           QByteArray bytes = reply->readAll();  //获取字节
           QString result(bytes);  //转化为字符串
           qDebug()<<"解析成功"; //自定义方法，解析歌曲数据
           int i=0,count=0;
           while(result[i]!='{') count++,i++;//处理字符串，让其能够转换成json
           result.remove(0,count);
           i=result.size()-1,count=0;
           while(result[i]!='}') i--,count++;
           result.remove(i+1,count);
           get_albumid_hash_ape(result);
       }

       else
       {
           //处理错误
           qDebug()<<"处理错误";
       }
}
void Widget::get_albumid_hash_ape(QString json)//解析得到歌曲者，歌曲名，歌曲id,歌曲hash值
{
    QByteArray byte_array;
    QJsonParseError json_error;
    QJsonDocument parse_document=QJsonDocument::fromJson(byte_array.append(json),&json_error);

    if(json_error.error==QJsonParseError::NoError)
    {
        //处理数据
        QJsonObject root_obj=parse_document.object();
        QJsonObject data=root_obj.value("data").toObject();
        QJsonValue song=data.value("song");
        if(song.isArray())
        {
            for(int i=0;i<20;i++)
            {
                QJsonObject data_obj=song.toArray().at(i).toObject();
                AlbumiD=data_obj.value("AlbumID").toInt();
                hash=data_obj.value("hash").toString();
                QString singername=data_obj.value("singername").toString();
                QString songname=data_obj.value("songname").toString();
                mp[AlbumiD].push_back(hash);
                mp[AlbumiD].push_back(singername);
                mp[AlbumiD].push_back(songname);

            }
        }

    }
    else {
        qDebug()<<"wrong";
    }
    //继续解析歌曲与歌词
    for(auto i:mp)
    {
        QString hash=i.second[0];
        QString url=QString("http://wwwapi.kugou.com/yy/index.php?r=play/getdata&callback=jQuery19108373958037571234_1594124463718&hash=%1&album_id=%2&dfid=3vHwcT3BUudr0zq4OL00hJeh&mid=348be07fbead24bf35612643f8439c6f&platid=4&_=1594124463723").arg(hash).arg(i.first);
        qDebug()<<url;
        nmanager2->get(QNetworkRequest(QUrl(url)));
    }
    player.setPlaylist(&playlist);
    mp.clear();

}
void Widget::deal_network_finished2(QNetworkReply* reply)//处理finishx信号
{
    //获取响应的信息，状态码为200表示正常
       QVariant status_code = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);

       //无错误返回
       if(reply->error() == QNetworkReply::NoError)
       {
           QByteArray bytes = reply->readAll();  //获取字节
           QString result(bytes);  //转化为字符串
           qDebug()<<"解析成功"; //自定义方法，解析歌曲数据
           int i=0,count=0;
           while(result[i]!='{') count++,i++;//处理字符串，让其能够转换成json
           result.remove(0,count);
           i=result.size()-1,count=0;
           while(result[i]!='}') i--,count++;
           result.remove(i+1,count);
           qDebug()<<result;
           get_url_lyrics(result);
       }

       else
       {
           //处理错误
           qDebug()<<"wrong";
       }
}
void Widget::get_url_lyrics(QString json)//获取歌曲的全名，歌词，url
{
    QByteArray byte_array;
    QJsonParseError json_error;
    QJsonDocument parse_document=QJsonDocument::fromJson(byte_array.append(json),&json_error);
    if(json_error.error==QJsonParseError::NoError)
    {
       QJsonObject obj=parse_document.object();
       QJsonObject data=obj.value("data").toObject();
       url=data.value("play_url").toString();
       lyrics=data.value("lyrics").toString();
       QString audioname=data.value("audio_name").toString();
       if(lyrics!=nullptr)
       {
           QString temp=QString("lyrics/%1.txt").arg(audioname);
           QFile file(temp);
           file.open(QIODevice::WriteOnly | QIODevice::Text);
           file.write(lyrics.toUtf8());
           file.close();
       }
       qDebug()<<url<<" "<<lyrics<<" "<<audioname;
       ui->list_singer->addItem(audioname);
       playlist.addMedia(QUrl(url));
    }
    else{
        qDebug()<<"wrong";
    }
}

void Widget::on_p_play_clicked()//播放按钮
{
    if(!playlist.isEmpty())
        {
            isPlay = !isPlay;
            if(!isPlay)
            {
                ui->p_play->setToolTip(QString("播放"));
                ui->p_play->setStyleSheet("QPushButton#p_play:hover{border-image: url(:/my-images/play5.png);}"
                                                      "QPushButton#p_play:!hover{border-image: url(:/my-images/play4.png);}"
                                                      "QPushButton#p_play:pressed{border-image: url(:/my-images/play5.png);}");
                player.pause();
            }
            else
            {
                ui->p_play->setToolTip(QString("暂停"));
                ui->p_play->setStyleSheet("QPushButton#p_play:hover{border-image: url(:/my-images/play2.png);}"
                                            "QPushButton#p_play:!hover{border-image: url(:/my-images/play1.png);}"
                                            "QPushButton#p_play:pressed{border-image: url(:/my-images/play3.png);}");
                player.play();
            }
        }
        else
        {
            QMessageBox::warning(this,"提示: ","播放列表为空!\n请先添加歌曲!");
        }

}

void Widget::on_p_left_clicked()
{
    player.setMedia(playlist.media(playlist.previousIndex()));
    player.setMedia(playlist.media(playlist.previousIndex()));
    playlist.setCurrentIndex(playlist.previousIndex());
    isPlay = false;
    on_p_play_clicked();

}
void Widget::deal_lyrics(QString temp)//处理歌词
{
    QString tt=QString("./lyrics/%1.txt").arg(temp);
    QFile file(tt);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
       {
           QString line;
           QTextStream in(&file);  //用文件构造流
           line = in.readLine();//读取一行放到字符串里
           QString pline=line;
           int target=0;
           while(!line.isNull())//字符串有内容
           {
               if(line.split("]").size()==2)
               {
                   QString kk=line.split("]").at(1);
                   QString pp=line.split("]").at(0);
                   QString lp=pp.split("[").at(1);
                   int m=lp.split(":").at(0).toInt();
                   QString lq=lp.split(":").at(1);
                   int s=lq.split(".").at(0).toInt();


                   QString p2=line.split("]").at(0);
                   QString p3=p2.split("[").at(1);
                   QString p4=p3.split(":").at(1);
                   p4=p4+'.';
                   int ms=p4.split(".").at(1).toInt();
                   int sum=m*60000+s*1000+ms;
                   if(!kk.isEmpty()||target!=0)
                   que.push_back({sum,kk}),target++;
               }
               line=in.readLine();//循环读取下行

           }
       }
       file.close();
       if(que.size()>=3)
       {
           ui->label_ly1->setText(que.at(0).second);
           ui->label_ly2->setText(que.at(1).second);
           ui->lable_ly3->setText(que.at(2).second);
       }
       else {
           ui->label_ly1->setText("暂无歌词");
       }

}
void Widget::deal_duration(qint64 playtime)
{
    que.clear();
    m_tim.start(100);
    playtime=player.duration();
    ui->horizontalSlider->setMinimum(0);
    ui->horizontalSlider->setMaximum(playtime);
    int pos=playlist.currentIndex();
    ui->list_singer->setCurrentRow(pos);
    int p=ui->list_singer->currentRow();
    QString s=ui->list_singer->item(p)->text();//传给歌词解析
    deal_lyrics(s);

}
void Widget::deal_hslider(qint64 k)
{
    int p=ui->verticalSlider->value();
    player.setVolume(p);
    ui->horizontalSlider->setValue(k);
    if(!que.empty()&&que.size()>3&&k>=que.at(1).first)
    {
        que.pop_front();
        ui->label_ly1->setText(que[0].second);
        ui->label_ly2->setText(que[1].second);
        ui->lable_ly3->setText(que[2].second);
    }
    else if(que.size()==3&&k>=que.at(1).first)
    {
        que.pop_front();
        ui->label_ly1->setText(que[0].second);
        ui->label_ly2->setText(que[1].second);
        ui->lable_ly3->setText("");

    }
    else if(que.size()==2&&k>=que.at(1).first)
    {
        que.pop_front();
        ui->label_ly1->setText(que[0].second);
        ui->label_ly2->setText("");
        ui->lable_ly3->setText("");
    }
}

void Widget::on_p_add_clicked()
{
       QString path=QFileDialog::getOpenFileName(this,"open","../");
       //获取文件信息
       filename="";
       QFileInfo info(path);
       filename=info.fileName();
       path= info.path();
       path.replace(QString("/"), QString("\\"));/*替换目录格式*/
       ui->list_singer->addItem(filename);
       QString absDir = QString("%1\\%2").arg(path).arg(filename);
       playlist.addMedia(QUrl::fromLocalFile(absDir));
}
void Widget::thread_do_search()//线程的处理函数
{
    QString temp=ui->lineEdit->text();
    qDebug()<<temp;
    QString url=QString("http://searchrecommend.kugou.com/get/complex?callback=jQuery1124008280769743433058_1594104901081&word=%1&_=1594104901083").arg(temp);
    qDebug()<<url;
    nmanager->get(QNetworkRequest(QUrl(url)));
}

void Widget::on_p_right_clicked()
{
    player.setMedia(playlist.media(playlist.nextIndex()));
        playlist.setCurrentIndex(playlist.nextIndex());
        isPlay = false;
        on_p_play_clicked();
}
