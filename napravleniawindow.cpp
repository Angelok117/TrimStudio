#include "napravleniawindow.h"
#include <QLabel>
#include <QComboBox>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QToolButton>
#include <QMessageBox>

DirectionWindow::DirectionWindow(QWidget *parent)
    : QWidget(parent)
{
    QLabel* label_title = new QLabel("Направления", this);
    QFont font_title = label_title->font();
    font_title.setBold(true);
    font_title.setPointSize(20);
    label_title->setFont(font_title);
    label_title->setAlignment(Qt::AlignCenter);

    QLabel* label_hint = new QLabel("Выберите направление в каждой категории", this);
    label_hint->setAlignment(Qt::AlignCenter);

    m_combo_modern = new QComboBox(this);
    m_combo_modern->addItem("Выберите направление");
    m_combo_modern->addItem("Хип-хоп");
    m_combo_modern->addItem("Контемпорари");
    m_combo_modern->addItem("Джаз-фанк");

    m_combo_folk = new QComboBox(this);
    m_combo_folk->addItem("Выберите направление");
    m_combo_folk->addItem("Русский народный");
    m_combo_folk->addItem("Кавказский");
    m_combo_folk->addItem("Ирландский");

    m_combo_passion = new QComboBox(this);
    m_combo_passion->addItem("Выберите направление");
    m_combo_passion->addItem("Латина");
    m_combo_passion->addItem("Бачата");
    m_combo_passion->addItem("Сальса");

    m_combo_ball = new QComboBox(this);
    m_combo_ball->addItem("Выберите направление");
    m_combo_ball->addItem("Вальс");
    m_combo_ball->addItem("Танго");
    m_combo_ball->addItem("Самба");

    QFormLayout* layout_form = new QFormLayout;
    layout_form->setHorizontalSpacing(20);
    layout_form->setVerticalSpacing(16);
    layout_form->setLabelAlignment(Qt::AlignLeft);
    layout_form->addRow("Современные", m_combo_modern);
    layout_form->addRow("Народные", m_combo_folk);
    layout_form->addRow("Страсть", m_combo_passion);
    layout_form->addRow("Бальные", m_combo_ball);

    QToolButton* button_back = new QToolButton(this);
    button_back->setArrowType(Qt::LeftArrow);
    button_back->setAutoRaise(true);
    button_back->setMinimumSize(60, 60);
    connect(button_back, &QToolButton::clicked, this, &DirectionWindow::backRequested);

    QToolButton* button_next = new QToolButton(this);
    button_next->setArrowType(Qt::RightArrow);
    button_next->setAutoRaise(true);
    button_next->setMinimumSize(60, 60);
    connect(button_next, &QToolButton::clicked, this, &DirectionWindow::onNextClicked);

    QHBoxLayout* layout_buttons = new QHBoxLayout;
    layout_buttons->addWidget(button_back);
    layout_buttons->addStretch();
    layout_buttons->addWidget(button_next);

    QVBoxLayout* layout_main = new QVBoxLayout(this);
    layout_main->setContentsMargins(60, 40, 60, 40);
    layout_main->addWidget(label_title);
    layout_main->addWidget(label_hint);
    layout_main->addSpacing(20);
    layout_main->addLayout(layout_form);
    layout_main->addStretch();
    layout_main->addLayout(layout_buttons);
}

bool DirectionWindow::isChosen(QComboBox* combo) const
{
    return combo->currentIndex() > 0;
}

void DirectionWindow::onNextClicked()
{
    if (!isChosen(m_combo_modern) || !isChosen(m_combo_folk) || !isChosen(m_combo_passion) || !isChosen(m_combo_ball))
    {
        QMessageBox::warning(this, "Внимание", "Выберите направление в каждой категории");
        return;
    }

    emit nextRequested();
}
