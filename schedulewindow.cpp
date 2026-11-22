#include "schedulewindow.h"
#include <QLabel>
#include <QTableWidget>
#include <QHeaderView>
#include <QToolButton>
#include <QMessageBox>
#include <QHBoxLayout>
#include <QVBoxLayout>

ScheduleWindow::ScheduleWindow(QWidget *parent)
    : QWidget(parent)
{
    QLabel* label_title = new QLabel("Расписание", this);
    QFont font_title = label_title->font();
    font_title.setBold(true);
    font_title.setPointSize(20);
    label_title->setFont(font_title);
    label_title->setAlignment(Qt::AlignCenter);

    QLabel* label_hint = new QLabel("Отметьте дни занятий, не больше 10", this);
    label_hint->setAlignment(Qt::AlignCenter);

    m_table = new QTableWidget(5, 7, this);
    m_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_table->setSelectionMode(QAbstractItemView::NoSelection);
    m_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    m_table->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    m_table->horizontalHeader()->setVisible(false);
    m_table->verticalHeader()->setVisible(false);
    connect(m_table, &QTableWidget::cellClicked, this, &ScheduleWindow::onCellClicked);

    for (int row = 0; row < 5; row++)
    {
        for (int column = 0; column < 7; column++)
        {
            int day = row * 7 + column + 1;
            QTableWidgetItem* item = new QTableWidgetItem(QString::number(day));
            item->setTextAlignment(Qt::AlignCenter);
            m_table->setItem(row, column, item);
        }
    }
    m_table->item(4, 3)->setText("");
    m_table->item(4, 4)->setText("");
    m_table->item(4, 5)->setText("");
    m_table->item(4, 6)->setText("");

    m_label_count = new QLabel(this);
    m_label_count->setAlignment(Qt::AlignCenter);

    QToolButton* button_back = new QToolButton(this);
    button_back->setArrowType(Qt::LeftArrow);
    button_back->setAutoRaise(true);
    button_back->setMinimumSize(60, 60);
    connect(button_back, &QToolButton::clicked, this, &ScheduleWindow::backRequested);

    QToolButton* button_next = new QToolButton(this);
    button_next->setArrowType(Qt::RightArrow);
    button_next->setAutoRaise(true);
    button_next->setMinimumSize(60, 60);
    connect(button_next, &QToolButton::clicked, this, &ScheduleWindow::onNextClicked);

    QHBoxLayout* layout_buttons = new QHBoxLayout;
    layout_buttons->addWidget(button_back);
    layout_buttons->addStretch();
    layout_buttons->addWidget(button_next);

    QVBoxLayout* layout_main = new QVBoxLayout(this);
    layout_main->setContentsMargins(60, 30, 60, 30);
    layout_main->addWidget(label_title);
    layout_main->addWidget(label_hint);
    layout_main->addSpacing(20);
    layout_main->addWidget(m_table, 1);
    layout_main->addWidget(m_label_count);
    layout_main->addLayout(layout_buttons);

    updateCount();
}

int ScheduleWindow::lessonCount() const
{
    return m_days.size();
}

void ScheduleWindow::updateCell(int row, int column)
{
    QTableWidgetItem* item = m_table->item(row, column);
    if (item == nullptr || item->text().isEmpty())
    {
        return;
    }

    int day = row * 7 + column + 1;
    if (m_days.contains(day))
    {
        item->setBackground(QColor(170, 90, 200));
        item->setForeground(Qt::white);
        QFont font_item = item->font();
        font_item.setBold(true);
        item->setFont(font_item);
    }
    else
    {
        item->setBackground(Qt::white);
        item->setForeground(Qt::black);
        QFont font_item = item->font();
        font_item.setBold(false);
        item->setFont(font_item);
    }
}

void ScheduleWindow::updateCount()
{
    m_label_count->setText("Выбрано занятий: " + QString::number(m_days.size()));
}

void ScheduleWindow::onCellClicked(int row, int column)
{
    QTableWidgetItem* item = m_table->item(row, column);
    if (item == nullptr || item->text().isEmpty())
    {
        return;
    }

    int day = row * 7 + column + 1;
    if (m_days.contains(day))
    {
        m_days.remove(day);
    }
    else
    {
        if (m_days.size() >= 10)
        {
            QMessageBox::warning(this, "Внимание", "Можно выбрать не больше 10 занятий");
            return;
        }
        m_days.insert(day);
    }

    updateCell(row, column);
    updateCount();
}

void ScheduleWindow::onNextClicked()
{
    if (m_days.isEmpty())
    {
        QMessageBox::warning(this, "Внимание", "Отметьте хотя бы один день");
        return;
    }

    emit nextRequested();
}
