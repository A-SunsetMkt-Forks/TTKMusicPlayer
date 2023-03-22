#include "musicdownloadqueryfactory.h"
//
#include "musicwyqueryrequest.h"
#include "musickgqueryrequest.h"
#include "musickwqueryrequest.h"
//
#include "musicwyquerymovierequest.h"
#include "musickgquerymovierequest.h"
#include "musickwquerymovierequest.h"
//
#include "musicwyqueryalbumrequest.h"
#include "musickgqueryalbumrequest.h"
#include "musickwqueryalbumrequest.h"
//
#include "musicwyqueryartistrequest.h"
#include "musickgqueryartistrequest.h"
#include "musickwqueryartistrequest.h"
//
#include "musicwyqueryartistlistrequest.h"
#include "musickgqueryartistlistrequest.h"
#include "musickwqueryartistlistrequest.h"
//
#include "musicwyquerytoplistrequest.h"
#include "musickgquerytoplistrequest.h"
#include "musickwquerytoplistrequest.h"
//
#include "musicwyqueryplaylistrequest.h"
#include "musickgqueryplaylistrequest.h"
#include "musickwqueryplaylistrequest.h"
//
#include "musicqueryrecommendrequest.h"
//
#include "musicwycommentsrequest.h"
#include "musickgcommentsrequest.h"
#include "musickwcommentsrequest.h"
//
#include "musicwydiscoverlistrequest.h"
#include "musickgdiscoverlistrequest.h"
#include "musickwdiscoverlistrequest.h"
//
#include "musicwysongsuggestrequest.h"
#include "musickgsongsuggestrequest.h"
#include "musickwsongsuggestrequest.h"
//
#include "musictranslationrequest.h"
//
#include "musicdownloaddatarequest.h"
//
#include "musicdownloadtextrequest.h"
#include "musicwydownloadtextrequest.h"
#include "musickwdownloadtextrequest.h"
//
#include "musickwdownloadimagerequest.h"
#include "musicdownloadbackgroundrequest.h"
//

MusicAbstractQueryRequest *MusicDownLoadQueryFactory::makeQueryRequest(QObject *parent)
{
    MusicAbstractQueryRequest *request = nullptr;
    const int index = G_SETTING_PTR->value(MusicSettingManager::DownloadServerIndex).toInt();
    switch(TTKStaticCast(MusicAbstractQueryRequest::QueryServer, index))
    {
        case MusicAbstractQueryRequest::QueryServer::WY: request = new MusicWYQueryRequest(parent); break;
        case MusicAbstractQueryRequest::QueryServer::KW: request = new MusicKWQueryRequest(parent); break;
        case MusicAbstractQueryRequest::QueryServer::KG: request = new MusicKGQueryRequest(parent); break;
        default: request = new MusicWYQueryRequest(parent);
    }
    TTK_INFO_STREAM(QString("MusicQueryrequest server: %1").arg(request->queryServer()));
    return request;
}

MusicAbstractQueryRequest *MusicDownLoadQueryFactory::makeMovieRequest(QObject *parent)
{
    MusicAbstractQueryRequest *request = nullptr;
    const int index = G_SETTING_PTR->value(MusicSettingManager::DownloadServerIndex).toInt();
    switch(TTKStaticCast(MusicAbstractQueryRequest::QueryServer, index))
    {
        case MusicAbstractQueryRequest::QueryServer::WY: request = new MusicWYQueryMovieRequest(parent); break;
        case MusicAbstractQueryRequest::QueryServer::KW: request = new MusicKWQueryMovieRequest(parent); break;
        case MusicAbstractQueryRequest::QueryServer::KG: request = new MusicKGQueryMovieRequest(parent); break;
        default: request = new MusicWYQueryMovieRequest(parent);
    }
    TTK_INFO_STREAM(QString("MusicQueryMovieRequest server: %1").arg(request->queryServer()));
    return request;
}

MusicAbstractQueryRequest *MusicDownLoadQueryFactory::makeAlbumRequest(QObject *parent)
{
    MusicAbstractQueryRequest *request = nullptr;
    const int index = G_SETTING_PTR->value(MusicSettingManager::DownloadServerIndex).toInt();
    switch(TTKStaticCast(MusicAbstractQueryRequest::QueryServer, index))
    {
        case MusicAbstractQueryRequest::QueryServer::WY: request = new MusicWYQueryAlbumRequest(parent); break;
        case MusicAbstractQueryRequest::QueryServer::KW: request = new MusicKWQueryAlbumRequest(parent); break;
        case MusicAbstractQueryRequest::QueryServer::KG: request = new MusicKGQueryAlbumRequest(parent); break;
        default: request = new MusicWYQueryAlbumRequest(parent);
    }
    TTK_INFO_STREAM(QString("MusicQueryAlbumRequest server: %1").arg(request->queryServer()));
    return request;
}

