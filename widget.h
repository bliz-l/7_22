#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "regwindow.h"
#include <QUdpSocket>
#include <QMessageBox>
#include <QHostAddress>
#include <QDebug>
#include "logwindow.h"
#include "logwindow_p.h"


#define LOG_SERVER_IP "192.168.0.113"//服务器端地址
#define LOG_SERVER_PORT 2345        //注册端口
#define DOCTOR 0
#define PATIENT 1

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT




struct login_struct
{
    char log_user[20];
    char log_passwd[20];
};
struct log_result_struct
{
    int result;
    int type;
};



public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
public slots:
    void slot_btn_reg(void);
    void slot_btn_log(void);
    void slot_ReadyRead_log(void);


private:
    Ui::Widget *ui;
    QUdpSocket *udpsock_log;
};

#endif // WIDGET_H
