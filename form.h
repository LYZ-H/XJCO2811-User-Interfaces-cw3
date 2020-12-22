#ifndef FORM_H
#define FORM_H

#include <QWidget>
#include <QScrollArea>
#include "ui_form.h"
#include "video_search.h"

namespace Ui {
    class Form;
}

class Form : public QWidget {
Q_OBJECT

public:
    explicit Form(QWidget *parent = nullptr,
                  QScrollArea *videoScroller = nullptr,
                  VideoSearch *searchBox = nullptr,
                  QLabel *label = nullptr);

    ~Form() override;

public:
    void resizeEvent(QResizeEvent *event) override;

    Ui::Form *ui{};
    QScrollArea *videoScroller;
    VideoSearch *searchBox;
    QLabel *label;

};

#endif // FORM_H
