#include "aboutwindow.h"
#include <QLabel>
#include <QPushButton>
#include <QIcon>
#include <QHBoxLayout>
#include <QVBoxLayout>

AboutWindow::AboutWindow(QWidget *parent)
    : QWidget(parent)
{
    QLabel* label_title = new QLabel("О нас", this);
    QFont font_title = label_title->font();
    font_title.setBold(true);
    font_title.setPointSize(20);
    label_title->setFont(font_title);
    label_title->setAlignment(Qt::AlignCenter);

    QHBoxLayout* layout_columns = new QHBoxLayout;
    layout_columns->setSpacing(30);
    layout_columns->addWidget(createColumn("Софа", "https://vk.ru/sofie_mur", ":/img/img/sofa.png", "Замурчательный руководитель народного танца. Докажу, что кокошник — это не бабушкин сундук, а главный аксессуар сезона. Научу вас надевать его так, чтобы завидовали все, и отплясывать «Яблочко» с таким задором, что соседи начнут стучать в такт."));
    layout_columns->addWidget(createColumn("Ангел", "https://vk.ru/angelbelyaeva", ":/img/img/angel.png", "Очаровательный руководитель бальных танцев. Научу вас кружиться по паркету так, чтобы даже люстры закружились от зависти. Докажу, что вальс — это не просто три шага, а настоящее искусство покорять сердца и танцпол!"));
    layout_columns->addWidget(createColumn("Сыч", "https://vk.ru/bartok_3972", ":/img/img/sonya.png", "Невероятный и многогранный руководитель всех видов танца (особенно страстных). Если танец — это огонь, то я — это спичка, которая его зажигает. Научу вас быть не просто огоньком, а настоящим пожаром на паркете"));

    QPushButton* button_home = new QPushButton("Главное меню", this);
    connect(button_home, &QPushButton::clicked, this, &AboutWindow::homeRequested);

    QVBoxLayout* layout_main = new QVBoxLayout(this);
    layout_main->setContentsMargins(40, 30, 40, 30);
    layout_main->addWidget(label_title);
    layout_main->addSpacing(20);
    layout_main->addLayout(layout_columns);
    layout_main->addStretch();
    layout_main->addWidget(button_home, 0, Qt::AlignCenter);
}

QWidget* AboutWindow::createColumn(const QString &name, const QString &link, const QString &photo, const QString &info)
{
    QWidget* column = new QWidget(this);

    QLabel* label_photo = new QLabel(column);
    label_photo->setPixmap(QIcon(photo).pixmap(140, 140));
    label_photo->setAlignment(Qt::AlignCenter);

    QLabel* label_name = new QLabel(name, column);
    QFont font_name = label_name->font();
    font_name.setBold(true);
    font_name.setPointSize(14);
    label_name->setFont(font_name);
    label_name->setAlignment(Qt::AlignCenter);

    QLabel* label_link = new QLabel("<a href=\"" + link + "\">VK</a>", column);
    label_link->setOpenExternalLinks(true);
    label_link->setAlignment(Qt::AlignCenter);

    QLabel* label_text = new QLabel(info, column);
    label_text->setWordWrap(true);
    label_text->setAlignment(Qt::AlignCenter);

    QVBoxLayout* layout_column = new QVBoxLayout(column);
    layout_column->addWidget(label_photo);
    layout_column->addWidget(label_name);
    layout_column->addWidget(label_link);
    layout_column->addWidget(label_text);
    layout_column->addStretch();
    return column;
}
