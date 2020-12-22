
#include <QFileInfo>
#include "video_search.h"

void VideoSearch::search(const QString& text) {
    _filteredVideos.clear();

    for (auto & _allVideo : _allVideos) {
        QString path = _allVideo.url->toString(); //get the file path as a string
        QFileInfo file(path);
        //get the base name of the file, eg: "name.mp4" would give "name"
        QString name = file.baseName();
        if (text == name) {
            _filteredVideos.push_back(_allVideo);
        }
    }
}

void label::searchLabel(const QString& text) {
    if (text == "") {
        setVisible(true);
    } else {
        setVisible(false);
    }
}
