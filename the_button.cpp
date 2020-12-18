
#include <QFileInfo>
#include <QtDebug>

#include "the_button.h"

void TheButton::init(TheButtonInfo* i) {
    setIcon(*(i->icon));
    info =  i;
}


void TheButton::clicked() {
    emit jumpTo(info);
}

void TheButton::searchBtn(QString hey) {

    //get the file path as a string
    QString path = info->url->toString();
    QFileInfo file(path);
    QString name = file.baseName();

    if (hey == "") {
        setVisible(true);
    } else {
        if(hey != name) {
            setHidden(true);
        } else {
            setVisible(true);
        }
    }
}
