// панель инструментов
#include "TopBar.h"

InputArea::InputArea(QString _area_txt)
{
    this->p_ledit = new QLineEdit(_area_txt);
    this->setBuddy(this->p_ledit);  // переход фокуса на поле ввода при нажатии

    connect
    (
        this->p_ledit,
        &QLineEdit::returnPressed,  // enter
        this,
        &InputArea::slot_enter_pressed
    );
}

InputArea::~InputArea()
{}

// Метод для получения указателя на объект QLineEdit
QLineEdit* InputArea::get_edit_area()
{
    return this->p_ledit;
}

// при нажатии клавиши Enter испускает сигнал
void InputArea::slot_enter_pressed()
{
    emit this->sig_get_text(this->p_ledit->text());
}

TopBar::TopBar
(
    QSize* _pos,
    QSize* _size,
    QWidget* _parent
) :
    QWidget(_parent),
    pos{_pos},
    size{_size}
{
    this->p_curr_tname = new QLabel("Тест");
    this->p_filter = new InputArea("Введите фильтр");
    this->p_delete_line = new InputArea("Введите строку для удаления");
    this->p_add_new_row = new QPushButton("Добавить строку");

    // макет настройки
    this->p_layout = new QHBoxLayout;

    this->p_layout->addWidget(this->p_curr_tname);  // метка имени таблицы в макет

    this->p_layout->addWidget(this->p_filter);
    this->p_layout->addWidget(this->p_filter->get_edit_area());

    this->p_layout->addWidget(this->p_delete_line);
    this->p_layout->addWidget(this->p_delete_line->get_edit_area());

    this->p_layout->addWidget(this->p_add_new_row);

    this->setLayout(this->p_layout);

    // настройка геометрии
    this->setGeometry
    (
        _pos->width(),
        _pos->height(),
        _size->width(),
        _size->height()
    );

    connect // фильтр
    (
        this->p_filter,
        &InputArea::sig_get_text,
        this,
        &TopBar::slot_filter_transmitter
    );

    connect  // удаление
    (
        this->p_delete_line,
        &InputArea::sig_get_text,
        this,
        &TopBar::slot_delete_rownum_transmitter
    );

    connect  // добавление
    (
        this->p_add_new_row,
        &QPushButton::clicked,
        this,
        &TopBar::slot_add_new_row
    );
}

TopBar::~TopBar() {}

// Слот для установки нового имени таблицы
void TopBar::slot_set_tname(QString& _tname)
{
    emit this->sig_change_tname(_tname);
}

// Слот для обработки сигнала с текстом фильтра
void TopBar::slot_filter_transmitter(const QString& _filter)
{
    emit this->sig_filter_data_transmitter(_filter);
}

// Слот для обработки сигнала с номером строки для удаления
void TopBar::slot_delete_rownum_transmitter(const QString& _rownum)
{
    emit this->sig_delete_rownum_transmitter(_rownum);
}

// Слот для обработки нажатия на кнопку добавления строки
void TopBar::slot_add_new_row()
{
    emit this->sig_add_new_row();
}
