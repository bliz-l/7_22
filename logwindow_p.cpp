#include "logwindow_p.h"
#include "ui_logwindow_p.h"

LogWindow_P::LogWindow_P(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LogWindow_P)
{
    ui->setupUi(this);

    connect(ui->btn_refresh, SIGNAL(clicked(bool)), this, SLOT(slot_btn_refresh()));
}

LogWindow_P::~LogWindow_P()
{
    delete ui;
}
void LogWindow_P::slot_btn_refresh()
{

}
