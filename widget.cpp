#include "widget.h"
#include "ui_widget.h"


Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setWindowTitle("登录界面");//设置窗口名称
    //设置文本框的提示
    ui->ledit_user->setPlaceholderText("用户名");
    ui->ledit_passwd->setPlaceholderText("密码");
    ui->ledit_passwd->setEchoMode(QLineEdit::Password);

    //连接退出按钮的单击信号槽函数
    connect(ui->btn_exit, SIGNAL(clicked(bool)), this, SLOT(close()));

    //注册
    connect(ui->btn_reg, SIGNAL(clicked(bool)), this, SLOT(slot_btn_reg()));
    //登录
    udpsock_log = new QUdpSocket();//在头文件中定义
    connect(ui->btn_login, SIGNAL(clicked(bool)), this, SLOT(slot_btn_log()));
    connect(udpsock_log, SIGNAL(readyRead()), this, SLOT(slot_ReadyRead_log()));
}

Widget::~Widget()
{
    delete ui;
}
void Widget::slot_btn_reg()
{
    //显示注册窗口
    //1、定义窗口类
    RegWindow *reg_win = new RegWindow();
    reg_win->setAttribute(Qt::WA_DeleteOnClose);
    //2、显示窗口
    reg_win->show();
}
void Widget::slot_btn_log()
{
    //发送的数据：用户名 密码 性别 年龄
    //1、将发送的数据打包
    QString user_str = ui->ledit_user->text();
    QString passwd_str = ui->ledit_passwd->text();
    if(user_str.isEmpty()||passwd_str.isEmpty())
    {
        QMessageBox::information(this,"登录信息","请输入完整的登录信息");
        return;
    }
    //封装数据
    struct login_struct login;
    //封装、字符串类型转变，从QString转换为std string，最后转为C语言字符串
    qsnprintf(login.log_user,20,user_str.toStdString().c_str());
    qsnprintf(login.log_passwd,20,passwd_str.toStdString().c_str());
    //2、将打包后的数据发送到服务器端
    //功能：通过网络发送数据
    //参数：发送的数据 接收方的IP 接收方的端口号
    QHostAddress *address = new QHostAddress(LOG_SERVER_IP);
    qint64 ret = udpsock_log->writeDatagram((char *)&login,sizeof(login),*address,LOG_SERVER_PORT);
    if(ret<0)
    {
        QMessageBox::information(this,"发送信息","发送登录数据失败");
        return;
    }
    //qDebug()<<user_str;
}

void Widget::slot_ReadyRead_log()
{
    struct log_result_struct result;
    udpsock_log->readDatagram((char *)&result,sizeof(struct log_result_struct));
    if(result.result==1)
    {
        QMessageBox::information(this,"登录结果","登录成功！");
        //打开登录窗口
        if(result.type == DOCTOR)
        {
            LogWindow *log_win = new LogWindow;
            log_win->setAttribute(Qt::WA_DeleteOnClose);
            log_win->show();
        }
        else if(result.type == PATIENT)
        {
            LogWindow_P *log_win_p = new LogWindow_P;
            log_win_p->setAttribute(Qt::WA_DeleteOnClose);
            log_win_p->show();
        }


    }
    else
    {
        QMessageBox::information(this,"登录结果","用户名或密码错误");
    }
}
