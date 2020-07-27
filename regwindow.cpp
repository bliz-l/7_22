#include "regwindow.h"
#include "ui_regwindow.h"

RegWindow::RegWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RegWindow)
{
    ui->setupUi(this);
    udpsock = new QUdpSocket();
    this->setWindowTitle("注册窗口");
    ui->ledit_user->setPlaceholderText("用户名");
    ui->ledit_passwd->setPlaceholderText("密码");
    ui->ledit_age->setPlaceholderText("年龄");
    ui->ledit_passwd->setEchoMode(QLineEdit::Password);
    ui->rbtn_man->setChecked(true);
    ui->rbtn_woman->setChecked(false);
    connect(ui->btn_reg,SIGNAL(clicked(bool)),this,SLOT(slot_btn_reg_clicked()));
    connect(udpsock,SIGNAL(readyRead()),this,SLOT(slot_readyRead()));
}

RegWindow::~RegWindow()
{
    delete ui;
}

void RegWindow::on_rbtn_man_clicked()
{
    ui->rbtn_woman->setChecked(false);
}

void RegWindow::on_rbtn_woman_clicked()
{
    ui->rbtn_man->setChecked(false);
}
//注册按钮槽函数
void RegWindow::slot_btn_reg_clicked()
{
    //发送的数据：用户名 密码 性别 年龄
    //1、将发送的数据打包
    QString user_str = ui->ledit_user->text();
    QString passwd_str = ui->ledit_passwd->text();
    QString age_str = ui->ledit_age->text();
    if(user_str.isEmpty()||passwd_str.isEmpty()||age_str.isEmpty())
    {
        QMessageBox::information(this,"注册信息","请输入完整的注册信息");
        return;
    }
    int sex;
    if(ui->rbtn_woman->isChecked())
    {
        sex = FEMALE;
    }
    else
    {
        sex = MALE;
    }
    //封装数据
    struct reg_struct reg;
    //封装、字符串类型转变，从QString转换为std string，最后转为C语言字符串
    qsnprintf(reg.reg_user,20,user_str.toStdString().c_str());
    qsnprintf(reg.reg_passwd,20,passwd_str.toStdString().c_str());
    reg.reg_age = age_str.toInt();
    reg.reg_sex = sex;
    //2、将打包后的数据发送到服务器端
    //功能：通过网络发送数据
    //参数：发送的数据 接收方的IP 接收方的端口号
    QHostAddress *address = new QHostAddress(REG_SERVER_IP);
    qint64 ret = udpsock->writeDatagram((char *)&reg,sizeof(reg),*address,REG_SERVER_PORT);
    if(ret<0)
    {
        QMessageBox::information(this,"发送信息","注册窗口发送数据失败");
        return;
    }
    qDebug()<<user_str;
}

void RegWindow::slot_readyRead()
{
    struct result_struct result;
    udpsock->readDatagram((char *)&result,sizeof(struct result_struct));
    if(result.result==1)
    {
        QMessageBox::information(this,"注册结果","注册成功！");
    }
    else
    {
        QMessageBox::information(this,"注册结果","注册失败");
    }
}
