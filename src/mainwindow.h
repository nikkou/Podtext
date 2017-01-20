#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QApplication>
#include <QLabel>
#include <string>
#include <QDebug> //remove all this stuff
#include <vector>
#include "downloader.h"
#include "listwidget.h"
#include "playerwidget.h"
#include "repo.h"
#include "source.h"
#include "remotesource.h"
#include "reader.h"
#include "settings.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    Settings *settings = nullptr;
    Repo *repo = nullptr;
    ListWidget *listWidget = nullptr;
    PlayerWidget *playerWidget = nullptr;

    explicit MainWindow(QWidget *parent = 0);
    virtual ~MainWindow();
    void enablePlayer(Data *data);
    Data *getData(Source *source);
    void updateStatus();\

signals:

};

#endif // MAINWINDOW_H
