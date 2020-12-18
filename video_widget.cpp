
#include <QMouseEvent>
#include <QKeyEvent>

#include "video_widget.h"

void VideoScreen::mouseDoubleClickEvent(QMouseEvent *event) {
    setFullScreen(!isFullScreen());
    event->accept();
}
//on double click or buttonpress, the video will go into fullscreen
void VideoScreen::keyPressEvent(QKeyEvent *event) {
    setFullScreen(!isFullScreen());
    event->accept();
}

void VideoScreen::setFullScr(bool value) {
    setFullScreen(!value);
}
