#include "musicwyquerymovierequest.h"

MusicWYQueryMovieRequest::MusicWYQueryMovieRequest(QObject *parent)
    : MusicQueryMovieRequest(parent)
{
    m_pageSize = 40;
    m_queryServer = QUERY_WY_INTERFACE;
}

void MusicWYQueryMovieRequest::startToPage(int offset)
{
    TTK_INFO_STREAM(QString("%1 startToSearch %2").arg(className()).arg(offset));

    deleteAll();
    m_totalSize = 0;
    m_pageSize = 20;

    QNetworkRequest request;
    const QByteArray &parameter = makeTokenQueryUrl(&request,
                      MusicUtils::Algorithm::mdII(WY_ARTIST_MOVIE_URL, false),
                      MusicUtils::Algorithm::mdII(WY_ARTIST_MOVIE_DATA_URL, false).arg(m_queryValue).arg(m_pageSize * offset).arg(m_pageSize));

    m_reply = m_manager.post(request, parameter);
    connect(m_reply, SIGNAL(finished()), SLOT(downLoadPageFinished()));
    QtNetworkErrorConnect(m_reply, this, replyError);
}

void MusicWYQueryMovieRequest::startToSearch(QueryType type, const QString &value)
{
    TTK_INFO_STREAM(QString("%1 startToSearch %2").arg(className(), value));

    deleteAll();
    m_queryType = type;
    m_queryValue = value.trimmed();

    QNetworkRequest request;
    const QByteArray &parameter = makeTokenQueryUrl(&request,
                      MusicUtils::Algorithm::mdII(WY_SONG_SEARCH_URL, false),
                      MusicUtils::Algorithm::mdII(WY_SONG_SEARCH_DATA_URL, false).arg(m_queryValue).arg(1014).arg(m_pageSize).arg(0).toUtf8());

    m_reply = m_manager.post(request, parameter);
    connect(m_reply, SIGNAL(finished()), SLOT(downLoadFinished()));
    QtNetworkErrorConnect(m_reply, this, replyError);
}

void MusicWYQueryMovieRequest::startToSingleSearch(const QString &value)
{
    TTK_INFO_STREAM(QString("%1 startToSingleSearch %2").arg(className(), value));

    deleteAll();
    m_queryValue = value.trimmed();

    QTimer::singleShot(MT_MS, this, SLOT(downLoadSingleFinished()));
}

void MusicWYQueryMovieRequest::downLoadFinished()
{
    TTK_INFO_STREAM(QString("%1 downLoadFinished").arg(className()));

    MusicQueryMovieRequest::downLoadFinished();
    if(m_reply && m_reply->error() == QNetworkReply::NoError)
    {
        QJson::Parser json;
        bool ok;
        const QVariant &data = json.parse(m_reply->readAll(), &ok);
        if(ok)
        {
            QVariantMap value = data.toMap();
            if(value["code"].toInt() == 200)
            {
                value = value["result"].toMap();
                m_totalSize = value["videoCount"].toInt();

                const QVariantList &datas = value["videos"].toList();
                for(const QVariant &var : qAsConst(datas))
                {
                    if(var.isNull())
                    {
                        continue;
                    }

                    value = var.toMap();
                    TTK_NETWORK_QUERY_CHECK();

                    const int type = value["type"].toInt();
                    if(type == 0)
                    {
                        const qint64 mvid = value["vid"].toLongLong();
                        if(mvid == 0)
                        {
                            continue;
                        }

                        TTK_NETWORK_QUERY_CHECK();
                        queryMovieList(mvid);
                        TTK_NETWORK_QUERY_CHECK();
                    }
                    else if(type == 1)
                    {
                        const QString &vid = value["vid"].toString();
                        TTK_NETWORK_QUERY_CHECK();
                        queryVideoList(vid);
                        TTK_NETWORK_QUERY_CHECK();
                    }
                }
            }
        }
    }

    Q_EMIT downLoadDataChanged(QString());
    deleteAll();
}

