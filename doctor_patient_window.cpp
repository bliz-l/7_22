#include "doctor_patient_window.h"
#include "ui_doctor_patient_window.h"

Doctor_Patient_window::Doctor_Patient_window(QString doctor_n, QString patient_n, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Doctor_Patient_window)
{
    ui->setupUi(this);
    QString str=doctor_n;
    str+="_";
    str+=patient_n;

    this->setWindowTitle(str);
}

Doctor_Patient_window::~Doctor_Patient_window()
{
    delete ui;
}
