#include "form.h"

Form::Form(QWidget *parent,QScrollArea* videoScroller, videoSearch* searchBox) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);
    this->videoScroller = videoScroller;
    this->searchBox = searchBox;
}

Form::~Form()
{
    delete ui;
}

void Form::resizeEvent(QResizeEvent *event) {
    videoScroller->setStyleSheet("border-color: translucent;");
    if(this->width()< 1000 && event != nullptr) {
        this->ui->listLayout->addWidget(videoScroller);
        this->ui->searchLayout->addWidget(searchBox);
        this->ui->widget_3->setVisible(0);
        this->ui->list->setVisible(1);
    }
    else {
        this->ui->listLayout2->addWidget(videoScroller);
        this->ui->searchLayout2->addWidget(searchBox);
        this->ui->list->setVisible(0);
        this->ui->widget_3->setVisible(1);
    }
}