MusicAbstractQueryRequest *MusicDownLoadQueryFactory::makeArtistRequest(QObject *parent)
{
    MusicAbstractQueryRequest *request = nullptr;
    const int index = G_SETTING_PTR->value(MusicSettingManager::DownloadServerIndex).toInt();
    switch(TTKStaticCast(MusicAbstractQueryRequest::QueryServer, index))
    {
        case MusicAbstractQueryRequest::QueryServer::WY: request = new MusicWYQueryArtistRequest(parent); break;
        case MusicAbstractQueryRequest::QueryServer::KW: request = new MusicKWQueryArtistRequest(parent); break;
        case MusicAbstractQueryRequest::QueryServer::KG: request = new MusicKGQueryArtistRequest(parent); break;
        default: request = new MusicWYQueryArtistRequest(parent);
    }
    TTK_INFO_STREAM(QString("MusicQueryArtistRequest server: %1").arg(request->queryServer()));
    return request;
}

MusicAbstractQueryRequest *MusicDownLoadQueryFactory::makeArtistListRequest(QObject *parent)
{
    MusicAbstractQueryRequest *request = nullptr;
    const int index = G_SETTING_PTR->value(MusicSettingManager::DownloadServerIndex).toInt();
    switch(TTKStaticCast(MusicAbstractQueryRequest::QueryServer, index))
    {
        case MusicAbstractQueryRequest::QueryServer::WY: request = new MusicWYQueryArtistListRequest(parent); break;
        case MusicAbstractQueryRequest::QueryServer::KW: request = new MusicKWQueryArtistListRequest(parent); break;
        case MusicAbstractQueryRequest::QueryServer::KG: request = new MusicKGQueryArtistListRequest(parent); break;
        default: request = new MusicWYQueryArtistListRequest(parent);
    }
    TTK_INFO_STREAM(QString("MusicQueryArtistListRequest server: %1").arg(request->queryServer()));
    return request;
}

MusicAbstractQueryRequest *MusicDownLoadQueryFactory::makeToplistRequest(QObject *parent)
{
    MusicAbstractQueryRequest *request = nullptr;
    const int index = G_SETTING_PTR->value(MusicSettingManager::DownloadServerIndex).toInt();
    switch(TTKStaticCast(MusicAbstractQueryRequest::QueryServer, index))
    {
        case MusicAbstractQueryRequest::QueryServer::WY: request = new MusicWYQueryToplistRequest(parent); break;
        case MusicAbstractQueryRequest::QueryServer::KW: request = new MusicKWQueryToplistRequest(parent); break;
        case MusicAbstractQueryRequest::QueryServer::KG: request = new MusicKGQueryToplistRequest(parent); break;
        default: request = new MusicWYQueryToplistRequest(parent);
    }
    TTK_INFO_STREAM(QString("MusicQueryToplistRequest server: %1").arg(request->queryServer()));
    return request;
}

MusicAbstractQueryRequest *MusicDownLoadQueryFactory::makePlaylistRequest(QObject *parent)
{
    MusicAbstractQueryRequest *request = nullptr;
    const int index = G_SETTING_PTR->value(MusicSettingManager::DownloadServerIndex).toInt();
    switch(TTKStaticCast(MusicAbstractQueryRequest::QueryServer, index))
    {
        case MusicAbstractQueryRequest::QueryServer::WY: request = new MusicWYQueryPlaylistRequest(parent); break;
        case MusicAbstractQueryRequest::QueryServer::KW: request = new MusicKWQueryPlaylistRequest(parent); break;
        case MusicAbstractQueryRequest::QueryServer::KG: request = new MusicKGQueryPlaylistRequest(parent); break;
        default: request = new MusicWYQueryPlaylistRequest(parent);
    }
    TTK_INFO_STREAM(QString("MusicQueryPlaylistRequest server: %1").arg(request->queryServer()));
    return request;
}

MusicAbstractQueryRequest *MusicDownLoadQueryFactory::makeRecommendRequest(QObject *parent)
{
    return (new MusicQueryRecommendRequest(parent));
}

MusicAbstractQueryRequest *MusicDownLoadQueryFactory::makeSimilarSongRequest(QObject *parent)
{
    return makeQueryRequest(parent);
}

MusicSongSuggestRequest *MusicDownLoadQueryFactory::makeSuggestRequest(QObject *parent)
{
    MusicSongSuggestRequest *request = nullptr;
    const int index = G_SETTING_PTR->value(MusicSettingManager::DownloadServerIndex).toInt();
    switch(TTKStaticCast(MusicAbstractQueryRequest::QueryServer, index))
    {
        case MusicAbstractQueryRequest::QueryServer::WY: request = new MusicWYSongSuggestRequest(parent); break;
        case MusicAbstractQueryRequest::QueryServer::KW: request = new MusicKWSongSuggestRequest(parent); break;
        case MusicAbstractQueryRequest::QueryServer::KG: request = new MusicKGSongSuggestRequest(parent); break;
        default: request = new MusicWYSongSuggestRequest(parent);
    }
    return request;
}

