#ifndef SCHEDULEWINDOW_H
#define SCHEDULEWINDOW_H

#include <QWidget>
#include <QSet>

class QTableWidget;
class QLabel;

class ScheduleWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ScheduleWindow(QWidget *parent = nullptr);

    int lessonCount() const;

signals:
    void backRequested();
    void nextRequested();

private slots:
    void onCellClicked(int row, int column);
    void onNextClicked();

private:
    void updateCell(int row, int column);
    void updateCount();

    QTableWidget* m_table;
    QLabel* m_label_count;
    QSet<int> m_days;
};
#endif
