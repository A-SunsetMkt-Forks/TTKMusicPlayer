#include "musicvideoqualitypopwidget.h"
#include "musicvideouiobject.h"
#include "musicvideosearchtablewidget.h"
#include "musicconnectionpool.h"

MusicVideoQualityPopWidget::MusicVideoQualityPopWidget(QWidget *parent)
    : MusicToolMenuWidget(parent)
{
    initialize();

    setFixedSize(44, 20);
    setStyleSheet(TTK::UI::VideoBtnSDMode);

    G_CONNECTION_PTR->setValue(className(), this);
    G_CONNECTION_PTR->connect(className(), MusicVideoSearchTableWidget::className());
}

MusicVideoQualityPopWidget::~MusicVideoQualityPopWidget()
{
    G_CONNECTION_PTR->removeValue(this);
    delete m_actionGroup;
}

void MusicVideoQualityPopWidget::setQualityActionState()
{
    QList<QAction*> actions = m_actionGroup->actions();
    if(actions.count() >= 4)
    {
        actions[0]->setEnabled(findExistByBitrate(MB_250));
        actions[1]->setEnabled(findExistByBitrate(MB_500));
        actions[2]->setEnabled(findExistByBitrate(MB_750));
        actions[3]->setEnabled(findExistByBitrate(MB_1000));
    }
}

void MusicVideoQualityPopWidget::setQualityText(const QString &url)
{
    QString style = TTK::UI::VideoBtnSDMode;
    switch(findMVBitrateByUrl(url))
    {
        case MB_250: style = TTK::UI::VideoBtnSTMode; break;
        case MB_500: style = TTK::UI::VideoBtnSDMode; break;
        case MB_750: style = TTK::UI::VideoBtnHDMode; break;
        case MB_1000: style = TTK::UI::VideoBtnSQMode; break;
        default: break;
    }
    setStyleSheet(style);
}

void MusicVideoQualityPopWidget::movieQualityChoiced(QAction *action)
{
    QString url;
    switch(TTKStaticCast(TTK::QueryQuality, action->data().toInt()))
    {
        case TTK::QueryQuality::None: url = findMVUrlByBitrate(MB_250); break;
        case TTK::QueryQuality::Standard: url = findMVUrlByBitrate(MB_500); break;
        case TTK::QueryQuality::High: url = findMVUrlByBitrate(MB_750); break;
        case TTK::QueryQuality::Super: url = findMVUrlByBitrate(MB_1000); break;
        default: break;
    }

    setQualityText(url);
    Q_EMIT mediaUrlChanged(url);
}

void MusicVideoQualityPopWidget::initialize()
{
    setTranslucentBackground();
    m_actionGroup = new QActionGroup(this);
    connect(m_actionGroup, SIGNAL(triggered(QAction*)), SLOT(movieQualityChoiced(QAction*)));

    m_containWidget->setFixedSize(140, 125);
    m_menu->removeAction(m_menu->actions().front());
    m_actionGroup->addAction(m_menu->addAction(tr("ST")))->setData(TTKStaticCast(int, TTK::QueryQuality::None));
    m_actionGroup->addAction(m_menu->addAction(tr("SD")))->setData(TTKStaticCast(int, TTK::QueryQuality::Standard));
    m_actionGroup->addAction(m_menu->addAction(tr("HD")))->setData(TTKStaticCast(int, TTK::QueryQuality::High));
    m_actionGroup->addAction(m_menu->addAction(tr("SQ")))->setData(TTKStaticCast(int, TTK::QueryQuality::Super));

    setQualityActionState();
}

QString MusicVideoQualityPopWidget::findMVUrlByBitrate(int bitrate)
{
    TTK::MusicSongPropertyList props;
    Q_EMIT queryMusicMediaInfo(props);

    for(const TTK::MusicSongProperty &prop : qAsConst(props))
    {
        if(prop.m_bitrate == bitrate)
        {
            return prop.m_url;
        }
    }
    return QString();
}

int MusicVideoQualityPopWidget::findMVBitrateByUrl(const QString &url)
{
    TTK::MusicSongPropertyList props;
    Q_EMIT queryMusicMediaInfo(props);

    for(const TTK::MusicSongProperty &prop : qAsConst(props))
    {
        const QString &aurl = prop.m_url;
        if(aurl == url)
        {
            return prop.m_bitrate;
        }
    }
    return 0;
}

bool MusicVideoQualityPopWidget::findExistByBitrate(int bitrate)
{
    TTK::MusicSongPropertyList props;
    Q_EMIT queryMusicMediaInfo(props);

    for(const TTK::MusicSongProperty &prop : qAsConst(props))
    {
        if(prop.m_bitrate == bitrate)
        {
            return true;
        }
    }
    return false;
}
