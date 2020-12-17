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
#include <QScrollArea>
#include <QLineEdit>
#include <QComboBox>

#include "the_player.h"
#include "the_layout.h"
#include "video_slider.h"
#include "the_pause.h"
#include "length_label.h"
#include "video_widget.h"
#include "next_video.h"

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
            thumb = f.left(f.length() - 5) + "def.png";
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
        thumb = f.left(f.length() - 5) + "def.png";
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


int main(int argc, char *argv[]) {

    // let's just check that Qt is operational first
    qDebug() << "Qt version: " << QT_VERSION_STR << endl;

    // create the Qt Application
    QApplication app(argc, argv);

    // collect all the videos in the folder
    vector<TheButtonInfo> videos;

    if (argc == 2)
        videos = getInfoIn(string(argv[1]));

    if (videos.empty()) {
        exit(-1);
    }

    // the widget that will show the video
    auto *videoWidget = new VideoScreen();

    // the QMediaPlayer which controls the playback
    auto *player = new ThePlayer;
    player->setVideoOutput(videoWidget);

    // a row of buttons
    auto *buttonWidget = new QWidget();
    // a list of the buttons
    vector<TheButton *> buttons;
    // the buttons are arranged horizontally
    auto *layout = new QGridLayout();
    buttonWidget->setLayout(layout);


    auto *videoScroller = new QScrollArea();
    auto *inner = new QFrame(videoScroller);

    auto *searchBoxParent = new QLineEdit();
    auto *searchBox = new videoSearch(videos, searchBoxParent);
    //need to connect here and update the videos vector to _videos from the searchBox object
    videoSearch::connect(searchBox, SIGNAL(textChanged(QString)), searchBox, SLOT(search(QString)));

    for (int i = 0; i < static_cast<int>(searchBox->_filteredVideos.size()); i++) {
        auto *button = new TheButton(buttonWidget);
        auto *buttonLabel = new label();
        // when clicked, tell the player to play.
        TheButton::connect(button, SIGNAL(jumpTo(TheButtonInfo * )), player, SLOT (jumpTo(TheButtonInfo * )));
        videoSearch::connect(searchBox, SIGNAL(textChanged(QString)), button, SLOT(searchBtn(QString)));
        videoSearch::connect(searchBox, SIGNAL(textChanged(QString)), buttonLabel, SLOT(searchlabel(QString)));
        buttons.push_back(button);

        //as it shows filtered videos according to search
        QString Qstr = searchBox->_filteredVideos.at(i).url->toString();
        string label = Qstr.toStdString();
        size_t found = label.find_last_of('/');
        label = label.substr(found + 1);
        QString qstr = QString::fromStdString(label);
        //adds a label with the filename underneath each thumbnail
        buttonLabel->setText(qstr);
        layout->addWidget(button);
        layout->addWidget(buttonLabel);
        button->init(&videos.at(i));
    }
    inner->setLayout(layout);
    videoScroller->setWidget(inner);
    videoScroller->setWidgetResizable(true);
    //mute button is connected to the player and slider
    auto *videoSlider = new VideoSlider(buttonWidget);

    ThePlayer::connect(player, SIGNAL(durationChanged(qint64)), videoSlider, SLOT(SetRange(qint64)));
    ThePlayer::connect(player, SIGNAL(positionChanged(qint64)), videoSlider, SLOT(SetValue(qint64)));
    VideoSlider::connect(videoSlider, SIGNAL(valueChanged(int)), player, SLOT(SetPosition(int)));
    //player and video slider are mutually connected
    auto *playBtn = new PlayButton(buttonWidget);
    //skip buttons connected to the player

    PlayButton::connect(playBtn, SIGNAL(clicked(bool)), player, SLOT(click()));
    ThePlayer::connect(player, SIGNAL(stateChanged(QMediaPlayer::State)),
                       playBtn, SLOT(setState(QMediaPlayer::State)));

    auto *nextBtn = new NextButton(buttonWidget);
    auto *backBtn = new PrevButton(buttonWidget);

    NextButton::connect(nextBtn, SIGNAL(clicked()), player, SLOT(nextVideo()));
    PrevButton::connect(backBtn, SIGNAL(clicked()), player, SLOT(prevVideo()));
    //this buttons connected to the player so it goes to next button while clicked

    auto *length_label = new LengthLabel(buttonWidget);
    auto *duration_label = new LengthLabel(buttonWidget);
    duration_label->setWhatsThis("duration_label");
    length_label->setWhatsThis("length_label");

    ThePlayer::connect(player, SIGNAL(positionChanged(qint64)),
                       length_label, SLOT(setLength(qint64)));
    ThePlayer::connect(player, SIGNAL(durationChanged(qint64)),
                       duration_label, SLOT (setLength(qint64)));
    //as video changes, length and duration labels will change

    auto *frame = new QFrame();
    auto *buttonsBox = new QHBoxLayout();
    buttonsBox->addWidget(backBtn);
    buttonsBox->addWidget(playBtn);
    buttonsBox->addWidget(nextBtn);
    frame->setLayout(buttonsBox);
    //added a frame to set all buttons in hboxlayout
    frame->setWhatsThis("buttons");

    // tell the player what buttons and videos are available
    player->setContent(&buttons, &videos);

    // create the main window and layout
    QWidget window;
    auto *top = new ResponsiveLayout();
    window.setLayout(top);
    window.setWindowTitle("Tomeo");
    window.setMinimumSize(500, 500);

    // add the video and the buttons to the top level widget
    top->addWidget(videoWidget);
    top->addWidget(videoScroller);
    top->addWidget(videoSlider);
    top->addWidget(length_label);
    top->addWidget(duration_label);
    top->addWidget(frame);

    // showtime!
    window.show();

    // wait for the app to terminate
    return QApplication::exec();
}
