#include "includes.h"
#include "widget.h"
#include <QtSql>  // модуль для работы с бд
#include <QFileInfo>  // работа с инфой о файлах

int main(int argc, char *argv[])  // управляет основным циклом событий приложения
{
    QApplication app_master(argc, argv);

    Widget* mainwgd = new Widget("C:/Users/Пользователь/Desktop/уеба/2 курс/ЯП с++/PROJECT_K/PROJECT_K/build/Desktop_Qt_6_8_1_MinGW_64_bit-Debug/test1.db");
    mainwgd->show();  // show() делает виджет видимым на экране

    return app_master.exec();  // Запускается основной цикл событий приложения
}
