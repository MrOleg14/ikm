// виджет для отображения данные из бд
#include "widget.h"

Widget::Widget(QString _db_source, QWidget *parent)  // Путь к источнику данных
    : QWidget(parent)
{
    // настройка цветовой палитры для фона главного окна
    this->setAutoFillBackground(true);

    this->p_backColor = new QPalette;
    this->p_backColor->setColor(this->backgroundRole(), Qt::white);
    this->setPalette(*p_backColor);

    // главное окно настройки
    this->setBaseSize(500, 1000);

    // область кнопок настройки
    this->p_mBar = new MenuBar
    (
        new QSize(80, 500),  // Размер области меню
        new QSize(10, 20),  // Размер элементов меню
        true,
        this
    );
    {   // добавляем кнопки в меню с изображениями и сигналами
        this->p_mBar->appendObject(EMITS_BTN_SIGNALS::SIG0, ":/ico/countries.png", "");
        this->p_mBar->appendObject(EMITS_BTN_SIGNALS::SIG1, ":/ico/shop.png", "");
        this->p_mBar->appendObject(EMITS_BTN_SIGNALS::SIG2, ":/ico/month.png", "");
        this->p_mBar->appendObject(EMITS_BTN_SIGNALS::SIG3, ":/ico/product.png", "");
        this->p_mBar->appendObject(EMITS_BTN_SIGNALS::SIG4, ":/ico/production.png", "");
    }
        /* buttons signals was connected to menu signal hendler */
    this->p_mBar->show();

    // настройка верхнего меню
    this->p_topBar = new TopBar
    (
        new QSize(  // Позиция и ширина области верхней панели
            this->p_mBar->size().width(),
            this->p_mBar->pos().y()
            ),
        new QSize(  // Размер области верхней панели
            this->width()-this->p_mBar->size().width(),
            60
            ),
        this
    );
    this->p_topBar->show();  // отображение верхней панели

    // настройка области просмотра БД
    // определить запросы для просмотра мода
    QMap<QString, QString>* p_queries = nullptr;
    // определить ссылки signal<->table для обмена таблицами
    QMap<EMITS_BTN_SIGNALS, QString>* p_links_sig_table = new QMap<EMITS_BTN_SIGNALS, QString>;
    {   // связь с таблицами бд
        p_links_sig_table->insert(EMITS_BTN_SIGNALS::SIG0, "country");
        p_links_sig_table->insert(EMITS_BTN_SIGNALS::SIG1, "shop");
        p_links_sig_table->insert(EMITS_BTN_SIGNALS::SIG2, "month");
        p_links_sig_table->insert(EMITS_BTN_SIGNALS::SIG3, "product");
        p_links_sig_table->insert(EMITS_BTN_SIGNALS::SIG4, "production");
    }
    DBViewer* p_db_viewer = new DBViewer  // отображение данных в виде таблицы
    (
        _db_source,  // путь к файлу базы данных
        p_queries,
        p_links_sig_table,
        new QSize  // области для просмотра
        (
            1500,
            900
        ),
        new QSize  // Позиция области просмотра
        (
            this->p_mBar->width(),
            this->p_topBar->height()
        ), // not optimazed
        QBoxLayout::Direction::TopToBottom,
        this
    );

    connect // выбрать таблицу
    (
        this->p_mBar,
        &MenuBar::sig_transmission,
        p_db_viewer,
        &DBViewer::table_swapper
    );

    connect // фильтр
    (
        this->p_topBar,
        &TopBar::sig_filter_data_transmitter,
        p_db_viewer,
        &DBViewer::exec_filter
    );

    connect // фильтр для удаления строки
    (
        this->p_topBar,
        &TopBar::sig_delete_rownum_transmitter,
        p_db_viewer,
        &DBViewer::remove_row
    );

    connect  // добавление новой строки
    (
        this->p_topBar,
        &TopBar::sig_add_new_row,
        p_db_viewer,
        &DBViewer::add_new_row
    );

    p_db_viewer->show();  // просмотр бд
}

Widget::~Widget()
{
}
