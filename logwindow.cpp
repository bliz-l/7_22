#include "logwindow.h"
#include "ui_logwindow.h"

LogWindow::LogWindow(QString user, QString type, QWidget *parent):
    QWidget(parent),
    ui(new Ui::LogWindow)
{
    ui->setupUi(this);
    //定义Qtreewidgetitem
    udpsock = new QUdpSocket();//定义udpsock

    QString str=user;
    str+="_";
    str+=type;
    str="登录:"+str;
    this->setWindowTitle(str);

    connect(ui->btn_show, SIGNAL(clicked(bool)), this, SLOT(slot_btn_show()));
    connect(ui->btn_exit, SIGNAL(clicked(bool)), this, SLOT(slot_btn_exit()));
    connect(ui->btn_get, SIGNAL(clicked(bool)), this, SLOT(slot_btn_get()));
    connect(ui->treeWidget, SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)), this, SLOT(slot_item_doubleclicked(QTreeWidgetItem*,int)));
    connect(udpsock, SIGNAL(readyRead()), this, SLOT(slot_ReadyRead()));


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
    //创建患者窗口，再医生界面也可以打开患者实时状态
    QString patient = "zhangsan";
    QString doctor = "lisi";
    Doctor_Patient_window *doc_pat_win = new Doctor_Patient_window(doctor,patient);
    doc_pat_win->setAttribute(Qt::WA_DeleteOnClose);
    doc_pat_win->show();


}
void LogWindow::slot_btn_exit()
{
    this->close();
}
void LogWindow::slot_item_doubleclicked(QTreeWidgetItem* patient_pointer,int column )
{
        //读取QTreeWidgetitem中病人的名字
        QString patient_name = patient_pointer->text(column);
        QString doctor_name = "lisi";//有待解决，如何将user传入
        ui->redit_name->setText(patient_name);
        //封装数据
        struct patient_search snd_info;
        //转换数据格式
        qsnprintf(snd_info.send_doctor,20,doctor_name.toStdString().c_str());
        qsnprintf(snd_info.send_patient,20,patient_name.toStdString().c_str());
        //设定发送目标地址
        QHostAddress *address = new QHostAddress(SEARCH_SERVER_IP);
        qint64 ret = udpsock->writeDatagram((char *)&snd_info,sizeof(snd_info),*address,SEARCH_SERVER_PORT);
        if(ret<0)
        {
            QMessageBox::information(this,"发送信息","发送登录数据失败");
            return;
        }
}
void LogWindow::slot_ReadyRead()
{
    struct patient_info result;
    udpsock->readDatagram((char *)&result,sizeof(struct patient_info));
    if(result.result == 1)
    {
        //QString search_age = QString::number(result.age,10);
        QString search_age = "18";
        QString search_sex;
        //if(result.sex == 0)
        //{
            //search_sex = "female";
       // }
        //else
        //{
           search_sex = "male";
        //}
        QString search_medic = result.medic;
        QString search_text = result.text;
        //显示信息
        ui->redit_age->setText(search_age);
        ui->redit_medic->setText(search_medic);
        ui->redit_sex->setText(search_sex);
        ui->redit_record->setText(search_text);
        QMessageBox::information(this, "查询结果", "查询成功");
    }
    else
    {
        QMessageBox::information(this, "查询结果", "查无此人");
    }

}
