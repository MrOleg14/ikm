#include "DBTableViewModel.h"


DBTableViewModel::DBTableViewModel
(
    QMap<EMITS_BTN_SIGNALS, QString>* _link_sig_names,  // динамически выбираем таблицу в зависимости от сигнала
    QWidget* _parent
) : QTableView(_parent), p_link_sig_names(_link_sig_names)  // инициализируем виджет таблицы
{
    this->setPalette(QPalette(Qt::white));  // устанавливаем белый цвет
    this->current_table = new QString("");
}

DBTableViewModel::~DBTableViewModel()
{
    delete this->p_link_sig_names;
}

void DBTableViewModel::set_model
(
    EMITS_BTN_SIGNALS _emitted_sig  // установка модели данных для отображения в таблице
)
{   // возврат итератора на первый элемент
    *(this->current_table) = this->p_link_sig_names->lowerBound(_emitted_sig).value();
    QSqlTableModel* tmp_rel_mdl = new QSqlTableModel;  // временная модель для работы с данными
    tmp_rel_mdl->setTable
    (
        *(this->current_table)
    );
    tmp_rel_mdl->select(); // загрузка данных

    // установить текущую модель для просмотра
    this->setModel(tmp_rel_mdl);
}

// Применяет фильтр к данным в таблице
void DBTableViewModel::exec_filter(const QString& _filter)
{
    QSqlTableModel* tmp_rel_mdl = new QSqlTableModel;
    tmp_rel_mdl->setTable
        (
            *(this->current_table)
        );
    tmp_rel_mdl->setFilter(_filter);  //  отобраем строки по заданному критерию
    tmp_rel_mdl->select(); // загрузка данных

    // установить текущую модель для просмотра
    this->setModel(tmp_rel_mdl);
}

// Добавляет новую строку в текущую таблицу
void DBTableViewModel::add_new_row()
{
    QSqlTableModel* tmp_rel_mdl = new QSqlTableModel;
    tmp_rel_mdl->setTable
        (
            *(this->current_table)
            );

    QSqlRecord rec = tmp_rel_mdl->record(0);

    int index_row = 0;
    tmp_rel_mdl->insertRows(index_row, 1);

    for(int col_ind = 0; col_ind < tmp_rel_mdl->columnCount(); ++col_ind)
    {
        tmp_rel_mdl->setData(tmp_rel_mdl->index(index_row, col_ind), "0");
    }

    if(!tmp_rel_mdl->submitAll())
    {
        qDebug("создание новой ошибки строки");
    }
    this->exec_filter("");
}

// Удаляет строки из таблицы на основе заданного фильтра
void DBTableViewModel::remove_row(const QString& _filter)
{
    QSqlTableModel* tmp_rel_mdl = new QSqlTableModel;
    tmp_rel_mdl->setTable
        (
            *(this->current_table)
            );
    tmp_rel_mdl->setFilter(_filter);
    tmp_rel_mdl->select();  // Загружаются данные
    tmp_rel_mdl->removeRows(0, tmp_rel_mdl->rowCount());  // удаление всех строк
    tmp_rel_mdl->submitAll();  // Сохранение изменений

    delete tmp_rel_mdl;
    tmp_rel_mdl = new QSqlTableModel;
    tmp_rel_mdl->setTable
        (
            *(this->current_table)
            );
    tmp_rel_mdl->select();
    this->setModel(tmp_rel_mdl);
}

// Автоматически изменяет размер колонок в соответствии с их содержимым
void DBTableViewModel::to_resize()
{
    if(this->model() != NULL)
    {
        int colCount = this->model()->columnCount();  // Получаем количество колонок
        for(int colNum = 0; colNum < colCount; ++colNum)
        {
            this->resizeColumnToContents(colNum);  // изменяем ширину колонки
        }
    }
}
