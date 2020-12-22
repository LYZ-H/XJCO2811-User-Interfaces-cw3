#ifndef FORM_H
#define FORM_H

#include <QWidget>
#include <QScrollArea>
#include "ui_form.h"
#include "video_search.h"

namespace Ui {
class Form;
}

class Form : public QWidget
{
    Q_OBJECT

public:
    explicit Form(QWidget *parent = nullptr,
                  QScrollArea* videoScroller = nullptr,
                  videoSearch* searchBox = nullptr);
    ~Form();

public:
    void resizeEvent(QResizeEvent *event);
    Ui::Form *ui;
    QScrollArea* videoScroller;
    videoSearch* searchBox;
};

#endif // FORM_H
