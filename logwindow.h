#ifndef LOGWINDOW_H
#define LOGWINDOW_H

#include <QWidget>
#include "widget.h"
#include <QTreeWidgetItem>
#include <QUdpSocket>
#include <QMessageBox>
#include <QHostAddress>
#include "doctor_patient_window.h"
#define SEARCH_SERVER_IP "192.168.0.113"
#define SEARCH_SERVER_PORT 2346

namespace Ui {
class LogWindow;
}

class LogWindow : public QWidget
{
    Q_OBJECT


struct patient_search
{
    char send_patient[20];
    char send_doctor[20];
};
struct patient_info
{
    int age;
    int sex;
    char medic[20];
    char text[50];
    int result;
};


public:
    explicit LogWindow(QString user, QString type, QWidget *parent = 0);
    ~LogWindow();

public slots:
    void slot_btn_exit(void);
    void slot_btn_show(void);
    void slot_btn_get(void);
    void slot_item_doubleclicked(QTreeWidgetItem*,int);
    void slot_ReadyRead(void);



private:
    Ui::LogWindow *ui;
    QUdpSocket *udpsock;
};

#endif // LOGWINDOW_H
