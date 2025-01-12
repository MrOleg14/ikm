// функционал меню
#include "../includes.h"
#include "MenuBar.h"

MenuBar::MenuBar
(
    QSize* _size,
    QSize* _pos,
    bool _orient_layout,  // ориентация макета (true - вертикальная, false - горизонтальная)
    QWidget* _parent
    ) :
    QWidget(_parent),
    p_size(_size),
    p_position(_pos)
{
    if(_orient_layout)  // условие для выбора типа макета
        this->p_menu_layout = new QVBoxLayout;
    else
        this->p_menu_layout = new QHBoxLayout;

    this->setLayout(this->p_menu_layout);
    this->setGeometry  // установка геометрии
    (
        _pos->width(),
        _pos->height(),
        _size->width(),
        _size->height()
    );

    this->p_items_list = new QList<CustomButton*>;  // новый список для хранения указателей
}

MenuBar::~MenuBar()
{
    delete this->p_size;
    delete this->p_position;
    delete this->p_menu_layout;
    delete this->p_items_list;
}

void MenuBar::appendObject  // перегрузка (метод добавления кнопки типа CustomButton в меню)
(
    EMITS_BTN_SIGNALS _btn_sig,
    QString _p_obj, /*для rvalue аргументов */  // путь к иконке
    QString _p_txt  // текст кнопки
)
{
    CustomButton* tmp_object = new CustomButton(_btn_sig, _p_obj);  // Создает объект
    this->p_menu_layout->addWidget(tmp_object);  // Добавляет кнопку в макет
    this->p_items_list->append(tmp_object);  // Добавляет указатель на кнопку в список

    connect  // соединение между сигналом и слотом
    (
        tmp_object,
        &CustomButton::is_be_checked,
        this,
        &MenuBar::sig_distrib_handler
    );
}

void MenuBar::appendObject  // перегрузка (метод добавления кнопки типа AugmentButton в меню)
(
    EMITS_BTN_SIGNALS _btn_sig,
    QString _btn_txt  // текст для кнопки
)
{
    AugmentButton* tmp_object = new AugmentButton(_btn_sig, _btn_txt);

    // установить белый цвет на кнопке
    tmp_object->setPalette(QPalette(Qt::white));
    tmp_object->setText(_btn_txt);
    this->p_menu_layout->addWidget(tmp_object);

    connect
    (
        tmp_object,
        &AugmentButton::is_be_checked,
        this,
        &MenuBar::sig_distrib_handler
    );
}

// Метод для получения указателя на список кнопок
QList<CustomButton*>* MenuBar::getObjectsList()
{
    return this->p_items_list;
}

// Метод для получения указателя на макет
QBoxLayout* MenuBar::get_layout()
{
    return this->p_menu_layout;
}

// обработка сигнала при нажатии
void MenuBar::sig_distrib_handler(EMITS_BTN_SIGNALS _clicked_btn_sig)
{
    for
    (
        int iter_btn = 0;
        iter_btn != this->p_items_list->size();
        ++iter_btn
    )
    {   // перебор кнопок в списке
        CustomButton* tmp_obj = this->p_items_list->at(iter_btn);
        if
        (   // Для всех кнопок, кроме нажатой, снимает выделение
            tmp_obj->get_emitted_sig() != _clicked_btn_sig
        )
        {
            tmp_obj->setChecked(false);
        }
    }
    this->update();  // обновлаяем состояние виджета

    emit this->sig_transmission(_clicked_btn_sig);  // испускаем сигнал
}
