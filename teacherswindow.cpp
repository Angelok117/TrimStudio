#include "teacherswindow.h"
#include <QLabel>
#include <QPushButton>
#include <QIcon>
#include <QListWidget>
#include <QVBoxLayout>

TeachersWindow::TeachersWindow(QWidget *parent)
    : QWidget(parent)
{
    QLabel* label_title = new QLabel("Педагоги", this);
    QFont font_title = label_title->font();
    font_title.setBold(true);
    font_title.setPointSize(20);
    label_title->setFont(font_title);
    label_title->setAlignment(Qt::AlignCenter);

    QListWidget* list_teachers = new QListWidget(this);
    list_teachers->setIconSize(QSize(120, 180));
    list_teachers->addItem(new QListWidgetItem(QIcon(":/img/img/1.jpg"), "Сычуанский, Сальса"));
    list_teachers->addItem(new QListWidgetItem(QIcon(":/img/img/2.jpg"), "Соня-Спайс, Бачата"));
    list_teachers->addItem(new QListWidgetItem(QIcon(":/img/img/3.jpg"), "Соня-Сноу, Румба"));
    list_teachers->addItem(new QListWidgetItem(QIcon(":/img/img/4.jpg"), "Сыч, Латина"));
    list_teachers->addItem(new QListWidgetItem(QIcon(":/img/img/5.jpg"), "Афро-соня, Афро Дэнс"));
    list_teachers->addItem(new QListWidgetItem(QIcon(":/img/img/6.jpg"), "Сониолли, Танго"));
    list_teachers->addItem(new QListWidgetItem(QIcon(":/img/img/7.jpg"), "Сонич, Ча-ча-ча"));
    list_teachers->addItem(new QListWidgetItem(QIcon(":/img/img/8.jpg"), "Сончелла, Хип-хоп"));
    list_teachers->addItem(new QListWidgetItem(QIcon(":/img/img/9.jpg"), "Соньета, Контемпорари"));
    list_teachers->addItem(new QListWidgetItem(QIcon(":/img/img/11.jpg"), "Соня-комета, Кавказские танцы"));
    list_teachers->addItem(new QListWidgetItem(QIcon(":/img/img/12.jpg"), "Сонисима, Ирландские танцы"));
    list_teachers->addItem(new QListWidgetItem(QIcon(":/img/img/13.jpeg"), "Софа, Русские народные танцы"));
    list_teachers->addItem(new QListWidgetItem(QIcon(":/img/img/14.png"), "Ангел, Бальные танцы"));

    QPushButton* button_home = new QPushButton("Главное меню", this);
    connect(button_home, &QPushButton::clicked, this, &TeachersWindow::homeRequested);

    QVBoxLayout* layout_main = new QVBoxLayout(this);
    layout_main->setContentsMargins(60, 40, 60, 40);
    layout_main->addWidget(label_title);
    layout_main->addWidget(list_teachers, 1);
    layout_main->addWidget(button_home, 0, Qt::AlignCenter);
}
