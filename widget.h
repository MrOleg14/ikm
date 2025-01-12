#ifndef WIDGET_H
#define WIDGET_H

// подключение заголовочных файлов
#include "includes.h"
#include "menu_bar/CustomButton.h"
#include "menu_bar/MenuBar.h"
#include "menu_bar/TopBar.h"
#include "table_view_model/DBViewer.h"

class Widget : public QWidget
{
Q_OBJECT

private:
    MenuBar* p_mBar;  // меню приложения
    TopBar* p_topBar;  // верхняя панель инструментов
    QPalette* p_backColor;  // управлениe цветами и стилями виджетов

public:
    Widget(QString, QWidget *parent = nullptr);  // конструктор для задания имени
    ~Widget();
};
#endif // WIDGET_H
