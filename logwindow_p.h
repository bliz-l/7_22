#ifndef LOGWINDOW_P_H
#define LOGWINDOW_P_H

#include <QWidget>
#include "widget.h"

namespace Ui {
class LogWindow_P;
}

class LogWindow_P : public QWidget
{
    Q_OBJECT

public:
    explicit LogWindow_P(QString user, QString type,QWidget *parent = 0);
    ~LogWindow_P();

public slots:
    void slot_btn_refresh(void);


private:
    Ui::LogWindow_P *ui;
};

#endif // LOGWINDOW_P_H
