
#include "video_volume.h"

void VolumeButton::setMute(bool flipMute)
{
    muteValue = !flipMute;
}

void VolumeButton::clicked()
{

    if (!muteValue){
        setIcon(style()->standardIcon(QStyle::SP_MediaVolumeMuted));
        //as usual, QStyle is used for the button icons
        emit moveSlider(0);
    } else {
        setIcon(style()->standardIcon(QStyle::SP_MediaVolume));
        //button icon changes depending on if muted or not
        emit(moveSlider(10)); //set to this value on unmute
    }
        setMute(muteValue);
        emit mute(muteValue);
}

void VolumeButton::changeIcon(int volVal) {

    if (volVal == 0) {
        setIcon(style()->standardIcon(QStyle::SP_MediaVolumeMuted));
    } if (volVal != 0 && muteValue == false) {
        setIcon(style()->standardIcon(QStyle::SP_MediaVolume));
    }
    //allows icon to be changed even if volume is changed via slider
}

//allows volume button to change slider
void VolumeSlider::moveSlider(int volume) {
    setSliderPosition(volume);
}
