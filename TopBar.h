// интерфейс
#ifndef TOPBAR_H
#define TOPBAR_H

#include "../includes.h"


class InputArea : public QLabel  // для отображения текста и изображений, основа ввода
{
Q_OBJECT
private:
    QLineEdit* p_ledit;  // указатель для ввода

public:
    InputArea(QString);  // конструктор, принимающий в качестве параметра строку
    ~InputArea();
    QLineEdit* get_edit_area();  // Метод для получения указателя на объект QLineEdit

public slots:
    void slot_enter_pressed();  // Слот для обработки нажатия клавиши Enter в поле ввода

signals:
    void sig_get_text(const QString&);  // сигнал, который испускается при вводе текста, передавая текст в виде строки
};


class TopBar : public QWidget
{
Q_OBJECT
private:
    QHBoxLayout* p_layout;  // для расположения виджетов горизонтально

    QLabel* p_curr_tname;  // отображения текущего имени таблицы
    InputArea* p_filter;  // ввод текста для фильтрации данных
    InputArea* p_delete_line;  // ввод номера строки для удаления
    QPushButton* p_add_new_row;  // добавлениe новой строки

    QSize* pos;
    QSize* size;

public:
    TopBar
    (
        QSize* _pos,
        QSize* _size,
        QWidget* _parent = nullptr
    );
    ~TopBar();

public slots:
    void slot_set_tname(QString&);  // установкa нового имени таблицы
    void slot_filter_transmitter(const QString&);  // прием отфильтрованного текста
    void slot_delete_rownum_transmitter(const QString&);  // прием номера строки для удаления
    void slot_add_new_row();  // обработкa нажатия на кнопку добавления новой строки

signals:
    void sig_change_tname(const QString&);  // передает новое имя
    void sig_filter_data_transmitter(const QString&);  // фильтруемый текст в виде строки
    void sig_delete_rownum_transmitter(const QString&);  // номер строки в виде строки
    void sig_add_new_row();  // при нажатии на кнопку добавления новой строки
};


#endif // TOPBAR_H
