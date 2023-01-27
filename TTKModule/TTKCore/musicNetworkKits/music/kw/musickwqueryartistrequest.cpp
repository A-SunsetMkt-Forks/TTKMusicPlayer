#include "musickwqueryartistrequest.h"

MusicKWQueryArtistRequest::MusicKWQueryArtistRequest(QObject *parent)
    : MusicQueryArtistRequest(parent)
{
    m_queryServer = QUERY_KW_INTERFACE;
}

void MusicKWQueryArtistRequest::startToSearch(const QString &value)
{
    TTK_INFO_STREAM(QString("%1 startToSearch %2").arg(className(), value));

    deleteAll();
    m_queryValue = value;

    QNetworkRequest request;
    request.setUrl(MusicUtils::Algorithm::mdII(KW_ARTIST_URL, false).arg(value).arg(0).arg(50));
    MusicKWInterface::makeRequestRawHeader(&request);

    m_reply = m_manager.get(request);
    connect(m_reply, SIGNAL(finished()), SLOT(downLoadFinished()));
    QtNetworkErrorConnect(m_reply, this, replyError);
}

void MusicKWQueryArtistRequest::downLoadFinished()
{
    TTK_INFO_STREAM(QString("%1 downLoadFinished").arg(className()));

    MusicQueryArtistRequest::downLoadFinished();
    if(m_reply && m_reply->error() == QNetworkReply::NoError)
    {
        QJson::Parser json;
        bool ok;
        const QVariant &data = json.parse(m_reply->readAll().replace("'", "\""), &ok);
        if(ok)
        {
            QVariantMap value = data.toMap();
            if(value.contains("abslist"))
            {
                bool artistFound = false;

                const QVariantList &datas = value["abslist"].toList();
                for(const QVariant &var : qAsConst(datas))
                {
                    if(var.isNull())
                    {
                        continue;
                    }

                    value = var.toMap();
                    TTK_NETWORK_QUERY_CHECK();

                    MusicObject::MusicSongInformation info;
                    info.m_singerName = MusicUtils::String::charactersReplaced(value["ARTIST"].toString());
                    info.m_songName = MusicUtils::String::charactersReplaced(value["SONGNAME"].toString());
                    info.m_duration = TTKTime::formatDuration(value["DURATION"].toInt() * 1000);

                    info.m_songId = value["MUSICRID"].toString().replace("MUSIC_", "");
                    info.m_artistId = value["ARTISTID"].toString();
                    info.m_albumId = value["ALBUMID"].toString();
                    info.m_albumName = MusicUtils::String::charactersReplaced(value["ALBUM"].toString());

                    info.m_year = value["RELEASEDATE"].toString();
                    info.m_trackNumber = "0";

                    info.m_coverUrl = MusicUtils::Algorithm::mdII(KW_ALBUM_COVER_URL, false).arg(info.m_songId);
                    info.m_lrcUrl = MusicUtils::Algorithm::mdII(KW_SONG_LRC_URL, false).arg(info.m_songId);
                    parseFromSongProperty(&info, value["FORMATS"].toString(), m_queryQuality, m_queryAllRecords);

                    if(info.m_songProps.isEmpty())
                    {
                        continue;
                    }

                    if(!findUrlFileSize(&info.m_songProps))
                    {
                        return;
                    }

                    if(!artistFound)
                    {
                        artistFound = true;
                        MusicResultDataItem result;
                        TTK_NETWORK_QUERY_CHECK();
                        queryArtistIntro(&result);
                        TTK_NETWORK_QUERY_CHECK();
                        result.m_id = info.m_artistId;
                        result.m_name = info.m_singerName;
                        Q_EMIT createArtistItem(result);
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

void MusicKWQueryArtistRequest::queryArtistIntro(MusicResultDataItem *item) const
{
    QNetworkRequest request;
    request.setUrl(MusicUtils::Algorithm::mdII(KW_ARTIST_INFO_URL, false).arg(m_queryValue));
    MusicKWInterface::makeRequestRawHeader(&request);

    QByteArray bytes = MusicObject::syncNetworkQueryForGet(&request);
    if(bytes.isEmpty())
    {
        return;
    }

    QJson::Parser json;
    bool ok;
    const QVariant &data = json.parse(bytes.replace("'", "\""), &ok);
    if(ok)
    {
        const QVariantMap &value = data.toMap();
        item->m_tags = value["country"].toString();
        item->m_updateTime = value["birthday"].toString();
        item->m_nickName = value["aartist"].toString();
        item->m_coverUrl = value["hts_pic"].toString();
        item->m_description = MusicUtils::String::convertHtmlToPlain(value["info"].toString());
    }
}
