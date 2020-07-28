#ifndef DOCTOR_PATIENT_WINDOW_H
#define DOCTOR_PATIENT_WINDOW_H

#include <QWidget>
#include <QPainter>
#include <QList>
#include <QTimer>
#include <QtCore/qmath.h>
#include <QPointF>

namespace Ui {
class Doctor_Patient_window;
}

class Doctor_Patient_window : public QWidget
{
    Q_OBJECT

public:
    explicit Doctor_Patient_window(QString doctor_n, QString patient_n, QWidget *parent = 0);
    ~Doctor_Patient_window();
    void paintEvent(QPaintEvent *);
public slots:
    void slot_data_form(void);

private:
    Ui::Doctor_Patient_window *ui;
    //定义存储列表QList
    QList<float> xList;
    QList<float> yList;
    //定义timer
    QTimer *m_timer;
    float x;
    int count;
};

#endif // DOCTOR_PATIENT_WINDOW_H
