#include "musickgcommentsrequest.h"
#include "musickgqueryrequest.h"

MusicKGSongCommentsRequest::MusicKGSongCommentsRequest(QObject *parent)
    : MusicCommentsRequest(parent)
{
    m_pageSize = 20;
}

void MusicKGSongCommentsRequest::startToPage(int offset)
{
    TTK_INFO_STREAM(QString("%1 startToSearch %2").arg(className()).arg(offset));

    deleteAll();
    m_totalSize = 0;

    QNetworkRequest request;
    request.setUrl(MusicUtils::Algorithm::mdII(KG_COMMENT_SONG_URL, false).arg(m_rawData["sid"].toString()).arg(offset + 1).arg(m_pageSize));
    MusicKGInterface::makeRequestRawHeader(&request);

    m_reply = m_manager.get(request);
    connect(m_reply, SIGNAL(finished()), SLOT(downLoadFinished()));
    QtNetworkErrorConnect(m_reply, this, replyError);
}

void MusicKGSongCommentsRequest::startToSearch(const QString &value)
{
    TTK_INFO_STREAM(QString("%1 startToSearch %2").arg(className(), value));

    TTKSemaphoreLoop loop;
    MusicKGQueryRequest *d = new MusicKGQueryRequest(this);
    connect(d, SIGNAL(downLoadDataChanged(QString)), &loop, SLOT(quit()));
    d->setQueryLite(true);
    d->setQueryAllRecords(false);
    d->startToSearch(MusicAbstractQueryRequest::QueryType::Music, value);
    loop.exec();

    m_rawData["sid"].clear();
    if(!d->isEmpty())
    {
        m_rawData["sid"] = d->songInfoList().front().m_songId;
        startToPage(0);
    }
}

void MusicKGSongCommentsRequest::downLoadFinished()
{
    TTK_INFO_STREAM(QString("%1 downLoadFinished").arg(className()));

    MusicCommentsRequest::downLoadFinished();
    if(m_reply && m_reply->error() == QNetworkReply::NoError)
    {
        QJson::Parser json;
        bool ok = false;
        const QVariant &data = json.parse(m_reply->readAll(), &ok);
        if(ok)
        {
            QVariantMap value = data.toMap();
            if(value["err_code"].toInt() == 0)
            {
                m_totalSize = value["count"].toLongLong();

                const QVariantList &datas = value["list"].toList();
                for(const QVariant &var : qAsConst(datas))
                {
                    if(var.isNull())
                    {
                        continue;
                    }

                    value = var.toMap();
                    TTK_NETWORK_QUERY_CHECK();

                    MusicResultDataItem result;
                    result.m_playCount = value["like"].toMap()["count"].toString();
                    result.m_updateTime = QString::number(QDateTime::fromString(value["addtime"].toString(), TTK_YEAR_STIME_FORMAT).toMSecsSinceEpoch());
                    result.m_description = value["content"].toString();
                    result.m_nickName = value["user_name"].toString();
                    result.m_coverUrl = value["user_pic"].toString();
                    Q_EMIT createCommentItem(result);
                }
            }
        }
    }

    Q_EMIT downLoadDataChanged(QString());
    deleteAll();
}



MusicKGPlaylistCommentsRequest::MusicKGPlaylistCommentsRequest(QObject *parent)
    : MusicCommentsRequest(parent)
{
    m_pageSize = 20;
}

void MusicKGPlaylistCommentsRequest::startToPage(int offset)
{
    TTK_INFO_STREAM(QString("%1 startToSearch %2").arg(className()).arg(offset));

    deleteAll();
    m_totalSize = 0;

    QNetworkRequest request;
    request.setUrl(MusicUtils::Algorithm::mdII(KG_COMMENT_PLAYLIST_URL, false).arg(m_rawData["sid"].toString()).arg(offset + 1).arg(m_pageSize));
    MusicKGInterface::makeRequestRawHeader(&request);

    m_reply = m_manager.get(request);
    connect(m_reply, SIGNAL(finished()), SLOT(downLoadFinished()));
    QtNetworkErrorConnect(m_reply, this, replyError);
}

void MusicKGPlaylistCommentsRequest::startToSearch(const QString &value)
{
    TTK_INFO_STREAM(QString("%1 startToSearch %2").arg(className(), value));

    m_rawData["sid"] = value;
    startToPage(0);
}

void MusicKGPlaylistCommentsRequest::downLoadFinished()
{
    TTK_INFO_STREAM(QString("%1 downLoadFinished").arg(className()));

    MusicCommentsRequest::downLoadFinished();
    if(m_reply && m_reply->error() == QNetworkReply::NoError)
    {
        QJson::Parser json;
        bool ok = false;
        const QVariant &data = json.parse(m_reply->readAll(), &ok);
        if(ok)
        {
            QVariantMap value = data.toMap();
            if(value["err_code"].toInt() == 0)
            {
                m_totalSize = value["count"].toLongLong();

                const QVariantList &datas = value["list"].toList();
                for(const QVariant &var : qAsConst(datas))
                {
                    if(var.isNull())
                    {
                        continue;
                    }

                    value = var.toMap();
                    TTK_NETWORK_QUERY_CHECK();

                    MusicResultDataItem result;
                    result.m_playCount = value["like"].toMap()["count"].toString();
                    result.m_updateTime = QString::number(QDateTime::fromString(value["addtime"].toString(), TTK_YEAR_STIME_FORMAT).toMSecsSinceEpoch());
                    result.m_description = value["content"].toString();
                    result.m_nickName = value["user_name"].toString();
                    result.m_coverUrl = value["user_pic"].toString();
                    Q_EMIT createCommentItem(result);
                }
            }
        }
    }

    Q_EMIT downLoadDataChanged(QString());
    deleteAll();
}
