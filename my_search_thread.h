#ifndef MY_SEARCH_THREAD_H
#define MY_SEARCH_THREAD_H

#include <QObject>
#include <QThread>
class my_search_thread : public QThread
{
public:
    explicit my_search_thread();
    void run();
public slots:
    void deal_signals();
};

#endif // MY_SEARCH_THREAD_H
