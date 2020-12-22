/*
 *
 *    ______
 *   /_  __/___  ____ ___  ___  ____
 *    / / / __ \/ __ `__ \/ _ \/ __ \
 *   / / / /_/ / / / / / /  __/ /_/ /
 *  /_/  \____/_/ /_/ /_/\___/\____/
 *              video for sports enthusiasts...
 *
 *  2811 cw3 : twak
 */

#include <iostream>
#include <QApplication>
#include <QtMultimediaWidgets/QVideoWidget>
#include <QMediaPlaylist>
#include <string>
#include <vector>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QHBoxLayout>
#include <QtCore/QFileInfo>
#include <QImageReader>
#include <QMessageBox>
#include <QtCore/QDir>
#include <QtCore/QDirIterator>
#include "the_player.h"
#include <QScrollArea>
#include <QLineEdit>
#include <QComboBox>
#include "the_layout.h"
#include "video_slider.h"
#include "skip_buttons.h"
#include "the_pause.h"
#include "length_label.h"
#include "video_widget.h"
#include "next_video.h"
#include "button_widget.h"
#include "form.h"

using namespace std;

vector<TheButtonInfo> thumbMatch(const QString &f, vector<TheButtonInfo> out, int index) {
    QString thumb = f.left(f.length() - 4) + ".png";
    if (QFile(thumb).exists()) { // if a png thumbnail exists
        auto *imageReader = new QImageReader(thumb);
        QImage sprite = imageReader->read(); // read the thumbnail
        if (!sprite.isNull()) {
            // voodoo to create an icon for the button
            auto *ico = new QIcon(QPixmap::fromImage(sprite));
            // convert the file location to a generic url
            QUrl *url = new QUrl(QUrl::fromLocalFile(f));
            // add to the output list
            out.emplace_back(url, ico, index);
        } else {
            thumb = ":/def.png";
            if (QFile(thumb).exists()) { // if a png thumbnail exists
                imageReader = new QImageReader(thumb);
                sprite = imageReader->read(); // read the thumbnail
                if (!sprite.isNull()) {
                    // voodoo to create an icon for the button
                    auto *ico = new QIcon(QPixmap::fromImage(sprite));
                    // convert the file location to a generic url
                    QUrl *url = new QUrl(QUrl::fromLocalFile(f));
                    // add to the output list
                    out.emplace_back(url, ico, index);
                }
            }
        }
    } else {
        thumb = ":/def.png";
        if (QFile(thumb).exists()) { // if a png thumbnail exists
            auto *imageReader = new QImageReader(thumb);
            QImage sprite = imageReader->read(); // read the thumbnail
            if (!sprite.isNull()) {
                // voodoo to create an icon for the button
                auto *ico = new QIcon(QPixmap::fromImage(sprite));
                // convert the file location to a generic url
                QUrl *url = new QUrl(QUrl::fromLocalFile(f));
                // add to the output list
                out.emplace_back(url, ico, index);
            }
        }
    }
    return out;
}

