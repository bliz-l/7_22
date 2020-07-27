#ifndef LOGWINDOW_H
#define LOGWINDOW_H

#include <QWidget>
#include "widget.h"

namespace Ui {
class LogWindow;
}

class LogWindow : public QWidget
{
    Q_OBJECT

public:
    explicit LogWindow(QWidget *parent = 0);
    ~LogWindow();




private:
    Ui::LogWindow *ui;
};

#endif // LOGWINDOW_H
