#ifndef THE_LAYOUT_H
#define THE_LAYOUT_H


#include <QtGui>
#include <QList>
#include <QLayout>
#include <QScrollArea>
#include <QVideoWidget>
#include <QSlider>
#include <QComboBox>

#include "full_screen.h"
#include "video_volume.h"
#include "video_search.h"

class ResponsiveLayout : public QLayout {
public:
    ResponsiveLayout(): QLayout() {}
    ~ResponsiveLayout();

    // standard functions for a QLayout
    void setGeometry(const QRect &rect);
    void landscapeMode(QFrame *frame, QScrollArea *qw, QVideoWidget *videoWidget,
                       QSlider *videoSlider, VolumeSlider *volumeSlider,
                       FullScreenButton *fullScreen, videoSearch *searchBox,
                       QComboBox *combo, const QRect &r);
    void portraitMode(QFrame *frame, QScrollArea *qw, QVideoWidget *videoWidget,
                       QSlider *videoSlider, VolumeSlider *volumeSlider,
                       FullScreenButton *fullScreen, videoSearch *searchBox,
                       QComboBox *combo, const QRect &r);
    void addItem(QLayoutItem *item);
    QSize sizeHint() const;
    QSize minimumSize() const;
    int count() const;
    QLayoutItem *itemAt(int) const;
    QLayoutItem *takeAt(int);
    void setScrollArea(QScrollArea *sArea);

private:
    QList<QLayoutItem*> list_;
    QScrollArea *scrollAreaPart{};
};

#endif // THE_LAYOUT_H
