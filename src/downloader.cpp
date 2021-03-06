#include "downloader.h"
#include "mainwindow.h"

using namespace std;

Downloader::Downloader(MainWindow *mainWindow, RemoteSource *source_param) : DataCreator(source_param)
{
    this->mainWindow = mainWindow;
    remoteSource = static_cast<RemoteSource *>(source);
}

Downloader::~Downloader() {

}

RemoteData *Downloader::getData() {
    data = new RemoteData();

    data->name = name;
    data->language = language;

    manager = new QNetworkAccessManager();
    qDebug() << "created manager";
//    connect(manager, SIGNAL(finished(QNetworkReply *)), this, SLOT(replyFinished(QNetworkReply *)));
    downloadText();
    qDebug() << "downloadText() done";

    return data;
}

void Downloader::downloadText() {
    QNetworkRequest textRequest(QUrl(remoteSource->getTextUrl().c_str()));
    textRequest.setRawHeader("User-Agent" , "Mozilla Firefox"); //needed for the server to accept the request otherwise error ensues
    textReply = manager->get(textRequest);
    currentReply = textReply;
    connect(textReply, SIGNAL(error(QNetworkReply::NetworkError)), SLOT(onError(QNetworkReply::NetworkError)));
    connect(textReply, SIGNAL(readyRead()), this, SLOT(readTextChunk()));
    connect(textReply, SIGNAL(finished()), SLOT(textFinished()));
}

void Downloader::downloadAudio() {
    QNetworkRequest audioRequest(QUrl(remoteSource->getAudioUrl().c_str()));
    audioRequest.setRawHeader("User-Agent" , "Mozilla Firefox"); //needed for the server to accept the request otherwise error ensues
    audioReply = manager->get(audioRequest);
    currentReply = textReply;
    connect(audioReply, SIGNAL(error(QNetworkReply::NetworkError)), SLOT(onError(QNetworkReply::NetworkError)));
    connect(audioReply, SIGNAL(readyRead()), this, SLOT(readAudioChunk()));
//    connect(audioReply, SIGNAL(downloadProgress(qint64, qint64)), this, SLOT(downloadProgress(qint64, qint64))); //too slow
    connect(audioReply, SIGNAL(finished()), SLOT(audioFinished()));
}

void Downloader::textFinished() {
    qDebug() << "all text was read";
    qDebug() << "text size in memory: " << this->data->text.size();
    textReply->deleteLater();

    this->data->parseText();

    mainWindow->updateStatus();

    downloadAudio();
}

void Downloader::audioFinished() {
    qDebug() << "all audio was read";
    qDebug() << "audio size in memory: " << this->data->audio.size();
    audioReply->deleteLater();
    currentReply = nullptr;
    mainWindow->updateStatus();
}

void Downloader::onError(QNetworkReply::NetworkError code)
{
    string str("Request failed with code ");
//    str.append(code);
    str.append(currentReply->errorString().toStdString());
    qDebug() << QString::fromStdString(str);
    mainWindow->onError(str);
}

//void Downloader::downloadProgress(qint64 received, qint64 total) {
//    qDebug() << "received " << received << " total " << total;
//}

void Downloader::readTextChunk() {
    QByteArray data = textReply->readAll();
    this->data->text.append(data.data());
    qlonglong totalSize = textReply->header(QNetworkRequest::ContentLengthHeader).toLongLong();
    double size = this->data->text.size();
    this->data->textDownloadedPercent = size / totalSize;
//    qDebug() << "text percent" << this->data->textDownloadedPercent;
    mainWindow->updateStatus();
}

void Downloader::readAudioChunk() {
    QByteArray data = audioReply->readAll();
    qlonglong totalSize = audioReply->header(QNetworkRequest::ContentLengthHeader).toLongLong();
    if (totalSize != this->data->audio.size()) {
        this->data->audio.append(totalSize, (char) 0);
    }
//    this->data->audio.append(data);
//    double size = this->data->audio.size();
    this->data->audio.replace(this->data->pos, data.size(), data);
    this->data->pos += data.size();
    this->data->audioDownloadedPercent = this->data->pos / totalSize;
    this->data->totalAudio = totalSize;
//    qDebug() << "audio percent" << this->data->audioDownloadedPercent;
    mainWindow->updateStatus();
}

Downloader::~Downloader()
{
	delete(mainWindow);
	delete(remoteSource);
	delete(manager);
	delete(audioReply);
	delete(textReply);
	delete(currentReply);
	delete(data);
}