// read in videos and thumbnails to this directory
vector<TheButtonInfo> getInfoIn(const string &loc) {

    vector<TheButtonInfo> out = vector<TheButtonInfo>();
    QDir dir(QString::fromStdString(loc));
    QDirIterator it(dir);
    int index = 0;
    while (it.hasNext()) { // for all files

        QString f = it.next();

        if (f.contains("."))

        #if defined(_WIN32)
            if (f.contains(".wmv")) { // windows
            #else
                if (f.contains(".mp4") || f.contains("MOV"))  { // mac/linux
            #endif
                out = thumbMatch(f, out, index);
                index++;
            }
        }
        return out;
}

VideoSlider* init_slider(ThePlayer *player, ButtonWidget *buttonWidget) {
    auto *videoSlider = new VideoSlider(buttonWidget);

    ThePlayer::connect(player, SIGNAL(durationChanged(qint64)),
                       videoSlider, SLOT(SetRange(qint64)));
    ThePlayer::connect(player, SIGNAL(positionChanged(qint64)),
                       videoSlider, SLOT(SetValue(qint64)));
    VideoSlider::connect(videoSlider, SIGNAL(sliderMoved(int)),
                         player, SLOT(SetPosition(int)));
    //player and video slider are mutually connected

    return videoSlider;
}

VolumeSlider* init_volum(ThePlayer *player, ButtonWidget *buttonWidget) {
    auto *muteButton = buttonWidget->muteButton;
    auto *volumeSlider = new VolumeSlider(buttonWidget);

    VolumeSlider::connect(volumeSlider, SIGNAL(valueChanged(int)),
                          player, SLOT(setVolume(int)));
    VolumeSlider::connect(volumeSlider, SIGNAL(valueChanged(int)),
                          muteButton, SLOT(changeIcon(int)));
    VolumeSlider::connect(volumeSlider, SIGNAL(sliderMoved(int)),
                          player, SLOT(setVolume(int)));
    //volume slider changing is connected to the player and the mute button
    VolumeButton::connect(muteButton, SIGNAL(mute(bool)), player, SLOT(setMuted(bool)));
    //mute button is connected to the player and slider

    return volumeSlider;
}

QComboBox* init_sortby(ButtonWidget *buttonWidget) {
    //sort by combo box
    auto *sortby = new QComboBox(buttonWidget);
    sortby->addItem("A-Z");
    sortby->addItem("Date");
    sortby->setWhatsThis("sortby");

    return sortby;
}

QComboBox* init_rate(ThePlayer *player, ButtonWidget *buttonWidget) {
    auto *playrate = new QComboBox(buttonWidget);
    // for selecting playrate

    playrate->addItem("0.5x speed", QVariant(0.5));
    playrate->addItem("1x speed", QVariant(1));
    playrate->addItem("2x speed", QVariant(2));
    playrate->addItem("4x speed", QVariant(4));
    playrate->setCurrentIndex(1);
    playrate->setWhatsThis("playrate");

    //connected combobox with playrate settting slot
    QComboBox::connect(playrate, SIGNAL(activated(int)), player, SLOT(doPlayRate(int)));

    return playrate;
}

LengthLabel* init_length(ThePlayer *player, ButtonWidget *buttonWidget) {
    auto *length_label = new LengthLabel(buttonWidget);
    length_label->setWhatsThis("length_label");

    ThePlayer::connect(player, SIGNAL(positionChanged(qint64)),
                       length_label, SLOT(setLength(qint64)));
    //as video changes, length labels will change

    return length_label;
}

LengthLabel* init_duration(ThePlayer *player, ButtonWidget *buttonWidget) {
    auto *duration_label = new LengthLabel(buttonWidget);
    duration_label->setWhatsThis("duration_label");

    ThePlayer::connect(player, SIGNAL(durationChanged(qint64)),
                       duration_label, SLOT (setLength(qint64)));

    return duration_label;
}

void init_button(ThePlayer *player, ButtonWidget *buttonWidget, VideoScreen* videoWidget) {
    auto *forwardSkipBtn = buttonWidget->forwardSkipBtn;
    auto *backwardSkipBtn = buttonWidget->backwardSkipBtn;
    auto *playBtn = buttonWidget->playBtn;

    ForwardButton::connect(forwardSkipBtn, SIGNAL(clicked(bool)), player, SLOT(skipBack(bool)));
    BackwardButton::connect(backwardSkipBtn, SIGNAL(clicked(bool)),
                            player, SLOT(skipForward(bool)));
    //skip buttons connected to the player

    PlayButton::connect(playBtn, SIGNAL(clicked(bool)), player, SLOT(click()));
    ThePlayer::connect(player, SIGNAL(stateChanged(QMediaPlayer::State)),
                       playBtn, SLOT(setState(QMediaPlayer::State)));

    auto *nextBtn = buttonWidget->nextBtn;
    auto *backBtn = buttonWidget->backBtn;

    NextButton::connect(nextBtn, SIGNAL(clicked()), player, SLOT(nextVideo()));
    PrevButton::connect(backBtn, SIGNAL(clicked()), player, SLOT(prevVideo()));
    //this buttons connected to the player so it goes to next button while clicked

    auto *fullScreen = buttonWidget->fullScreen;
    buttonWidget->muteButton->click();

    FullScreenButton::connect(fullScreen, SIGNAL(clicked(bool)),
                              videoWidget, SLOT(setFullScr(bool)));
    //button connected to the video, to set it to fullscreen

}

void init_frame(ButtonWidget *buttonWidget, Form* f) {
        f->ui->controlLayout->addWidget(buttonWidget->forwardSkipBtn);
        f->ui->controlLayout->addWidget(buttonWidget->backBtn);
        f->ui->controlLayout->addWidget(buttonWidget->playBtn);
        f->ui->controlLayout->addWidget(buttonWidget->nextBtn);
        f->ui->controlLayout->addWidget(buttonWidget->backwardSkipBtn);
        f->ui->volumeLayout->addWidget(buttonWidget->muteButton);
        f->ui->fullLayout->addWidget(buttonWidget->fullScreen);

}

void init_window(ThePlayer *player,
                 ButtonWidget *buttonWidget,
                 VideoScreen *videoWidget,
                 Form* f) {
    VideoSlider *videoSlider = init_slider(player, buttonWidget);
    VolumeSlider *volumeSlider = init_volum(player, buttonWidget);
    auto *length_label = init_length(player, buttonWidget);
    auto *duration_label = init_duration(player, buttonWidget);
//    QComboBox *playrate = init_rate(player, buttonWidget);
//    QComboBox *sortby = init_sortby(buttonWidget);

    init_frame(buttonWidget, f);
    f->ui->screenLayout->addWidget(videoWidget);
    f->ui->sliderLayout->addWidget(videoSlider);
    f->ui->timeLayout->addWidget(length_label);
    f->ui->timeLayout->addWidget(duration_label);
    f->ui->volumeLayout->addWidget(volumeSlider);

}

vector<TheButtonInfo> init_video(int argc, char *argv[]) {
    vector<TheButtonInfo> videos;
    if (argc == 2)
        videos = getInfoIn(string(argv[1]));
    if (videos.empty()) {
        exit(-1);
    }
    return videos;
}

int main(int argc, char *argv[]) {
    qDebug() << "Qt version: " << QT_VERSION_STR << Qt::endl;
    QApplication app(argc, argv);
    vector<TheButtonInfo> videos = init_video(argc, argv);

    auto *videoWidget = new VideoScreen();
    videoWidget->setFullScreen(false); //starts off not in fullscreen
    auto *player = new ThePlayer;
    player->setVideoOutput(videoWidget);
    auto *buttonWidget = new ButtonWidget();
    vector<TheButton *> buttons;// the buttons are arranged horizontally
    auto *layout = new QGridLayout();
    buttonWidget->setLayout(layout);
    init_button(player, buttonWidget, videoWidget);
    auto *videoScroller = new QScrollArea();
    auto *inner = new QFrame(videoScroller);
    auto *searchBoxParent = new QLineEdit();
    auto *searchBox = new videoSearch(videos, searchBoxParent);
    videoSearch::connect(searchBox,SIGNAL(textChanged(QString)),searchBox,SLOT(search(QString)));
    for (int i = 0; i < static_cast<int>(videos.size()); i++) {
        auto *button = new TheButton(buttonWidget);
        auto *buttonLabel = new label();
        TheButton::connect(button, SIGNAL(jumpTo(TheButtonInfo *)),
                           player, SLOT (jumpTo(TheButtonInfo *)));
        videoSearch::connect(searchBox, SIGNAL(textChanged(QString)),
                             button, SLOT(searchBtn(QString)));
        videoSearch::connect(searchBox, SIGNAL(textChanged(QString)),
                             buttonLabel, SLOT(searchlabel(QString)));
        buttons.push_back(button);
        QString Qstr = videos.at(i).url->toString();
        string label = Qstr.toStdString();
        size_t found = label.find_last_of('/');
        label = label.substr(found + 1);
        QString qstr = QString::fromStdString(label);
        buttonLabel->setText(qstr);
        layout->addWidget(button);
        layout->addWidget(buttonLabel);
        button->init(&videos.at(i));
    }
    inner->setLayout(layout);
    videoScroller->setWidget(inner);
    videoScroller->setWidgetResizable(true);
    player->setContent(&buttons, &videos);

    Form f(nullptr, videoScroller, searchBox);

    qDebug() << "Qt version: " << f.size().width() << Qt::endl;
    init_window(player, buttonWidget, videoWidget, &f);

    f.show();

    return QApplication::exec();
}
