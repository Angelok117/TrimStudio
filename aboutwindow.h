#ifndef ABOUTWINDOW_H
#define ABOUTWINDOW_H

#include <QWidget>

class AboutWindow : public QWidget
{
    Q_OBJECT

public:
    explicit AboutWindow(QWidget *parent = nullptr);

signals:
    void homeRequested();

private:
    QWidget* createColumn(const QString &name, const QString &link, const QString &photo, const QString &info);
};
#endif
