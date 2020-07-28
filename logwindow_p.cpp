#include "logwindow_p.h"
#include "ui_logwindow_p.h"

LogWindow_P::LogWindow_P(QString user, QString type, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LogWindow_P)
{
    ui->setupUi(this);
    QString str=user;
    str+="_";
    str+=type;
    str="登录:"+str;
    this->setWindowTitle(str);

    connect(ui->btn_refresh, SIGNAL(clicked(bool)), this, SLOT(slot_btn_refresh()));
}

LogWindow_P::~LogWindow_P()
{
    delete ui;
}
void LogWindow_P::slot_btn_refresh()
{

}
