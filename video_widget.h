#ifndef VIDEO_WIDGET_H
#define VIDEO_WIDGET_H


#include <QVideoWidget>

class VideoScreen : public QVideoWidget {
    Q_OBJECT
public:
    VideoScreen() : QVideoWidget() {
   }
protected:
    void keyPressEvent(QKeyEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
    //used to make the player become full screen on doubleclick/button press
private slots:
    void setFullScr(bool value);

};
#endif // VIDEO_WIDGET_H
