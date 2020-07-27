#include "logwindow_p.h"
#include "ui_logwindow_p.h"

LogWindow_P::LogWindow_P(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LogWindow_P)
{
    ui->setupUi(this);


}

LogWindow_P::~LogWindow_P()
{
    delete ui;
}