void MusicWYQueryMovieRequest::downLoadPageFinished()
{
    TTK_INFO_STREAM(QString("%1 downLoadPageFinished").arg(className()));

    MusicPageQueryRequest::downLoadFinished();
    if(m_reply && m_reply->error() == QNetworkReply::NoError)
    {
        QJson::Parser json;
        bool ok;
        const QVariant &data = json.parse(m_reply->readAll(), &ok);
        if(ok)
        {
            QVariantMap value = data.toMap();
            if(value["code"].toInt() == 200 && value.contains("mvs"))
            {
                TTK_NETWORK_QUERY_CHECK();
                queryArtistMoviesCount(m_queryValue.toLongLong());
                TTK_NETWORK_QUERY_CHECK();

                const QVariantList &datas = value["mvs"].toList();
                for(const QVariant &var : qAsConst(datas))
                {
                    if(var.isNull())
                    {
                        continue;
                    }

                    value = var.toMap();
                    TTK_NETWORK_QUERY_CHECK();

                    MusicResultDataItem result;
                    result.m_id = QString::number(value["id"].toLongLong());
                    result.m_coverUrl = value["imgurl"].toString();
                    result.m_name = value["name"].toString();
                    result.m_updateTime.clear();
                    Q_EMIT createMovieItem(result);
                }
            }
        }
    }

    Q_EMIT downLoadDataChanged(QString());
    deleteAll();
}

void MusicWYQueryMovieRequest::downLoadSingleFinished()
{
    TTK_INFO_STREAM(QString("%1 downLoadSingleFinished").arg(className()));

    MusicQueryMovieRequest::downLoadFinished();

    const qint64 mvid = m_queryValue.toLongLong();
    if(mvid != 0)
    {
        TTK_NETWORK_QUERY_CHECK();
        queryMovieList(mvid);
        TTK_NETWORK_QUERY_CHECK();
    }

    Q_EMIT downLoadDataChanged(QString());
    deleteAll();
}

void MusicWYQueryMovieRequest::queryMovieList(qint64 id)
{
    QNetworkRequest request;
    const QByteArray &parameter = makeTokenQueryUrl(&request,
                      MusicUtils::Algorithm::mdII(WY_MOVIE_URL, false),
                      MusicUtils::Algorithm::mdII(WY_MOVIE_DATA_URL, false).arg(id));

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
            value = value["data"].toMap();
            MusicObject::MusicSongInformation info;
            info.m_songId = QString::number(id);
            info.m_songName = MusicUtils::String::charactersReplaced(value["name"].toString());
            info.m_singerName = MusicUtils::String::charactersReplaced(value["artistName"].toString());
            info.m_duration = TTKTime::msecTime2LabelJustified(value["duration"].toInt());

            value = value["brs"].toMap();
            for(const QString &key : value.keys())
            {
                const int bitrate = key.toInt();
                MusicObject::MusicSongProperty prop;
                if(bitrate <= 375)
                    prop.m_bitrate = MB_250;
                else if(bitrate > 375 && bitrate <= 625)
                    prop.m_bitrate = MB_500;
                else if(bitrate > 625 && bitrate <= 875)
                    prop.m_bitrate = MB_750;
                else if(bitrate > 875)
                    prop.m_bitrate = MB_1000;

                prop.m_url = value[key].toString();
                prop.m_format = MusicUtils::String::stringSplitToken(prop.m_url);

                if(!findUrlFileSize(&prop))
                {
                    return;
                }

                info.m_songProps.append(prop);
            }

            if(info.m_songProps.isEmpty())
            {
                return;
            }

            MusicResultInfoItem item;
            item.m_songName = info.m_songName;
            item.m_singerName = info.m_singerName;
            item.m_duration = info.m_duration;
            item.m_type = mapQueryServerString();
            Q_EMIT createSearchedItem(item);
            m_songInfos << info;
        }
    }
}

