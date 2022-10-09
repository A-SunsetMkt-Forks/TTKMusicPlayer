#include "qsyncdeletedata.h"
#include "qsyncdatainterface_p.h"

QSyncDeleteData::QSyncDeleteData(QNetworkAccessManager *networkManager, QObject *parent)
    : QSyncDataInterface(networkManager, parent)
{

}

void QSyncDeleteData::deleteDataOperator(const QString &bucket, const QString &fileName)
{
    TTK_D(QSyncDataInterface);
    const QString &method = "DELETE";
    const QString &url = TTK_SEPARATOR + fileName;
    const QString &resource = TTK_SEPARATOR + bucket + url;
    const QString &host = bucket + TTK_DOT + QSyncConfig::HOST;

    TTKStringMap headers;
    headers.insert("Date", QSyncUtils::GMT());
    headers.insert("Host", host);
    headers.insert("Content-Type", "charset=utf-8");

    d->insertAuthorization(method, headers, resource);

    QNetworkRequest request;
    request.setUrl("http://" + host + url);

    for(auto itr = headers.constBegin(); itr != headers.constEnd(); ++itr)
    {
        request.setRawHeader(itr.key().toUtf8(), itr.value().toUtf8());
    }

    QNetworkReply *reply = d->m_manager->deleteResource(request);
    connect(reply, SIGNAL(finished()), SLOT(receiveDataFromServer()));
    QtNetworkErrorConnect(reply, this, replyError);
}

void QSyncDeleteData::receiveDataFromServer()
{
    QNetworkReply *reply = TTKObject_cast(QNetworkReply*, sender());
    if(reply)
    {
        Q_EMIT deleteFileFinished(reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt() == 204);
        reply->deleteLater();
    }
    else
    {
        Q_EMIT deleteFileFinished(false);
    }
}
