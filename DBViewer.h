#ifndef DBVIEWER_H
#define DBVIEWER_H

#include "../includes.h"
#include "DBTableViewModel.h"

class DBViewer : public QWidget  // виджет для граф интерфейса
{
    Q_OBJECT
private:
    QBoxLayout* p_layout;  // управлениe компоновкой дочерних виджетов
    DBTableViewModel* p_models_views;  // отображение данных в виде таблицы
    QMap<QString, QString>* p_view_mod_queries;  // управлениe запросами к базе данных

    // TABLE_VIEW_MOD view_mod;
    EMITS_BTN_SIGNALS view_mod;

    QSize* p_size;
    QSize* p_position;

public:
    DBViewer
    (
        QString&, // DB ресурс
        QMap<QString, QString>*, // таблица<->ссылки запроса
        QMap<EMITS_BTN_SIGNALS, QString>*,  // сигналы
        QSize*,
        QSize*,
        QBoxLayout::Direction,  // направление компоновки
        QWidget* _parent = 0  // родительский виджет
    );
    ~DBViewer();

public:
    void set_view_mod(EMITS_BTN_SIGNALS);  // установкa режима отображения на основе переданного сигнала
    void clean_layout();  // очистка компоновки виджета

public slots:
    void table_swapper(EMITS_BTN_SIGNALS);  // сменa таблицы
    void view_mod_swapper(EMITS_BTN_SIGNALS);  // режима отображения

    void exec_filter(const QString&);  // выполнениe фильтрации данных в таблицe
    void add_new_row();  // добавлениe новой строки в таблицу
    void remove_row(const QString&);  // удалениe строки
};

#endif // DBVIEWER_H
