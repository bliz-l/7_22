#ifndef LOGWINDOW_P_H
#define LOGWINDOW_P_H

#include <QWidget>
#include "widget.h"
#include <QPainter>
#include <QList>
#include <QTimer>
#include <QtCore/qmath.h>
#include <QPointF>

namespace Ui {
class LogWindow_P;
}

class LogWindow_P : public QWidget
{
    Q_OBJECT

public:
    explicit LogWindow_P(QString user, QString type,QWidget *parent = 0);
    ~LogWindow_P();
    void paintEvent(QPaintEvent *);

public slots:

    void slot_data_form(void);


private:
    Ui::LogWindow_P *ui;
    //定义存储列表QList
    QList<float> xList;
    QList<float> yList;
    //定义timer
    QTimer *m_timer;
    float x;
    int count;
};

#endif // LOGWINDOW_P_H
