#include "musicdownloadbackgroundrequest.h"
#include "musicbpdownloadimagerequest.h"
#include "musickwdownloadimagerequest.h"
#include "musictxdownloadimagerequest.h"

MusicDownloadBackgroundRequest::MusicDownloadBackgroundRequest(const QString &name, const QString &path, QObject *parent)
    : MusicAbstractNetwork(parent),
      m_pluginIndex(-1),
      m_name(name),
      m_path(path)
{

}

void MusicDownloadBackgroundRequest::startRequest()
{
    m_pluginIndex = -1;
    findAllPlugins();
}

void MusicDownloadBackgroundRequest::downLoadFinished(const QString &bytes)
{
    if(bytes == TTK_DEFAULT_STR)
    {
        deleteLater();
        return;
    }
    else if(bytes.toInt() == 0)
    {
        findAllPlugins();
    }
}

void MusicDownloadBackgroundRequest::findAllPlugins()
{
    MusicAbstractDownloadImageRequest *d = nullptr;
    switch(++m_pluginIndex)
    {
        case 0: d = new MusicKWDownloadBackgroundRequest(m_name, m_path, this); break;
        case 1: d = new MusicTXDownloadBackgroundRequest(m_name, m_path, this); break;
        case 2: d = new MusicBPDownloadBackgroundRequest(m_name, m_path, this); break;
        default: deleteLater(); break;
    }

    if(d)
    {
        connect(d, SIGNAL(downLoadDataChanged(QString)), SLOT(downLoadFinished(QString)));
        d->startRequest();
    }
}
