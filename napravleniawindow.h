#ifndef DIRECTIONWINDOW_H
#define DIRECTIONWINDOW_H

#include <QWidget>

class QComboBox;

class DirectionWindow : public QWidget
{
    Q_OBJECT

public:
    explicit DirectionWindow(QWidget *parent = nullptr);

signals:
    void backRequested();
    void nextRequested();

private slots:
    void onNextClicked();

private:
    bool isChosen(QComboBox* combo) const;

    QComboBox* m_combo_modern;
    QComboBox* m_combo_folk;
    QComboBox* m_combo_passion;
    QComboBox* m_combo_ball;
};
#endif