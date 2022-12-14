#include "musicabstractqueryrequest.h"

MusicAbstractQueryRequest::MusicAbstractQueryRequest(QObject *parent)
    : MusicPageQueryRequest(parent),
      m_queryServer("Invalid"),
      m_queryQuality(MusicObject::QueryQuality::Standard),
      m_queryAllRecords(false),
      m_queryLite(false)
{

}

void MusicAbstractQueryRequest::startToSingleSearch(const QString &id)
{
    Q_UNUSED(id);
}

QString MusicAbstractQueryRequest::mapQueryServerString() const
{
    const QString &v = tr("Current used server from %1");
    if(m_queryServer.contains(QUERY_KG_INTERFACE))
    {
        return v.arg(tr("KG"));
    }
    else if(m_queryServer.contains(QUERY_KW_INTERFACE))
    {
        return v.arg(tr("KW"));
    }
    else if(m_queryServer.contains(QUERY_WY_INTERFACE))
    {
        return v.arg(tr("WY"));
    }
    else
    {
        return QString();
    }
}

void MusicAbstractQueryRequest::downLoadFinished()
{
    Q_EMIT clearAllItems();
    m_songInfos.clear();
    MusicPageQueryRequest::downLoadFinished();
}

bool MusicAbstractQueryRequest::findUrlFileSize(MusicObject::MusicSongProperty *prop) const
{
    TTK_NETWORK_QUERY_CHECK(false);
    if(prop->m_size.isEmpty() || prop->m_size == TTK_DEFAULT_STR)
    {
        prop->m_size = MusicUtils::Number::sizeByte2Label(MusicObject::queryFileSizeByUrl(prop->m_url));
    }
    TTK_NETWORK_QUERY_CHECK(false);
    return true;
}

bool MusicAbstractQueryRequest::findUrlFileSize(MusicObject::MusicSongPropertyList *props) const
{
    for(int i = 0; i < props->count(); ++i)
    {
        if(!findUrlFileSize(&(*props)[i]))
        {
            return false;
        }
    }
    return true;
}
