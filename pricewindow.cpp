#include "pricewindow.h"
#include <QLabel>
#include <QSlider>
#include <QLineEdit>
#include <QCheckBox>
#include <QPushButton>
#include <QStackedWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QToolButton>
#include <QStyle>
#include <QMessageBox>
PriceWindow::PriceWindow(QWidget *parent)
    : QWidget(parent)
    , m_lessons(1)
{
    QLabel* label_title = new QLabel("Стоимость", this);
    QFont font_title = label_title->font();
    font_title.setBold(true);
    font_title.setPointSize(20);
    label_title->setFont(font_title);
    label_title->setAlignment(Qt::AlignCenter);

    m_label_days = new QLabel("Дней: 1", this);

    m_slider_months = new QSlider(Qt::Horizontal, this);
    m_slider_months->setRange(1, 12);
    m_slider_months->setValue(1);
    m_slider_months->setTickPosition(QSlider::TicksBelow);
    m_slider_months->setTickInterval(1);
    m_label_months = new QLabel("Месяцев: 1", this);
    connect(m_slider_months, &QSlider::valueChanged, this, [this](int value) {
        m_label_months->setText("Месяцев: " + QString::number(value));
    });

    QLabel* label_price = new QLabel("Цена за зан.: 50 р.", this);

    QPushButton* button_calc = new QPushButton("Расчет", this);
    m_line_sum = new QLineEdit(this);
    m_line_sum->setReadOnly(true);
    m_line_sum->setPlaceholderText("Итоговая сумма");
    connect(button_calc, &QPushButton::clicked, this, &PriceWindow::onCalculateClicked);

    QHBoxLayout* layout_calc = new QHBoxLayout;
    layout_calc->addWidget(button_calc);
    layout_calc->addWidget(m_line_sum);

    QLabel* label_arrow = new QLabel(this);
    label_arrow->setPixmap(style()->standardIcon(QStyle::SP_ArrowDown).pixmap(24, 24));
    label_arrow->setAlignment(Qt::AlignCenter);

    QHBoxLayout* layout_arrow = new QHBoxLayout;
    layout_arrow->addStretch();
    layout_arrow->addWidget(label_arrow);
    layout_arrow->addStretch();

    m_check_agree = new QCheckBox("Ознакомлен(а)", this);
    connect(m_check_agree, &QCheckBox::checkStateChanged, this, &PriceWindow::onCheckChanged);

    QLabel* label_name = new QLabel("Введите имя:", this);
    m_line_name = new QLineEdit(this);
    m_line_name->setPlaceholderText("Ваше имя");
    connect(m_line_name, &QLineEdit::textChanged, this, &PriceWindow::onCheckChanged);

    m_button_confirm = new QPushButton("Подтвердить", this);
    m_button_confirm->setEnabled(false);
    connect(m_button_confirm, &QPushButton::clicked, this, &PriceWindow::onConfirmClicked);

    QWidget* page_form = new QWidget(this);
    QVBoxLayout* layout_form = new QVBoxLayout(page_form);
    layout_form->addWidget(m_label_days);
    layout_form->addWidget(m_slider_months);
    layout_form->addWidget(m_label_months);
    layout_form->addWidget(label_price);
    layout_form->addSpacing(10);
    layout_form->addLayout(layout_calc);
    layout_form->addSpacing(20);
    layout_form->addLayout(layout_arrow);
    layout_form->addWidget(m_check_agree);
    layout_form->addWidget(label_name);
    layout_form->addWidget(m_line_name);
    layout_form->addWidget(m_button_confirm);

    QWidget* page_done = new QWidget(this);
    QLabel* label_done = new QLabel("Ура, вы записаны!", page_done);
    font_title.setPointSize(24);
    label_done->setFont(font_title);
    label_done->setAlignment(Qt::AlignCenter);
    QPushButton* button_home = new QPushButton("Вернуться на главную", page_done);
    connect(button_home, &QPushButton::clicked, this, [this]() {
        m_stack->setCurrentIndex(0);
        m_check_agree->setChecked(false);
        m_line_name->clear();
        m_line_sum->clear();
        m_slider_months->setValue(1);
        emit homeRequested();
    });

    QVBoxLayout* layout_done = new QVBoxLayout(page_done);
    layout_done->addStretch();
    layout_done->addWidget(label_done);
    layout_done->addWidget(button_home, 0, Qt::AlignCenter);
    layout_done->addStretch();

    m_stack = new QStackedWidget(this);
    m_stack->addWidget(page_form);
    m_stack->addWidget(page_done);

    QToolButton* button_back = new QToolButton(this);
    button_back->setArrowType(Qt::LeftArrow);
    button_back->setAutoRaise(true);
    button_back->setMinimumSize(60, 60);
    connect(button_back, &QToolButton::clicked, this, &PriceWindow::backRequested);

    QHBoxLayout* layout_buttons = new QHBoxLayout;
    layout_buttons->addWidget(button_back);
    layout_buttons->addStretch();

    QVBoxLayout* layout_main = new QVBoxLayout(this);
    layout_main->setContentsMargins(60, 40, 60, 40);
    layout_main->addWidget(label_title);
    layout_main->addWidget(m_stack);
    layout_main->addLayout(layout_buttons);
}

void PriceWindow::setLessonCount(int count){
    m_lessons = count;
    m_label_days->setText("Дней: " + QString::number(count));
}

void PriceWindow::onCalculateClicked(){
    int months = m_slider_months->value();
    int sum = m_lessons * months * 50;
    m_line_sum->setText(QString::number(sum) + " р.");
}

void PriceWindow::onCheckChanged() {
    m_button_confirm->setEnabled(m_check_agree->isChecked() && !m_line_name->text().trimmed().isEmpty());
}

void PriceWindow::onConfirmClicked(){
    m_stack->setCurrentIndex(1);
}