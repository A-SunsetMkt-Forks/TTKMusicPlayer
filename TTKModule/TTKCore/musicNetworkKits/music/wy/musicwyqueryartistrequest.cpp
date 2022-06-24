#include "musicwyqueryartistrequest.h"

MusicWYQueryArtistRequest::MusicWYQueryArtistRequest(QObject *parent)
    : MusicQueryArtistRequest(parent)
{
    m_queryServer = QUERY_WY_INTERFACE;
}

void MusicWYQueryArtistRequest::startToSearch(const QString &value)
{
    TTK_LOGGER_INFO(QString("%1 startToSearch %2").arg(className(), value));

    deleteAll();
    m_queryValue = value;

    QNetworkRequest request;
    const QByteArray &parameter = makeTokenQueryUrl(&request,
                      MusicUtils::Algorithm::mdII(WY_ARTIST_URL, false).arg(value),
                      QString("{}"));

    m_reply = m_manager.post(request, parameter);
    connect(m_reply, SIGNAL(finished()), SLOT(downLoadFinished()));
    QtNetworkErrorConnect(m_reply, this, replyError);
}

void MusicWYQueryArtistRequest::downLoadFinished()
{
    TTK_LOGGER_INFO(QString("%1 downLoadFinished").arg(className()));

    MusicQueryArtistRequest::downLoadFinished();
    if(m_reply && m_reply->error() == QNetworkReply::NoError)
    {
        QJson::Parser json;
        bool ok;
        const QVariant &data = json.parse(m_reply->readAll(), &ok);
        if(ok)
        {
            QVariantMap value = data.toMap();
            if(value["code"].toInt() == 200 && value.contains("hotSongs"))
            {
                bool artistFound = false;
                //
                const QVariantMap &artistObject = value["artist"].toMap();
                const QString &coverUrl = artistObject["picUrl"].toString();
                const QString &singerName = MusicUtils::String::charactersReplaced(artistObject["name"].toString());

                const QVariantList &datas = value["hotSongs"].toList();
                for(const QVariant &var : qAsConst(datas))
                {
                    if(var.isNull())
                    {
                        continue;
                    }

                    value = var.toMap();
                    TTK_NETWORK_QUERY_CHECK();

                    MusicObject::MusicSongInformation info;
                    info.m_songName = MusicUtils::String::charactersReplaced(value["name"].toString());
                    info.m_singerName = singerName;
                    info.m_coverUrl = coverUrl;
                    info.m_duration = MusicTime::msecTime2LabelJustified(value["dt"].toInt());
                    info.m_songId = QString::number(value["id"].toInt());
                    info.m_lrcUrl = MusicUtils::Algorithm::mdII(WY_SONG_LRC_OLD_URL, false).arg(info.m_songId);

                    const QVariantMap &albumObject = value["al"].toMap();
                    info.m_albumId = QString::number(albumObject["id"].toInt());
                    info.m_albumName = MusicUtils::String::charactersReplaced(albumObject["name"].toString());

                    const QVariantList &artistsArray = value["ar"].toList();
                    for(const QVariant &artistValue : qAsConst(artistsArray))
                    {
                        if(artistValue.isNull())
                        {
                            continue;
                        }

                        const QVariantMap &artistObject = artistValue.toMap();
                        info.m_artistId = QString::number(artistObject["id"].toULongLong());
                        break; //just find first singer
                    }

                    info.m_year = QString();
                    info.m_discNumber = value["cd"].toString();
                    info.m_trackNumber = value["no"].toString();

                    TTK_NETWORK_QUERY_CHECK();
                    readFromMusicSongPropertyNew(&info, value, m_queryQuality, m_queryAllRecords);
                    TTK_NETWORK_QUERY_CHECK();

                    if(info.m_songProps.isEmpty())
                    {
                        continue;
                    }

                    if(!artistFound)
                    {
                        artistFound = true;
                        MusicResultsItem result;
                        TTK_NETWORK_QUERY_CHECK();
                        downLoadIntro(&result);
                        TTK_NETWORK_QUERY_CHECK();
                        result.m_id = m_queryValue;
                        result.m_name = info.m_singerName;
                        result.m_nickName = artistObject["trans"].toString();
                        result.m_coverUrl = info.m_coverUrl;
                        Q_EMIT createArtistInfoItem(result);
                    }

                    MusicSearchedItem item;
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

void MusicWYQueryArtistRequest::downLoadIntro(MusicResultsItem *item) const
{
    QNetworkRequest request;
    const QByteArray &parameter = makeTokenQueryUrl(&request,
                      MusicUtils::Algorithm::mdII(WY_ARTIST_INFO_URL, false),
                      MusicUtils::Algorithm::mdII(WY_ARTIST_INFO_DATA_URL, false).arg(m_queryValue));

    const QByteArray &bytes = MusicObject::syncNetworkQueryForPost(&request, parameter);
    if(bytes.isEmpty())
    {
        return;
    }

    QJson::Parser json;
    bool ok;
    const QVariant &data = json.parse(bytes, &ok);
    if(ok)
    {
        QVariantMap value = data.toMap();
        if(value["code"].toInt() == 200)
        {
            item->m_description = value["briefDesc"].toString();
            if(!item->m_description.isEmpty())
            {
                item->m_description = QString("%1\r\n\r\n").arg(item->m_description);
            }

            const QVariantList &datas = value["introduction"].toList();
            for(const QVariant &var : qAsConst(datas))
            {
                if(var.isNull())
                {
                    continue;
                }

                value = var.toMap();
                item->m_description += QString("**%1**\r\n").arg(value["ti"].toString());
                item->m_description += value["txt"].toString() + "\r\n\r\n";
            }
        }
    }
}
