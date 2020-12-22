#ifndef BUTTON_WIDGET_H
#define BUTTON_WIDGET_H

#include <QWidget>
#include "skip_buttons.h"
#include <QEvent>
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>
#include "skip_buttons.h"
#include "video_volume.h"
#include "the_pause.h"
#include "next_video.h"
#include "full_screen.h"

class ButtonWidget : public QWidget {
Q_OBJECT
public:
    ButtonWidget() : QWidget() {}

public:
    VolumeButton *muteButton = new VolumeButton(this);
    ForwardButton *forwardSkipBtn = new ForwardButton(this);
    BackwardButton *backwardSkipBtn = new BackwardButton(this);
    PlayButton *playBtn = new PlayButton(this);
    NextButton *nextBtn = new NextButton(this);
    PrevButton *backBtn = new PrevButton(this);
    FullScreenButton *fullScreen = new FullScreenButton(this);

};

#endif // BUTTON_WIDGET_H
