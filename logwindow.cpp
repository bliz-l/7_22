#include "logwindow.h"
#include "ui_logwindow.h"

LogWindow::LogWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LogWindow)
{
    ui->setupUi(this);
    //定义Qtreewidgetitem
    udpsock_log = new QUdpSocket();//定义udpsock

    connect(ui->btn_show, SIGNAL(clicked(bool)), this, SLOT(slot_btn_show()));
    connect(ui->btn_exit, SIGNAL(clicked(bool)), this, SLOT(slot_btn_exit()));
    connect(ui->btn_get, SIGNAL(clicked(bool)), this, SLOT(slot_btn_get()));
    connect(ui->treeWidget, SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)), this, SLOT(slot_item_doubleclicked()));



}

LogWindow::~LogWindow()
{
    delete ui;
}
void LogWindow::slot_btn_get()
{
    QTreeWidgetItem *patient_item_1 = new QTreeWidgetItem(ui->treeWidget);
    QTreeWidgetItem *patient_item_2 = new QTreeWidgetItem(ui->treeWidget);
    QTreeWidgetItem *patient_item_3 = new QTreeWidgetItem(ui->treeWidget);

    patient_item_1->setText(0, "zhangsan");
    patient_item_2->setText(0, "wangwu");
    patient_item_3->setText(0, "zhaoliu");
}
void LogWindow::slot_btn_show()
{


}
void LogWindow::slot_btn_exit()
{
    this->close();
}
void LogWindow::slot_item_doubleclicked()
{

}
