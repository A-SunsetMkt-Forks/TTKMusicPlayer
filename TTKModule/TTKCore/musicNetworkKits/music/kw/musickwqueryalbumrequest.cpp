#include "musickwqueryalbumrequest.h"

MusicKWQueryAlbumRequest::MusicKWQueryAlbumRequest(QObject *parent)
    : MusicQueryAlbumRequest(parent)
{
    m_queryServer = QUERY_KW_INTERFACE;
}

void MusicKWQueryAlbumRequest::startToSearch(const QString &value)
{
    TTK_INFO_STREAM(QString("%1 startToSearch %2").arg(className(), value));

    deleteAll();
    m_queryValue = value;

    QNetworkRequest request;
    request.setUrl(MusicUtils::Algorithm::mdII(KW_ALBUM_URL, false).arg(value));
    MusicKWInterface::makeRequestRawHeader(&request);

    m_reply = m_manager.get(request);
    connect(m_reply, SIGNAL(finished()), SLOT(downLoadFinished()));
    QtNetworkErrorConnect(m_reply, this, replyError);
}

void MusicKWQueryAlbumRequest::startToSingleSearch(const QString &value)
{
    TTK_INFO_STREAM(QString("%1 startToSingleSearch %2").arg(className(), value));

    deleteAll();

    QNetworkRequest request;
    request.setUrl(MusicUtils::Algorithm::mdII(KW_ARTIST_ALBUM_URL, false).arg(value));
    MusicKWInterface::makeRequestRawHeader(&request);

    QNetworkReply *reply = m_manager.get(request);
    connect(reply, SIGNAL(finished()), SLOT(downLoadSingleFinished()));
    QtNetworkErrorConnect(reply, this, replyError);
}

void MusicKWQueryAlbumRequest::downLoadFinished()
{
    TTK_INFO_STREAM(QString("%1 downLoadFinished").arg(className()));

    MusicQueryAlbumRequest::downLoadFinished();
    if(m_reply && m_reply->error() == QNetworkReply::NoError)
    {
        QJson::Parser json;
        bool ok;
        const QVariant &data = json.parse(m_reply->readAll().replace("'", "\""), &ok);
        if(ok)
        {
            QVariantMap value = data.toMap();
            if(!value.isEmpty() && value.contains("musiclist"))
            {
                bool albumFound = false;
                //
                MusicResultDataItem result;
                const QString &albumName = value["name"].toString();
                result.m_nickName = value["albumid"].toString();
                result.m_coverUrl = value["pic"].toString();
                if(!MusicUtils::String::isNetworkUrl(result.m_coverUrl) && !result.m_coverUrl.contains(TTK_NULL_STR))
                {
                    result.m_coverUrl = MusicUtils::Algorithm::mdII(KW_ALBUM_COVER_PREFIX_URL, false) + result.m_coverUrl;
                }
                result.m_description = albumName + TTK_SPLITER +
                                       value["lang"].toString() + TTK_SPLITER +
                                       value["company"].toString() + TTK_SPLITER +
                                       value["pub"].toString();
                const QVariantList &datas = value["musiclist"].toList();
                for(const QVariant &var : qAsConst(datas))
                {
                    if(var.isNull())
                    {
                        continue;
                    }

                    value = var.toMap();
                    TTK_NETWORK_QUERY_CHECK();

                    MusicObject::MusicSongInformation info;
                    info.m_singerName = MusicUtils::String::charactersReplaced(value["artist"].toString());
                    info.m_songName = MusicUtils::String::charactersReplaced(value["name"].toString());
                    info.m_duration = TTK_DEFAULT_STR;

                    info.m_songId = value["id"].toString();
                    info.m_artistId = value["artistid"].toString();
                    info.m_albumId = result.m_nickName;
                    info.m_albumName = MusicUtils::String::charactersReplaced(albumName);

                    info.m_year = QString();
                    info.m_trackNumber = "0";

                    info.m_coverUrl = MusicUtils::Algorithm::mdII(KW_ALBUM_COVER_URL, false).arg(info.m_songId);
                    info.m_lrcUrl = MusicUtils::Algorithm::mdII(KW_SONG_LRC_URL, false).arg(info.m_songId);
                    parseFromSongProperty(&info, value["formats"].toString(), m_queryQuality, m_queryAllRecords);

                    if(info.m_songProps.isEmpty())
                    {
                        continue;
                    }

                    if(!findUrlFileSize(&info.m_songProps))
                    {
                        return;
                    }

                    if(!albumFound)
                    {
                        albumFound = true;
                        result.m_id = info.m_albumId;
                        result.m_name = info.m_singerName;
                        Q_EMIT createAlbumItem(result);
                    }

                    MusicResultInfoItem item;
                    item.m_songName = info.m_songName;
                    item.m_singerName = info.m_singerName;
                    item.m_albumName = info.m_albumName;
                    item.m_duration = info.m_duration;
                    item.m_type = mapQueryServerString();
                    Q_EMIT createSearchedItem(item);
                    m_songInfos << info;
                }
            }
        }
    }

    Q_EMIT downLoadDataChanged(QString());
    deleteAll();
}

void MusicKWQueryAlbumRequest::downLoadSingleFinished()
{
    TTK_INFO_STREAM(QString("%1 downLoadSingleFinished").arg(className()));

    MusicPageQueryRequest::downLoadFinished();
    QNetworkReply *reply = TTKObject_cast(QNetworkReply*, sender());
    if(reply && reply->error() == QNetworkReply::NoError)
    {
        QJson::Parser json;
        bool ok;
        const QVariant &data = json.parse(reply->readAll().replace("'", "\""), &ok);
        if(ok)
        {
            QVariantMap value = data.toMap();
            if(value.contains("albumlist"))
            {
                const QVariantList &datas = value["albumlist"].toList();
                for(const QVariant &var : qAsConst(datas))
                {
                    if(var.isNull())
                    {
                        continue;
                    }

                    value = var.toMap();
                    TTK_NETWORK_QUERY_CHECK();

                    MusicResultDataItem result;
                    result.m_id = value["albumid"].toString();
                    result.m_coverUrl = value["pic"].toString();
                    if(!result.m_coverUrl.contains(TTK_NULL_STR) && !MusicUtils::String::isNetworkUrl(result.m_coverUrl))
                    {
                        result.m_coverUrl = MusicUtils::Algorithm::mdII(KW_ALBUM_COVER_PREFIX_URL, false) + result.m_coverUrl;
                    }
                    result.m_name = value["name"].toString();
                    result.m_updateTime = value["pub"].toString().replace(TTK_DEFAULT_STR, TTK_DOT);
                    Q_EMIT createAlbumItem(result);
                }
            }
        }
    }

    Q_EMIT downLoadDataChanged(QString());
    deleteAll();
}
