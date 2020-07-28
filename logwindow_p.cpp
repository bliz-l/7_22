#include "logwindow_p.h"
#include "ui_logwindow_p.h"

LogWindow_P::LogWindow_P(QString user, QString type, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LogWindow_P)
{
    ui->setupUi(this);

    count = 0;
    x = -10;
    m_timer = new QTimer(this);
    m_timer->start(10);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(slot_data_form()));
    //timeout 与slot关联
    QString str=user;
    str+="_";
    str+=type;
    str="登录:"+str;
    this->setWindowTitle(str);


}

LogWindow_P::~LogWindow_P()
{
    delete ui;
}

void LogWindow_P::slot_data_form()
{
    //生成波形数据
    x+=0.2;
    xList.append(x);
    yList.append(qSin(x));
    count++;
    if(count%2 == 0)
    {
        update();
    }
    if(count == 100)
    {
        xList.clear();
        yList.clear();
        count = 0;
        x = -10;
    }
}
void LogWindow_P::paintEvent(QPaintEvent *event)
{
    //画心电图
    QPainter painter(this);
    //设置画笔
    QPen pen;
    pen.setColor(Qt::black);
    pen.setStyle(Qt::SolidLine);
    pen.setWidth(0.5);
    //使用画笔
    painter.setPen(pen);

    //设置画图区域
    painter.setViewport(50, 50, width()-100, height()-100);
    painter.setWindow(-10, 2, 20,-4);//物理区域
    painter.fillRect(-10, 2, 20, -4, Qt::white);

    //直线
    painter.drawLine(-10, 0, 10, 0);

    //波形
    for(int i=0; i<yList.count(); i++)
    {
        if(i == 0)
        {
            //先画点
            painter.drawPoint(QPointF(xList[i], yList[i]));
        }
        else
        {
            //连线
            painter.drawLine(QPointF(xList[i-1], yList[i-1]),
                             QPointF(xList[i], yList[i]));
        }
    }
}
