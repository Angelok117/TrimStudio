#include "mainwindow.h"
#include "napravleniawindow.h"
#include "teacherswindow.h"
#include "schedulewindow.h"
#include <QLabel>
#include <QIcon>
#include <QPushButton>
#include <QStackedWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QUrl>
#include <QDesktopServices>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setMinimumSize(800, 600);
    setWindowTitle("TrimDance");
    setWindowIcon(QIcon(":/img/00.png"));

    m_stack = new QStackedWidget(this);
    m_direction = new DirectionWindow(this);
    m_teachers = new TeachersWindow(this);
    m_schedule = new ScheduleWindow(this);
    setCentralWidget(m_stack);

    m_stack->addWidget(createMainPage());
    m_stack->addWidget(m_direction);
    m_stack->addWidget(m_teachers);
    m_stack->addWidget(m_schedule);

    connect(m_direction, &DirectionWindow::backRequested, this, [this]() {
        showPage(m_stack->widget(0));
    });

    connect(m_teachers, &TeachersWindow::homeRequested, this, [this]() {
        showPage(m_stack->widget(0));
    });

    connect(m_direction, &DirectionWindow::nextRequested, this, [this]() {
        showPage(m_schedule);
    });

    connect(m_schedule, &ScheduleWindow::backRequested, this, [this]() {
        showPage(m_direction);
    });
}

MainWindow::~MainWindow() = default;

void MainWindow::showPage(QWidget* page)
{
    m_stack->setCurrentWidget(page);
}

QWidget* MainWindow::createMainPage()
{
    QWidget* page = new QWidget(this);

    QLabel* label_logo = new QLabel(page);
    label_logo->setPixmap(QIcon(":/img/00.png").pixmap(80, 80));

    QLabel* label_title = new QLabel("TrimDance", page);
    QFont font_title = label_title->font();
    font_title.setBold(true);
    font_title.setPointSize(28);
    label_title->setFont(font_title);

    QLabel* label_subtitle = new QLabel("Танцевальная студия", page);

    QVBoxLayout* layout_titles = new QVBoxLayout;
    layout_titles->setSpacing(0);
    layout_titles->addWidget(label_title);
    layout_titles->addWidget(label_subtitle);

    QHBoxLayout* layout_header = new QHBoxLayout;
    layout_header->addWidget(label_logo);
    layout_header->addLayout(layout_titles);
    layout_header->addStretch();

    QPushButton* button_sign = new QPushButton("ЗАПИСЬ", page);
    button_sign->setMinimumSize(260, 220);
    QFont font_sign = button_sign->font();
    font_sign.setBold(true);
    font_sign.setPointSize(24);
    button_sign->setFont(font_sign);

    QPushButton* button_about = new QPushButton("О нас", page);
    QPushButton* button_photo = new QPushButton("Фото", page);
    QPushButton* button_teachers = new QPushButton("Педагоги", page);

    QVBoxLayout* layout_right = new QVBoxLayout;
    layout_right->setSpacing(20);
    layout_right->addWidget(button_about);
    layout_right->addWidget(button_photo);
    layout_right->addWidget(button_teachers);

    QHBoxLayout* layout_center = new QHBoxLayout;
    layout_center->setSpacing(40);
    layout_center->addWidget(button_sign);
    layout_center->addLayout(layout_right);

    QVBoxLayout* layout_main = new QVBoxLayout(page);
    layout_main->setContentsMargins(50, 30, 50, 40);
    layout_main->addLayout(layout_header);
    layout_main->addStretch();
    layout_main->addLayout(layout_center);
    layout_main->addStretch();

    connect(button_photo, &QPushButton::clicked, this, []() {
        QDesktopServices::openUrl(QUrl("https://disk.yandex.ru/d/-_jKPWhKPeDFEQ"));
    });

    connect(button_sign, &QPushButton::clicked, this, [this]() {
        showPage(m_direction);
    });

    connect(button_teachers, &QPushButton::clicked, this, [this]() {
        showPage(m_teachers);
    });

    return page;
}
