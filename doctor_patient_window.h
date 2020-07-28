#ifndef DOCTOR_PATIENT_WINDOW_H
#define DOCTOR_PATIENT_WINDOW_H

#include <QWidget>

namespace Ui {
class Doctor_Patient_window;
}

class Doctor_Patient_window : public QWidget
{
    Q_OBJECT

public:
    explicit Doctor_Patient_window(QString doctor_n, QString patient_n, QWidget *parent = 0);
    ~Doctor_Patient_window();

private:
    Ui::Doctor_Patient_window *ui;
};

#endif // DOCTOR_PATIENT_WINDOW_H
