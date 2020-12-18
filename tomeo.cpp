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
#include <QtWidgets/QFileIconProvider>
#include <QDesktopServices>
#include <QImageReader>
#include <QMessageBox>
#include <QtCore/QDir>
#include <QtCore/QDirIterator>
#include "the_player.h"
#include "the_button.h"
#include <QScrollArea>
#include <QPushButton>
#include <QFrame>
#include <QLineEdit>
#include <QComboBox>

#include "the_layout.h"
#include "video_widget.h"
#include "video_search.h"


using namespace std;

vector<TheButtonInfo> thumbMatch(QString f, vector<TheButtonInfo> out, int index) {
    QString thumb = f.left( f.length() - 4) +".png";
    if (QFile(thumb).exists()) { // if a png thumbnail exists
        QImageReader *imageReader = new QImageReader(thumb);
        QImage sprite = imageReader->read(); // read the thumbnail
        if (!sprite.isNull()) {
            // voodoo to create an icon for the button
            QIcon* ico = new QIcon(QPixmap::fromImage(sprite));
            // convert the file location to a generic url
            QUrl* url = new QUrl(QUrl::fromLocalFile(f));
            // add to the output list
            out . push_back(TheButtonInfo(url, ico , index));
        } else {
            QString thumb = f.left(f.length() - 5) +"def.png";
            if (QFile(thumb).exists()) { // if a png thumbnail exists
                QImageReader *imageReader = new QImageReader(thumb);
                QImage sprite = imageReader->read(); // read the thumbnail
                if (!sprite.isNull()) {
                    // voodoo to create an icon for the button
                    QIcon* ico = new QIcon(QPixmap::fromImage(sprite));
                    // convert the file location to a generic url
                    QUrl* url = new QUrl(QUrl::fromLocalFile(f));
                    // add to the output list
                    out . push_back(TheButtonInfo(url, ico, index));
                }
            }
        }
    } else {
        QString thumb = f.left( f.length() - 5) +"def.png";
        if (QFile(thumb).exists()) { // if a png thumbnail exists
            QImageReader *imageReader = new QImageReader(thumb);
            QImage sprite = imageReader->read(); // read the thumbnail
            if (!sprite.isNull()) {
                // voodoo to create an icon for the button
                QIcon* ico = new QIcon(QPixmap::fromImage(sprite));
                // convert the file location to a generic url
                QUrl* url = new QUrl(QUrl::fromLocalFile(f));
                // add to the output list
                out . push_back(TheButtonInfo(url,ico ,index));
            }
        }
    }
    return out;
}

// read in videos and thumbnails to this directory
vector<TheButtonInfo> getInfoIn (string loc) {

    vector<TheButtonInfo> out =  vector<TheButtonInfo>();
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

    if (videos.size() == 0) {
        exit(-1);
    }

    // create the main window and layout
    QWidget window;

    // the widget that will show the video
    VideoScreen *videoWidget = new VideoScreen();

    // the QMediaPlayer which controls the playback
    ThePlayer *player = new ThePlayer;
    player->setVideoOutput(videoWidget);

    // a row of buttons
    QWidget *buttonWidget = new QWidget();
    // a list of the buttons
    vector<TheButton*> buttons;
    // the buttons are arranged horizontally
    QGridLayout *layout = new QGridLayout();
    buttonWidget->setLayout(layout);


    QScrollArea *videoScroller = new QScrollArea();
//    videoScroller->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
//    videoScroller->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    QFrame *inner = new QFrame(videoScroller);

    QLineEdit *searchBoxParent = new QLineEdit();
    videoSearch *searchBox = new videoSearch(videos, searchBoxParent);
    //need to connect here and update the videos vector to _videos from the searchBox object
    searchBox->connect(searchBox,SIGNAL(textChanged(QString)),searchBox,SLOT(search(QString)));

    for (int i = 0; i < static_cast<int>(searchBox->_filteredVideos.size()); i++) {
        TheButton *button = new TheButton(buttonWidget);
        label *buttonLabel = new label();
        // when clicked, tell the player to play.
        button->connect(button, SIGNAL(jumpTo(TheButtonInfo* )), 
            player, SLOT (jumpTo(TheButtonInfo*)));
        searchBox->connect(searchBox,SIGNAL(textChanged(QString)), 
            button, SLOT(searchBtn(QString)));
        searchBox->connect(searchBox,SIGNAL(textChanged(QString)),
            buttonLabel, SLOT(searchlabel(QString)));
        buttons.push_back(button);

        //as it shows filtered videos according to search
        QString Qstr = searchBox->_filteredVideos.at(i).url->toString();
        string label = Qstr.toStdString();
        size_t found = label.find_last_of("/");
        label = label.substr(found+1);
        QString qstr = QString::fromStdString(label);
        //adds a label with the filename underneath each thumbnail
        buttonLabel->setText(qstr);
//        layout->addWidget(button,2*(i/2),i%2);
//        layout->addWidget(buttonLabel,2*(i/2)+1,i%2);
        layout->addWidget(button);
        layout->addWidget(buttonLabel);

        button->init(&videos.at(i));
    }
    inner->setLayout(layout);
    videoScroller->setWidget(inner);
    videoScroller->setWidgetResizable(true);

    //connected combobox with playrate settting slot
    //playrate->connect(playrate,SIGNAL(activated(int)),player, SLOT(doPlayRate(int)));
    // tell the player what buttons and videos are available
    player->setContent(&buttons, & videos);

    // create the main layout
    ResponsiveLayout *top = new ResponsiveLayout();
    window.setLayout(top);
    window.setWindowTitle("Tomeo");
//    window.setMinimumSize(800, 800);

    // add the video and the buttons to the top level widget
    top->addWidget(videoWidget);
    top->addWidget(videoScroller);

    // showtime!
    window.show();

    // wait for the app to terminate
    return app.exec();
}
