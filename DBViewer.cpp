// отображение данных из SQLite базы
#include "../includes.h"
#include "DBViewer.h"

DBViewer::DBViewer
(
    QString& _db_soruce, // DB ресурс
    QMap<QString, QString>* _table_query_links, // таблица<->ссылки запроса
    QMap<EMITS_BTN_SIGNALS, QString>* _link_sig_table,  // словарь, связывающий имена таблиц с SQL-запросами
    QSize* _size,
    QSize* _position,
    QBoxLayout::Direction _layout_format,  // направление макета
    QWidget* _parent
) :
    QWidget(_parent),
    p_size(_size),
    p_position(_position)
{
    // делаем макет
    this->p_layout = new QBoxLayout(_layout_format);
    this->setLayout(this->p_layout);
    this->setGeometry
    (   // задаем параметры
        _position->width(),
        _position->height(),
        _size->width(),
        _size->height()
    );
    // Создает объект QSqlDatabase для работы с базой данных SQLite
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(_db_soruce);  // установка имени бд
    if(!db.open())
    {
        qDebug("Ошибка с открытием базы данных");
    }

    // добавление представление моделей в макет
    this->p_models_views = new DBTableViewModel(_link_sig_table, this);
    this->p_models_views->setGeometry
    (
        _position->width(),
        _position->height(),
        _size->width(),
        _size->height()
    );
    this->p_layout->addWidget(this->p_models_views);  // добавляем в макет
    /*
        TEST SECTION
    */
}

DBViewer::~DBViewer()
{
    delete this->p_position;
    delete this->p_size;
}

// Метод для установки режима отображения (view_mod) таблиц
void DBViewer::set_view_mod(EMITS_BTN_SIGNALS _view_mod)
{
    this->view_mod = _view_mod;
}

// Метод для переключения отображаемой таблицы, обновляем размер
void DBViewer::table_swapper(EMITS_BTN_SIGNALS _emitted_sig)
{
    this->p_models_views->set_model(_emitted_sig);
    this->p_models_views->to_resize();
}

// Метод для переключения режима отображения
void DBViewer::view_mod_swapper(EMITS_BTN_SIGNALS _view_mod)
{
    switch (_view_mod)
    {
    case EMITS_BTN_SIGNALS::EDIT:
            this->p_models_views->to_resize();
            this->p_models_views->show();
        break;
    case EMITS_BTN_SIGNALS::ONLY_VIEW:
            this->p_models_views->hide();
        break;
    default:  // добавляет текстовое сообщение
        this->p_layout->addWidget
        (
            new QLabel(
            "THE DISPLAY OPTION IS NOT SELECTED\nHint: buttons 'View' and 'Edit' at the top")
        );
        break;
    }
}

// Метод для применения фильтра к таблице
void DBViewer::exec_filter(const QString& _filter)
{
    this->p_models_views->exec_filter(_filter);
    this->p_models_views->to_resize();
}

// Метод для добавления новой строки в таблицу
void DBViewer::add_new_row()
{
    this->p_models_views->add_new_row();
    this->p_models_views->to_resize();
}

// Метод для удаления строки из таблицы
void DBViewer::remove_row(const QString& _filter)
{
    this->p_models_views->remove_row(_filter);
    this->p_models_views->to_resize();
}
