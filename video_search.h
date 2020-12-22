#ifndef VIDEO_SEARCH_H
#define VIDEO_SEARCH_H


#include <QPushButton>
#include <QStyle>
#include <QWidget>
#include <QLineEdit>
#include <vector>
#include <QLabel>
#include <QGraphicsDropShadowEffect>
#include "the_button.h"

using namespace std;

class VideoSearch : public QLineEdit {
Q_OBJECT
public:
    VideoSearch(const vector<TheButtonInfo> &videos, QWidget *parent) : QLineEdit(parent) {
        _allVideos = videos;
        _filteredVideos = videos;
        setPlaceholderText("Search Video");
        setStyleSheet("QLineEdit{ "
                      "background-color:white;"
                      "border: 2px solid gray;"
                      "border-radius: 10px;"
                      "padding: 0 8px;"
                      "selection-background-color: darkgray;"
                      "font-size: 16px;}"
        );
    }

public:
    vector<TheButtonInfo> _filteredVideos;
    vector<TheButtonInfo> _allVideos;
private slots:

    void search(const QString &text);
};

class label : public QLabel {
Q_OBJECT
public:
    label() : QLabel() {
    }

private slots:

    void searchLabel(const QString &text);
};

#endif // VIDEO_SEARCH_H
