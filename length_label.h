#ifndef LENGTH_LABEL_H
#define LENGTH_LABEL_H


#include <QLabel>
#include <QUrl>
#include <QStyle>
#include <QAudio>
#include <QWidget>
#include <QSlider>
#include <QMediaPlayer>

class LengthLabel : public QLabel {
Q_OBJECT
public:
    explicit LengthLabel(QWidget *parent) : QLabel(parent) {
    }

private slots:

    //slot to set the duration of the current video
    void setLength(qint64);

private:
    bool playValue{};
};

#endif // LENGTH_LABEL_H
