// пользовательские кнопки
#include "../includes.h"
#include "CustomButton.h"

CustomButton::CustomButton
(
    EMITS_BTN_SIGNALS _btn_sig,  // сигнал при нажатии
    QString& _ico_path  // путь к иконке
) :
    QPushButton(), btn_sig(_btn_sig)
{
    // установить изображение
    if(_ico_path != "")  // передан ли путь к иконке
    {
        this->ico_obj = new QPixmap(_ico_path);  // создаем новфй объект
        this->setIcon(*(this->ico_obj));  // устанавливаем иконку для кнопки
        this->setIconSize(QSize(50, 50));  // устанавливаем размер иконки
    }
    else
        this->ico_obj = nullptr;

    this->setMouseTracking(true); // для выделения серого цвета
    this->setCheckable(true); // для рисования черного выделения
    this->setCursor(Qt::PointingHandCursor);  // курсор в виде руки

    connect  // устанавливает связь между сигналом clicked кнопки и слотом checked
    (
        this,
        &QPushButton::clicked,
        this,
        &CustomButton::checked/*emit EMITS_BTN_SIGNALS::<signal>*/
    );
}

CustomButton::~CustomButton()  // освобождаем память, выделенную для иконки
{
    delete this->ico_obj;
}

inline QPixmap* CustomButton::get_ico_obj()  // метод для получения указателя
{
    return this->ico_obj;
}

void CustomButton::set_ico_obj(QPixmap* _px_map)  // метод для установки нового объекта
{
    delete this->ico_obj;  // удаление памяти от старой иконки
    this->ico_obj = _px_map;
}
// метод для получения значения сигнала от кнопки
EMITS_BTN_SIGNALS CustomButton::get_emitted_sig()
{
    return this->btn_sig;
}

void CustomButton::checked()
{
    emit this->is_be_checked(this->btn_sig);
}

AugmentButton::AugmentButton
(
    EMITS_BTN_SIGNALS _btn_sig,  // сигнал кнопки
    QString& _btn_txt  // текст на кнопке
) : btn_sig(_btn_sig),
    btn_txt(_btn_txt)
{
    connect  // связь между сигналом и слотом
    (
        this,
        &QPushButton::clicked,
        this,
        &AugmentButton::checked
    );
}

AugmentButton::~AugmentButton() {}

void AugmentButton::checked()  // слот, вызываемый при нажатии на кнопку
{
    emit this->is_be_checked(this->btn_sig);
