
#include "video_slider.h"

void VideoSlider::SetValue(qint64 position) {
    setValue(position);
}
void VideoSlider::SetRange(qint64 position) {
    //set range is used to allow the slider range to change when the video changes
    setRange(0,position);
}
