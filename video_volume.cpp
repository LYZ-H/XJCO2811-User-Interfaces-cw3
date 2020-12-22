
#include "video_volume.h"

void VolumeButton::setMute(bool flipMute) {
    muteValue = !flipMute;
}

void VolumeButton::clicked() {

    if (!muteValue) {
        setIcon(QIcon(":/muteButton.svg"));
        //as usual, QStyle is used for the button icons
        emit moveSlider(0);
    } else {
        setIcon(QIcon(":/volume.svg"));
        //button icon changes depending on if muted or not
        emit(moveSlider(1600)); //set to this value on unmute
    }
    setMute(muteValue);
    emit mute(muteValue);
}

void VolumeButton::changeIcon(int volVal) {

    if (volVal == 0) {
        setIcon(QIcon(":/muteButton.svg"));
    }
    if (volVal != 0 && !muteValue) {
        setIcon(QIcon(":/volume.svg"));
    }
    //allows icon to be changed even if volume is changed via slider
}

//allows volume button to change slider
void VolumeSlider::moveSlider(qint64 volume) {
    setSliderPosition(volume);
}
