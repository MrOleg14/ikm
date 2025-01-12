// интерфейс меню
#ifndef MENUBAR_H  // защита от многократного включения заголовочного файла
#define MENUBAR_H  // предотвращение от повторного включения заголовочного файла

#include "../includes.h"
#include "CustomButton.h"

class MenuBar : public QWidget  // класс для всех виджетов
{
Q_OBJECT
private:
    QBoxLayout* p_menu_layout;  // расположения виджетов
    QList<CustomButton*>* p_items_list;  // хранит указатели на объекты CustomButton

    QSize* p_size;
    QSize* p_position;

public:
    MenuBar
    (
        QSize*,
        QSize*,
        // QPair<int, int>*,
        bool _orient_layout = true/*true -> vertical*/,  // ориентация расположения
        QWidget* _parent = 0
        // int _counter = 0
    );
    ~MenuBar();  // деструктор вызывается при удалении объекта MenuBar

    void appendObject(EMITS_BTN_SIGNALS, QString, QString);  // метод для добавления новой кнопки в меню
    void appendObject(EMITS_BTN_SIGNALS, QString);
    QList<CustomButton*>* getObjectsList();  // Метод для получения указателя на список кнопок
    QBoxLayout* get_layout();  // Метод для получения указателя на макет QBoxLayout

protected:
    // показать все кнопки
    void paintEvent(QPaintEvent*) override
    {
        QPainter painter(this);

        for
        (
            auto beg = this->p_items_list->begin();
            beg != this->p_items_list->end();
            ++beg
        )
        {
            (*beg)->show();
        }
    }

signals:
    void sig_transmission(EMITS_BTN_SIGNALS);

public slots:
    void sig_distrib_handler(EMITS_BTN_SIGNALS);  // принимает тип сигнала EMITS_BTN_SIGNALS и обрабатывает сигналы от кнопок
};


#endif // MENUBAR_H  // закрываем блок
