#ifndef PRICEWINDOW_H
#define PRICEWINDOW_H

#include <QWidget>

class QLabel;
class QSlider;
class QLineEdit;
class QCheckBox;
class QPushButton;
class QStackedWidget;

class PriceWindow : public QWidget
{
    Q_OBJECT

public:
    explicit PriceWindow(QWidget *parent = nullptr);

    void setLessonCount(int count);

signals:
    void backRequested();
    void homeRequested();

private slots:
    void onCalculateClicked();
    void onConfirmClicked();
    void onCheckChanged();

private:
    QLabel* m_label_days;
    QSlider* m_slider_months;
    QLabel* m_label_months;
    QLineEdit* m_line_sum;
    QCheckBox* m_check_agree;
    QLineEdit* m_line_name;
    QPushButton* m_button_confirm;
    QStackedWidget* m_stack;
    int m_lessons;
};
#endif