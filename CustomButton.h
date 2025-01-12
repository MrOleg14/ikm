// интерфейс
#ifndef CUSTOMBUTTON_H
#define CUSTOMBUTTON_H
// защита от повторного подключения заголовка + файлы с общими include
#include "../includes.h"

class CustomButton : public QPushButton
{
Q_OBJECT

private:
    QPixmap* ico_obj;  // хранение иконки
    EMITS_BTN_SIGNALS btn_sig;  // идентификатор иконки

protected:
    virtual void paintEvent(QPaintEvent*) override  // рисуем кнопочку
    {
        QPainter painter;

        // смещения масштаба изображения в эллипсе
        int sqr_offset = 10;
        int sqr_volume = 20;

        // кнопка прямоугольной формы
        QRect menuItem_draw_ellipse
        (
            this->rect().x(),
            this->rect().y(),
            this->rect().width(),
            this->rect().height()
        );
        // серый прямоугольник, если включено
        painter.begin(this);
        {
            if(this->isChecked())
                painter.setBrush(QBrush(Qt::black));
            else if(this->underMouse() && !this->isChecked() )
            {
                painter.setBrush(QBrush(Qt::lightGray));
            }
            else
                painter.setBrush(QBrush(Qt::white));
            painter.drawEllipse
            (
                menuItem_draw_ellipse.x(),
                menuItem_draw_ellipse.y(),
                menuItem_draw_ellipse.width(),
                menuItem_draw_ellipse.height()
            );
        }
        painter.end();
        if(this->ico_obj != nullptr)
        {
            painter.begin(this);
                painter.drawPixmap
                (
                    QRect
                    (
                        menuItem_draw_ellipse.x()+sqr_offset,
                        menuItem_draw_ellipse.y()+sqr_offset,
                        menuItem_draw_ellipse.width()-sqr_volume,
                        menuItem_draw_ellipse.height()-sqr_volume
                    ),
                    *(this->ico_obj)
                );
            painter.end();
        }
    }

public:
    CustomButton  // констурктор принимает путь к иконке
    (
        EMITS_BTN_SIGNALS,
        QString& _ico_path
        // QString& _btn_text
    );
    ~CustomButton();  // деструктор освобождает ресурсы

    // методы для получения и установки иконки
    QPixmap* get_ico_obj();
    void set_ico_obj(QPixmap*);
    EMITS_BTN_SIGNALS get_emitted_sig();

public slots:
    void checked();  // вызываться при нажатии на кнопку

signals:
    void is_be_checked(EMITS_BTN_SIGNALS);  // испускаться с передачей btn_sig
};


// наследует QPushButton, отправляет сигнал и обрабатывает слоты
class AugmentButton : public QPushButton
{
Q_OBJECT
private:
    EMITS_BTN_SIGNALS btn_sig;
    QString btn_txt;

public:
    AugmentButton(EMITS_BTN_SIGNALS, QString&);
    ~AugmentButton();

public slots:
    void checked();

signals:
    void is_be_checked(EMITS_BTN_SIGNALS);

};

#endif // CUSTOMBUTTON_H
