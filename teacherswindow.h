#ifndef TEACHERSWINDOW_H
#define TEACHERSWINDOW_H

#include <QWidget>

class TeachersWindow : public QWidget
{
    Q_OBJECT

public:
    explicit TeachersWindow(QWidget *parent = nullptr);

signals:
    void homeRequested();
};
#endif