void MusicWYQueryMovieRequest::queryVideoList(const QString &id)
{
    QNetworkRequest request;
    const QByteArray &parameter = makeTokenQueryUrl(&request,
                      MusicUtils::Algorithm::mdII(WY_VIDEO_INFO_URL, false),
                      MusicUtils::Algorithm::mdII(WY_VIDEO_INFO_DATA_URL, false).arg(id));

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
            value = value["data"].toMap();
            MusicObject::MusicSongInformation info;
            info.m_songId = id;
            info.m_songName = MusicUtils::String::charactersReplaced(value["title"].toString());
            info.m_duration = TTKTime::msecTime2LabelJustified(value["durationms"].toInt());

            const QVariantMap &artistObject = value["creator"].toMap();
            info.m_singerName = MusicUtils::String::charactersReplaced(artistObject["nickname"].toString());

            const QVariantList &datas = value["resolutions"].toList();
            for(const QVariant &var : qAsConst(datas))
            {
                if(var.isNull())
                {
                    continue;
                }

                value = var.toMap();
                TTK_NETWORK_QUERY_CHECK();

                const int bitrate = value["resolution"].toInt();
                MusicObject::MusicSongProperty prop;
                queryVideoUrlPath(prop.m_url, id, bitrate);
                TTK_NETWORK_QUERY_CHECK();

                if(prop.m_url.isEmpty())
                {
                    continue;
                }

                if(bitrate <= 375)
                    prop.m_bitrate = MB_250;
                else if(bitrate > 375 && bitrate <= 625)
                    prop.m_bitrate = MB_500;
                else if(bitrate > 625 && bitrate <= 875)
                    prop.m_bitrate = MB_750;
                else if(bitrate > 875)
                    prop.m_bitrate = MB_1000;

                prop.m_size = MusicUtils::Number::sizeByte2Label(value["size"].toInt());
                prop.m_format = MusicUtils::String::stringSplitToken(prop.m_url);
                info.m_songProps.append(prop);
            }

            if(info.m_songProps.isEmpty())
            {
                return;
            }

            MusicResultInfoItem item;
            item.m_songName = info.m_songName;
            item.m_singerName = info.m_singerName;
            item.m_duration = info.m_duration;
            item.m_type = mapQueryServerString();
            Q_EMIT createSearchedItem(item);
            m_songInfos << info;
        }
    }
}

void MusicWYQueryMovieRequest::queryVideoUrlPath(QString &url, const QString &id, int bitrate) const
{
    QNetworkRequest request;
    const QByteArray &parameter = makeTokenQueryUrl(&request,
                      MusicUtils::Algorithm::mdII(WY_VIDEO_PATH_URL, false),
                      MusicUtils::Algorithm::mdII(WY_VIDEO_PATH_DATA_URL, false).arg(id).arg(bitrate));

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
            const QVariantList &datas = value["urls"].toList();
            for(const QVariant &var : qAsConst(datas))
            {
                if(var.isNull())
                {
                    continue;
                }

                value = var.toMap();
                TTK_NETWORK_QUERY_CHECK();

                url = value["url"].toString();
                if(!url.isEmpty())
                {
                    return;
                }
            }
        }
    }
}

void MusicWYQueryMovieRequest::queryArtistMoviesCount(qint64 id)
{
    m_totalSize = TTK_HIGH_LEVEL;

    QNetworkRequest request;
    const QByteArray &parameter = makeTokenQueryUrl(&request,
                      MusicUtils::Algorithm::mdII(WY_ARTIST_MOVIE_URL, false),
                      MusicUtils::Algorithm::mdII(WY_ARTIST_MOVIE_DATA_URL, false).arg(id).arg(0).arg(TTK_HIGH_LEVEL));

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
        const QVariantMap &value = data.toMap();
        if(value["code"].toInt() == 200 && value.contains("mvs"))
        {
            m_totalSize = value["mvs"].toList().count();
        }
    }
}
