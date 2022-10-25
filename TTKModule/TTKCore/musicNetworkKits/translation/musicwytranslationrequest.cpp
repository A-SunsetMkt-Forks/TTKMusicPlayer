#include "musicwytranslationrequest.h"
#include "musicwyqueryinterface.h"
#include "musicwyqueryrequest.h"

MusicWYTranslationRequest::MusicWYTranslationRequest(QObject *parent)
    : MusicTranslationRequest(parent)
{

}

void MusicWYTranslationRequest::startRequest(const QString &data)
{
    TTK_INFO_STREAM(QString("%1 startToSearch").arg(className()));

    Q_UNUSED(data);
    deleteAll();

    MusicSemaphoreLoop loop;
    MusicWYQueryRequest *d = new MusicWYQueryRequest(this);
    connect(d, SIGNAL(downLoadDataChanged(QString)), &loop, SLOT(quit()));
    d->setQueryLite(true);
    d->setQueryAllRecords(false);
    d->startToSearch(MusicAbstractQueryRequest::QueryType::Music, QFileInfo(m_rawData["name"].toString()).baseName());
    loop.exec();

    QUrl url;
    if(!d->isEmpty())
    {
        url.setUrl(MusicUtils::Algorithm::mdII(WY_SONG_LRC_OLD_URL, false).arg(d->songInfoList().front().m_songId));
    }

    QNetworkRequest request;
    request.setUrl(url);
    MusicObject::setSslConfiguration(&request);

    m_reply = m_manager.get(request);
    connect(m_reply, SIGNAL(finished()), SLOT(downLoadFinished()));
    QtNetworkErrorConnect(m_reply, this, replyError);
}

void MusicWYTranslationRequest::downLoadFinished()
{
    MusicTranslationRequest::downLoadFinished();
    if(m_reply && m_reply->error() == QNetworkReply::NoError)
    {
        QJson::Parser json;
        bool ok;
        const QVariant &data = json.parse(m_reply->readAll(), &ok);
        if(ok)
        {
            QVariantMap value = data.toMap();
            if(value.contains("code") && value["code"].toInt() == 200)
            {
                value = value["tlyric"].toMap();
                Q_EMIT downLoadDataChanged(value["lyric"].toString());
            }
        }
        else
        {
            Q_EMIT downLoadDataChanged(QString());
        }
    }
    else
    {
        TTK_ERROR_STREAM("Translation source data error");
        Q_EMIT downLoadDataChanged(QString());
    }

    deleteAll();
}