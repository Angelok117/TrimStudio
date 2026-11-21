#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QStackedWidget;
class DirectionWindow;
class TeachersWindow;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private:
    QWidget* createMainPage();
    void showPage(QWidget* page);

    QStackedWidget* m_stack;
    DirectionWindow* m_direction;
    TeachersWindow* m_teachers;
};
#endif
