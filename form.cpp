#include "form.h"
#include "the_player.h"

Form::Form(QWidget *parent, QScrollArea *videoScroller, VideoSearch *searchBox, QLabel *label) :
        QWidget(parent),
        ui(new Ui::Form) {
    ui->setupUi(this);
    this->videoScroller = videoScroller;
    this->searchBox = searchBox;
    this->videoScroller->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->videoScroller->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->label = label;
    label->setStyleSheet("margin:10px; margin-bottom:0px; padding:0px");
}

Form::~Form() {
    delete ui;
}

void Form::resizeEvent(QResizeEvent *event) {
    videoScroller->setStyleSheet("border-color: translucent;");
    if (this->width() < 1000 && event!=nullptr) {
        this->ui->listLayout->addWidget(label);
        this->ui->listLayout->addWidget(videoScroller);
        this->ui->searchLayout->addWidget(searchBox);
        this->ui->widget_3->setVisible(false);
        this->ui->list->setVisible(true);
    } else {
        this->ui->listLayout2->addWidget(label);
        this->ui->listLayout2->addWidget(videoScroller);
        this->ui->searchLayout2->addWidget(searchBox);
        this->ui->list->setVisible(false);
        this->ui->widget_3->setVisible(true);
    }

}
