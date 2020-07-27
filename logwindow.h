#ifndef LOGWINDOW_H
#define LOGWINDOW_H

#include <QWidget>
#include "widget.h"
#include <QTreeWidgetItem>
#include <QUdpSocket>
#include <QMessageBox>
#include <QHostAddress>

namespace Ui {
class LogWindow;
}

class LogWindow : public QWidget
{
    Q_OBJECT

struct patient_tbl
{
    char get_patient[20];
    int count;
};
struct doctor_name
{
    char send_doctor[20];
};
struct patient_name
{
    char send_patient[10];
};
struct patient_info
{
    int age;
    int sex;
    char medic[20];
    char text[50];
};


public:
    explicit LogWindow(QWidget *parent = 0);
    ~LogWindow();

public slots:
    void slot_btn_exit(void);
    void slot_btn_show(void);
    void slot_btn_get(void);
    void slot_item_doubleclicked(void);



private:
    Ui::LogWindow *ui;
    QUdpSocket *udpsock_log;
};

#endif // LOGWINDOW_H
