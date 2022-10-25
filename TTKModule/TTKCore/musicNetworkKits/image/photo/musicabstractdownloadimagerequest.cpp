#include "musicabstractdownloadimagerequest.h"
#include "musicbackgroundmanager.h"
#include "musictopareawidget.h"

MusicAbstractDownloadImageRequest::MusicAbstractDownloadImageRequest(const QString &name, const QString &path, QObject *parent)
    : MusicAbstractNetwork(parent),
      m_index(0),
      m_counter(0),
      m_artName(name),
      m_savePath(path)
{

}

void MusicAbstractDownloadImageRequest::deleteAll()
{
    MusicAbstractNetwork::deleteAll();
    deleteLater();
}

void MusicAbstractDownloadImageRequest::downLoadDataFinished()
{
    MusicAbstractNetwork::downLoadFinished();
    if(++m_index >= m_counter)
    {
        G_BACKGROUND_PTR->setArtistName(m_artName);
        MusicTopAreaWidget::instance()->musicBackgroundThemeDownloadFinished();
        Q_EMIT downLoadDataChanged(TTK_DEFAULT_STR);
        deleteAll();
    }
}
