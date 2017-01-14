#include "playerwidget.h"
#include "mainwindow.h"

PlayerWidget::PlayerWidget(MainWindow *parent, Data* data) // : QWidget(parent) ?
{
    this->mainWindow = parent;
    this->data = data;

    QVBoxLayout *layout = new QVBoxLayout;
    QLabel* label = new QLabel("Downloading...");
    label->setAlignment(Qt::AlignCenter);
    layout->addWidget(label);

    setLayout(layout);
}


//#include <QtMultimedia>
//#include <QtMultimediaWidgets>
//  QApplication app (argc, argv);

//  QMediaPlayer *player = new QMediaPlayer();
//  player->setMedia(QUrl::fromLocalFile("/home/nikkou/Dropborx/Techno/cpp/project/Slow_Chinese_164.mp3"));
//  player->setVolume(50);
//  player->play();
//  cout << strlen(player->errorString().toLatin1().data()) << "\n";
//  cout << player->error() << "\n";
//  // std::this_thread::sleep_for(std::chrono::milliseconds(20000));
