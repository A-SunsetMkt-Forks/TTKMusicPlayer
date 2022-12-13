#include "musicydtranslationrequest.h"

#define QUERY_URL          "alNydEx6cDhBTklzNFBuUmJiOVk0RVZJZEZOUXRvVHVCcWxxeW4vTnFmbU1QTjBHT2ZuWUxxQU1SMlVPMklJeERSS2xJZTl2Sm1KWVNtUGxCb2JneGUrVTZxQXY2cjhmUmdHNk81QkYrdjVUYVJwZlFPa0NlQ05melF4MXJLUXMrWk5vcmtCWTRFb0pBSE9aeVhUR3FvcnI4SnV0REVwaWRKZk1QZz09"
#define TRANSLATION_URL    "MERYdllhU0NxcW1KS1BNQjFwYnQ2UXBDQmlkSUJ3S05tNUdSSUJxcnZjZlBpY0hRWGVVTkh0TjhFOFhlMnlDOExpY2VnVmlmWE1XMlhrK2l2YXl0T3RVbk5CdWo1R0I5UFFla1NBZ0tUK3hvaVA4SUsyNFRoRVlIQXJSbU5xaHlsUGU1N0svb1NNNjVvUWRLV2VvR2NKY2g4Zms9"

MusicYDTranslationRequest::MusicYDTranslationRequest(QObject *parent)
    : MusicAbstractTranslationRequest(parent)
{

}

void MusicYDTranslationRequest::startRequest(const QString &data)
{
    TTK_INFO_STREAM(QString("%1 startRequest").arg(className()));

    deleteAll();

    QString sid;
    {
        QNetworkRequest request;
        request.setUrl(MusicUtils::Algorithm::mdII(QUERY_URL, false));
        MusicObject::setSslConfiguration(&request);

        const QString &bytes = QString(MusicObject::syncNetworkQueryForGet(&request));
        if(bytes.isEmpty())
        {
            Q_EMIT downLoadDataChanged(QString());
            return;
        }

        const QRegExp regx("sid\\:\\s\\'([0-9a-f\\.]+)");
        sid = (regx.indexIn(bytes) != -1) ? regx.cap(1) : bytes;
    }

    if(sid.isEmpty())
    {
        Q_EMIT downLoadDataChanged(QString());
        return;
    }

    QNetworkRequest request;
    request.setUrl(MusicUtils::Algorithm::mdII(TRANSLATION_URL, false).arg(sid, mapToString(Language::Chinese), data));
    MusicObject::setSslConfiguration(&request);

    m_reply = m_manager.get(request);
    connect(m_reply, SIGNAL(finished()), SLOT(downLoadFinished()));
    QtNetworkErrorConnect(m_reply, this, replyError);
}

void MusicYDTranslationRequest::downLoadFinished()
{
    MusicAbstractTranslationRequest::downLoadFinished();
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
                const QVariantList &datas = value["text"].toList();
                for(const QVariant &var : qAsConst(datas))
                {
                    if(var.isNull())
                    {
                        continue;
                    }

                    Q_EMIT downLoadDataChanged(var.toString());
                    break;
                }
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

QString MusicYDTranslationRequest::mapToString(Language type) const
{
    switch(type)
    {
        case Language::Auto: return "auto";
        case Language::Chinese: return "zh";
        default: return QString();
    }
}
