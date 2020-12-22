
#include <QFileInfo>
#include <QtDebug>
#include <QDateTime>
#include <QGraphicsDropShadowEffect>
#include "the_button.h"

void TheButton::init(TheButtonInfo *i) {
    setIcon(*(i->icon));
    QString file1 = i->url->toString();
    QString file = file1.right(file1.length() - 8);
    QFileInfo file_info(file);
    QDateTime created = file_info.birthTime();
    setText("  Name:" + file_info.fileName() + "  \n" + "  Time:"
    + created.toString("yyyy-MM-dd hh:mm:ss "));
    info = i;
    auto *shadow = new QGraphicsDropShadowEffect(this);
    shadow->setOffset(0, 0);
    shadow->setColor(QColor("#444444"));
    shadow->setBlurRadius(10);
    setGraphicsEffect(shadow);
}


void TheButton::clicked() {
    emit jumpTo(info);
}

void TheButton::searchBtn(const QString &hey) {

    //get the file path as a string
    QString path = info->url->toString();
    QFileInfo file(path);
    QString name = file.baseName();

    if (hey == "") {
        setVisible(true);
    } else {
        if (hey != name) {
            setHidden(true);
        } else {
            setVisible(true);
        }
    }
}