MusicCommentsRequest *MusicDownLoadQueryFactory::makeSongCommentRequest(QObject *parent)
{
    MusicCommentsRequest *request = nullptr;
    const int index = G_SETTING_PTR->value(MusicSettingManager::DownloadServerIndex).toInt();
    switch(TTKStaticCast(MusicAbstractQueryRequest::QueryServer, index))
    {
        case MusicAbstractQueryRequest::QueryServer::WY: request = new MusicWYSongCommentsRequest(parent); break;
        case MusicAbstractQueryRequest::QueryServer::KW: request = new MusicKWSongCommentsRequest(parent); break;
        case MusicAbstractQueryRequest::QueryServer::KG: request = new MusicKGSongCommentsRequest(parent); break;
        default: request = new MusicWYSongCommentsRequest(parent);
    }
    return request;
}

MusicCommentsRequest *MusicDownLoadQueryFactory::makePlaylistCommentRequest(QObject *parent)
{
    MusicCommentsRequest *request = nullptr;
    const int index = G_SETTING_PTR->value(MusicSettingManager::DownloadServerIndex).toInt();
    switch(TTKStaticCast(MusicAbstractQueryRequest::QueryServer, index))
    {
        case MusicAbstractQueryRequest::QueryServer::WY: request = new MusicWYPlaylistCommentsRequest(parent); break;
        case MusicAbstractQueryRequest::QueryServer::KW: request = new MusicKWPlaylistCommentsRequest(parent); break;
        case MusicAbstractQueryRequest::QueryServer::KG: request = new MusicKGPlaylistCommentsRequest(parent); break;
        default: request = new MusicWYPlaylistCommentsRequest(parent);
    }
    return request;
}

MusicDiscoverListRequest *MusicDownLoadQueryFactory::makeDiscoverListRequest(QObject *parent)
{
    MusicDiscoverListRequest *request = nullptr;
    const int index = G_SETTING_PTR->value(MusicSettingManager::DownloadServerIndex).toInt();
    switch(TTKStaticCast(MusicAbstractQueryRequest::QueryServer, index))
    {
        case MusicAbstractQueryRequest::QueryServer::WY: request = new MusicWYDiscoverListRequest(parent); break;
        case MusicAbstractQueryRequest::QueryServer::KW: request = new MusicKWDiscoverListRequest(parent); break;
        case MusicAbstractQueryRequest::QueryServer::KG: request = new MusicKGDiscoverListRequest(parent); break;
        default: request = new MusicWYDiscoverListRequest(parent);
    }
    return request;
}

MusicTranslationRequest *MusicDownLoadQueryFactory::makeTranslationRequest(const QString &data, QObject *parent)
{
    return (new MusicTranslationRequest(data, parent));
}

MusicAbstractDownLoadRequest *MusicDownLoadQueryFactory::makeLrcRequest(const QString &url, const QString &path, QObject *parent)
{
    const int index = G_SETTING_PTR->value(MusicSettingManager::DownloadServerIndex).toInt();
    switch(TTKStaticCast(MusicAbstractQueryRequest::QueryServer, index))
    {
        case MusicAbstractQueryRequest::QueryServer::WY: return (new MusicWYDownLoadTextRequest(url, path, parent));
        case MusicAbstractQueryRequest::QueryServer::KW: return (new MusicKWDownLoadTextRequest(url, path, parent));
        case MusicAbstractQueryRequest::QueryServer::KG: return (new MusicDownLoadTextRequest(url, path, parent));
        default: break;
    }
    return (new MusicDownLoadTextRequest(url, path, parent));
}

MusicAbstractDownLoadRequest *MusicDownLoadQueryFactory::makeCoverRequest(const QString &url, const QString &path, QObject *parent)
{
    const int index = G_SETTING_PTR->value(MusicSettingManager::DownloadServerIndex).toInt();
    switch(TTKStaticCast(MusicAbstractQueryRequest::QueryServer, index))
    {
        case MusicAbstractQueryRequest::QueryServer::WY: return (new MusicDownloadDataRequest(url, path, TTK::Download::Cover, parent));
        case MusicAbstractQueryRequest::QueryServer::KW: return (new MusicKWDownLoadCoverRequest(url, path, parent));
        case MusicAbstractQueryRequest::QueryServer::KG: return (new MusicDownloadDataRequest(url, path, TTK::Download::Cover, parent));
        default: break;
    }
    return (new MusicDownloadDataRequest(url, path, TTK::Download::Cover, parent));
}

MusicDownloadBackgroundRequest *MusicDownLoadQueryFactory::makeBackgroundRequest(const QString &name, const QString &path, QObject *parent)
{
    return (new MusicDownloadBackgroundRequest(name, path, parent));
}
