#ifndef REMOTESOURCE_H
#define REMOTESOURCE_H

#include <string>
#include "source.h"
#include <QDebug>

class RemoteSource : public Source
{
    string audioUrl;
    string textUrl;
public:
    RemoteSource(string name, string lang, string audioUrl, string textUrl);
    string getAudioUrl();
    string getTextUrl();
};

#endif // REMOTESOURCE_H
