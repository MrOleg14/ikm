// библиотеки и управление сигналами
#ifndef INCLUDES_H
#define INCLUDES_H

// библиотеки Qt для граф интерфейса и работа с базами данных
#include <QPair>

#include <QtCore>
#include <QObject>
#include <QApplication>

#include <QWidget>
#include <QPixmap>
#include <QVBoxLayout>
#include <QPushButton>
#include <QPainter>

#include <QLabel>
#include <QTextEdit>
#include <QLineEdit>

#include <QtSql>
#include <QTableView>

enum class EMITS_BTN_SIGNALS
{
    // Левое вертикальное меню
    SIG0,
    SIG1,
    SIG2,
    SIG3,
    SIG4,
    // Верхнее горизонтальное меню (просмотр модов)
    EDIT,
    ONLY_VIEW,
};


#endif // INCLUDES_H
