#include "musicdjradiocategoryrequest.h"

MusicDJRadioCategoryRequest::MusicDJRadioCategoryRequest(QObject *parent)
    : MusicAbstractDJRadioRequest(parent)
{

}

void MusicDJRadioCategoryRequest::startRequest()
{
    deleteAll();

    QNetworkRequest request;
    const QByteArray &parameter = makeTokenQueryUrl(&request,
                      MusicUtils::Algorithm::mdII(DJ_CATEGORY_URL, false),
                      QString("{}"));

    m_reply = m_manager.post(request, parameter);
    connect(m_reply, SIGNAL(finished()), SLOT(downLoadFinished()));
    QtNetworkErrorConnect(m_reply, this, replyError);
}

void MusicDJRadioCategoryRequest::downLoadFinished()
{
    m_items.clear();
    MusicAbstractDJRadioRequest::downLoadFinished();

    if(m_reply && m_reply->error() == QNetworkReply::NoError)
    {
        QJson::Parser json;
        bool ok;
        const QVariant &data = json.parse(m_reply->readAll(), &ok);
        if(ok)
        {
            QVariantMap value = data.toMap();
            if(value["code"].toInt() == 200 && value.contains("categories"))
            {
                const QVariantList &datas = value["categories"].toList();
                for(const QVariant &var : qAsConst(datas))
                {
                    if(var.isNull())
                    {
                        continue;
                    }

                    value = var.toMap();
                    TTK_NETWORK_QUERY_CHECK();

                    MusicResultDataItem result;
                    result.m_name = value["name"].toString();
                    result.m_id = value["id"].toString();
                    result.m_coverUrl = value["picMacUrl"].toString();
                    m_items << result;
                }
            }
        }
    }

    Q_EMIT downLoadDataChanged(QString());
    deleteAll();
}
