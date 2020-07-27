#ifndef REGWINDOW_H
#define REGWINDOW_H

#include <QWidget>
#include <QUdpSocket>
#include <QMessageBox>
#include <QHostAddress>
#include <QDebug>

namespace Ui {
class RegWindow;
}

class RegWindow : public QWidget
{
    Q_OBJECT
#define MALE 1
#define FEMALE 0
#define REG_SERVER_IP "192.168.0.113"//虚拟机ip地址
#define REG_SERVER_PORT 1234
struct reg_struct
{
    char reg_user[20];
    char reg_passwd[20];
    int reg_age;
    int reg_sex;
};

struct result_struct
{
    int result;
};
public:
    explicit RegWindow(QWidget *parent = 0);
    ~RegWindow();

private slots:
    void on_rbtn_man_clicked();

    void on_rbtn_woman_clicked();
public slots:
    void slot_btn_reg_clicked(void);
    void slot_readyRead(void);
private:
    Ui::RegWindow *ui;
    QUdpSocket *udpsock;
};

#endif // REGWINDOW_H
