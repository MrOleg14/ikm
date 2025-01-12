// отображениe данных в виде таблицы в приложении
#ifndef DBTABLEVIEWMODEL_H
#define DBTABLEVIEWMODEL_H

#include "../includes.h"

class DBTableViewModel : public QTableView
{
Q_OBJECT
private:
    QMap<EMITS_BTN_SIGNALS, QString>* p_link_sig_names;  // хранениe имен сигналов
    QString* current_table;  // хранениe информации о текущей таблице

public:
    DBTableViewModel  // конструктор для инициализации объекта
    (
        QMap<EMITS_BTN_SIGNALS, QString>*,
        QWidget* _parent = nullptr
    );

    ~DBTableViewModel();  // освобождение ресурсов

    void set_model(EMITS_BTN_SIGNALS);
    void apeendConnect(EMITS_BTN_SIGNALS, QString);  // подключениe сигналов к определённым строкам
    void to_resize();  // изменениe размера таблицы
    void exec_filter(const QString&);
    void remove_row(const QString&);  // удалениe строки из таблицы на основе переданного значения
    void add_new_row();  // добавлениe новой строки в таблицу
};


#endif // DBTABLEVIEWMODEL_H
