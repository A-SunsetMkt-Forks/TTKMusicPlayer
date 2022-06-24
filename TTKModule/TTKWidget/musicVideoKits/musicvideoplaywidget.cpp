#include "musicvideoplaywidget.h"
#include "musicvideoview.h"
#include "musicitemsearchedit.h"
#include "musicvideofloatwidget.h"
#include "musicsongsharingwidget.h"
#include "musicfunctionuiobject.h"
#include "musictinyuiobject.h"
#include "musicsettingmanager.h"
#include "musicapplication.h"
#include "ttkdesktopwrapper.h"

#include <QParallelAnimationGroup>

#define WINDOW_HEIGHT   508
#define WINDOW_WIDTH    678

MusicVideoPlayWidget::MusicVideoPlayWidget(QWidget *parent)
    : MusicAbstractMoveWidget(false, parent)
{
    setWindowTitle(tr("TTKMovie"));

    m_leaverTimer = new QTimer(this);
    m_leaverTimer->setInterval(4 * MT_S2MS);
    m_leaverTimer->setSingleShot(true);
    connect(m_leaverTimer, SIGNAL(timeout()), SLOT(leaveTimeout()));

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    m_topWidget = new QWidget(this);
    m_topWidget->setStyleSheet(MusicUIObject::MQSSBackgroundStyle06 + MusicUIObject::MQSSBorderStyle01);

    QHBoxLayout *topLayout = new QHBoxLayout(m_topWidget);
    topLayout->setContentsMargins(9, 4, 9, 4);

    m_textLabel = new QLabel(m_topWidget);
    m_textLabel->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    m_textLabel->setStyleSheet(MusicUIObject::MQSSColorStyle01);

    m_searchEdit = new MusicItemQueryEdit(m_topWidget);
    m_searchEdit->setFixedHeight(25);

    topLayout->addWidget(m_textLabel);
    topLayout->addStretch();
    topLayout->addWidget(m_searchEdit);

    m_closeButton = new QPushButton(this);
    m_closeButton->setToolTip(tr("Close"));
    m_closeButton->setFixedSize(14, 14);
    m_closeButton->setStyleSheet(MusicUIObject::MQSSBtnPClose);
    m_closeButton->setCursor(QCursor(Qt::PointingHandCursor));
    connect(m_closeButton, SIGNAL(clicked()), parent, SLOT(musicVideoClosed()));
    topLayout->addWidget(m_closeButton);
    m_topWidget->setLayout(topLayout);

#ifdef Q_OS_UNIX
    m_closeButton->setFocusPolicy(Qt::NoFocus);
#endif

    m_stackedWidget = new QStackedWidget(this);
    m_stackedWidget->setStyleSheet(MusicUIObject::MQSSBorderStyle01);

    QWidget *topMaskWidget = new QWidget(this);
    topMaskWidget->setFixedHeight(35);
    topMaskWidget->setStyleSheet(MusicUIObject::MQSSBackgroundStyle02);

    layout->addWidget(topMaskWidget);
    layout->addWidget(m_stackedWidget);
    setLayout(layout);

    m_searchEdit->hide();
    m_backButton = nullptr;
    m_topWidget->raise();

    m_videoFloatWidget = new MusicVideoFloatWidget(this);
    m_videoTable = new MusicVideoSearchTableWidget(this);
    m_videoView = new MusicVideoView(this);

    m_stackedWidget->addWidget(m_videoView);
    m_stackedWidget->addWidget(m_videoTable);
    m_stackedWidget->setCurrentIndex(VIDEO_WINDOW_INDEX_0);

    m_leaverAnimation = new QParallelAnimationGroup(this);
    QPropertyAnimation *topAnimation = new QPropertyAnimation(m_topWidget, "pos", m_leaverAnimation);
    topAnimation->setDuration(MT_S2MS / 2);
    QPropertyAnimation *ctrlAnimation = new QPropertyAnimation(m_videoView->controlBarWidget(), "pos", m_leaverAnimation);
    ctrlAnimation->setDuration(MT_S2MS / 2);
    m_leaverAnimation->addAnimation(topAnimation);
    m_leaverAnimation->addAnimation(ctrlAnimation);

    connect(m_videoTable, SIGNAL(mediaUrlPathChanged(MusicVideoItem)), SLOT(mediaUrlPathChanged(MusicVideoItem)));
    connect(m_videoTable, SIGNAL(restartSearchQuery(QString)), SLOT(videoResearchButtonSearched(QString)));
    connect(m_searchEdit, SIGNAL(clicked()), SLOT(searchButtonClicked()));
    connect(m_searchEdit->editor(), SIGNAL(enterFinished(QString)), SLOT(videoResearchButtonSearched(QString)));

    connect(m_videoFloatWidget, SIGNAL(searchButtonClicked()), SLOT(switchToSearchTable()));
    connect(m_videoFloatWidget, SIGNAL(popupButtonClicked()), SLOT(popupButtonClicked()));
    connect(m_videoFloatWidget, SIGNAL(fullscreenButtonClicked()), SLOT(fullscreenButtonClicked()));
    connect(m_videoFloatWidget, SIGNAL(downloadButtonClicked()), SLOT(downloadButtonClicked()));
    connect(m_videoFloatWidget, SIGNAL(shareButtonClicked()), SLOT(shareButtonClicked()));

    connect(m_videoView, SIGNAL(searchButtonClicked()), SLOT(switchToSearchTable()));
    connect(m_videoView, SIGNAL(popupButtonClicked()), SLOT(popupButtonClicked()));
    connect(m_videoView, SIGNAL(fullscreenButtonClicked()), SLOT(fullscreenButtonClicked()));
    connect(m_videoView, SIGNAL(downloadButtonClicked()), SLOT(downloadButtonClicked()));
    connect(m_videoView, SIGNAL(shareButtonClicked()), SLOT(shareButtonClicked()));
}

MusicVideoPlayWidget::~MusicVideoPlayWidget()
{
    delete m_leaverTimer;
    delete m_leaverAnimation;
    delete m_closeButton;
    delete m_textLabel;
    delete m_searchEdit;
    delete m_backButton;
    delete m_videoView;
    delete m_stackedWidget;
}

void MusicVideoPlayWidget::popupMode(bool popup)
{
    m_videoFloatWidget->popupMode(popup);
    blockMoveOption(!popup);

    if(popup)
    {
        const QSize &size = G_SETTING_PTR->value(MusicSettingManager::ScreenSize).toSize();
        setGeometry((size.width() - WINDOW_WIDTH) / 2, (size.height() - WINDOW_HEIGHT) / 2, WINDOW_WIDTH, WINDOW_HEIGHT);
        resizeWindow(0, 0);
        setParent(nullptr);
        show();
    }
    else
    {
#ifdef Q_OS_UNIX
        if(isFullScreen())
        {
            showNormal();
        }
#endif
        m_videoFloatWidget->fullscreenMode(false);
    }
}

bool MusicVideoPlayWidget::isPopupMode() const
{
    return !m_moveOption;
}

void MusicVideoPlayWidget::resizeWindow()
{
    const int width = G_SETTING_PTR->value(MusicSettingManager::WidgetSize).toSize().width();
    const int height = G_SETTING_PTR->value(MusicSettingManager::WidgetSize).toSize().height();

    if(!isFullScreen())
    {
#ifdef Q_OS_UNIX
        const bool v = isPopupMode();
        resizeWindow(v ? (this->width() - 680) : (width - WINDOW_WIDTH_MIN), v ? (this->height() - 508) : (height - WINDOW_HEIGHT_MIN));
#else
        resizeWindow(width - WINDOW_WIDTH_MIN, height - WINDOW_HEIGHT_MIN);
#endif
    }
}

void MusicVideoPlayWidget::resizeWindow(bool resize)
{
    if(resize)
    {
        showFullScreen();
    }
    else
    {
        showNormal();
        setGeometry(250, 150, WINDOW_WIDTH, WINDOW_HEIGHT);
    }

    QSize s = size();
#ifdef Q_OS_UNIX
    const QRect &rect = TTKDesktopWrapper::screenGeometry();
    if(isFullScreen() && !rect.isNull())
    {
        s = rect.size();
    }
    else
    {
        s = QSize(WINDOW_WIDTH, WINDOW_HEIGHT);
        showNormal();
    }
#endif
    resizeWindow(s.width() - WINDOW_WIDTH, s.height() - WINDOW_HEIGHT);
}

void MusicVideoPlayWidget::resizeWindow(int width, int height)
{
    m_topWidget->setGeometry(0, 0, 680 + width, 35);
    m_videoView->resizeWindow(width, height);
    m_videoTable->resizeWindow(width);
    m_videoFloatWidget->resizeWindow(width, height);
}

QString MusicVideoPlayWidget::searchText() const
{
    return m_searchEdit->editor()->text().trimmed();
}

void MusicVideoPlayWidget::switchToSearchTable()
{
    QHBoxLayout *topLayout = TTKStatic_cast(QHBoxLayout*, m_topWidget->layout());
    delete m_backButton;
    m_backButton = new QToolButton(m_topWidget);
    m_backButton->setFixedSize(20, 20);
    m_backButton->setToolTip(tr("Back"));
    m_backButton->setCursor(QCursor(Qt::PointingHandCursor));
    m_backButton->setStyleSheet(MusicUIObject::MQSSBtnBackBack);
    connect(m_backButton, SIGNAL(clicked()), SLOT(switchToPlayView()));
    topLayout->insertWidget(0, m_backButton);

    m_textLabel->clear();
    m_searchEdit->show();
    m_stackedWidget->setCurrentIndex(VIDEO_WINDOW_INDEX_1);
}

void MusicVideoPlayWidget::switchToPlayView()
{
    delete m_backButton;
    m_backButton = nullptr;

    setTitleText(m_videoItem.m_name);
    m_searchEdit->hide();
    m_stackedWidget->setCurrentIndex(VIDEO_WINDOW_INDEX_0);
}

void MusicVideoPlayWidget::searchButtonClicked()
{
    videoResearchButtonSearched(searchText());
}

void MusicVideoPlayWidget::videoResearchButtonSearched(const QString &name)
{
    switchToSearchTable();
    m_searchEdit->editor()->setText(name);
    m_videoTable->startSearchQuery(name);
}

void MusicVideoPlayWidget::videoResearchButtonSearched(const QVariant &data)
{
    m_videoTable->startSearchSingleQuery(data);
    const MusicObject::MusicSongInformation info(data.value<MusicObject::MusicSongInformation>());
    const MusicObject::MusicSongPropertyList &props = info.m_songProps;
    if(!props.isEmpty())
    {
        const MusicObject::MusicSongProperty &prop = props.front();
        MusicVideoItem data;
        data.m_name = info.m_singerName + " - " + info.m_songName;
        data.m_url = prop.m_url;
        data.m_id = info.m_songId;
        data.m_server = MUSIC_MOVIE_RADIO;
        mediaUrlPathChanged(data);
    }
}

void MusicVideoPlayWidget::startSearchSingleQuery(const QString &name)
{
    switchToSearchTable();
    m_videoTable->startSearchSingleQuery(name);
}

void MusicVideoPlayWidget::mediaUrlChanged(const QString &url)
{
    if(url.isEmpty())
    {
        return;
    }

    MusicApplication *w = MusicApplication::instance();
    if(w->isPlaying())
    {
        w->musicStatePlay();
    }
    ///stop current media play while mv starts.
    m_videoView->setMedia(url);
    m_videoView->play();

    switchToPlayView();
}

void MusicVideoPlayWidget::mediaUrlPathChanged(const MusicVideoItem &item)
{
    m_videoItem = item;
    setTitleText(item.m_name);
    mediaUrlChanged(item.m_url);
}

void MusicVideoPlayWidget::popupButtonClicked()
{
    Q_EMIT popupButtonClicked(!m_videoFloatWidget->isPopupMode());
}

void MusicVideoPlayWidget::fullscreenButtonClicked()
{
    if(!m_videoFloatWidget->isPopupMode())
    {
        return;
    }

    const bool full = !m_videoFloatWidget->isFullscreenMode();
    m_videoFloatWidget->fullscreenMode(full);
    Q_EMIT fullscreenButtonClicked(full);
}

void MusicVideoPlayWidget::downloadButtonClicked()
{
    m_videoTable->downloadLocalFromControl();
}

void MusicVideoPlayWidget::shareButtonClicked()
{
    const QString &name = m_videoItem.m_name.trimmed();
    const QString &id = m_videoItem.m_id.trimmed();
    if(name.isEmpty() || id.isEmpty())
    {
        return;
    }

    QVariantMap data;
    data["id"] = id;
    data["songName"] = name;
    data["queryServer"] = m_videoItem.m_server;

    MusicSongSharingWidget shareWidget(this);
    shareWidget.setData(MusicSongSharingWidget::Movie, data);
    shareWidget.exec();
}

void MusicVideoPlayWidget::leaveTimeout()
{
    QWidget *w(m_videoView->controlBarWidget());
    if(w->y() != height())
    {
        const int topHeight = (m_stackedWidget->currentIndex() == 1) ? 0 : -m_topWidget->height();
        start(0, topHeight, height() - w->height() - m_topWidget->height(), height());
    }
}

void MusicVideoPlayWidget::resizeEvent(QResizeEvent *event)
{
    MusicAbstractMoveWidget::resizeEvent(event);
    resizeWindow();

    m_leaverTimer->stop();
    m_leaverAnimation->stop();
}

void MusicVideoPlayWidget::enterEvent(QtEnterEvent *event)
{
    MusicAbstractMoveWidget::enterEvent(event);
    m_leaverTimer->stop();

    QWidget *w(m_videoView->controlBarWidget());
    if(w->y() >= height())
    {
        const int topHeight = (m_stackedWidget->currentIndex() == 1) ? 0 : -m_topWidget->height();
        start(topHeight, 0, height(), height() - w->height() - m_topWidget->height());
    }
}

void MusicVideoPlayWidget::leaveEvent(QEvent *event)
{
    MusicAbstractMoveWidget::leaveEvent(event);
    m_leaverTimer->start();
}

void MusicVideoPlayWidget::setTitleText(const QString &text)
{
    m_textLabel->setText(MusicUtils::Widget::elidedText(font(), text, Qt::ElideRight, width() - 50));
}

void MusicVideoPlayWidget::start(int st, int end, int ctrlst, int ctrlend)
{
    m_leaverAnimation->stop();
    QPropertyAnimation *animation = TTKStatic_cast(QPropertyAnimation*, m_leaverAnimation->animationAt(0));
    animation->setStartValue(QPoint(0, st));
    animation->setEndValue(QPoint(0, end));
                        animation = TTKStatic_cast(QPropertyAnimation*, m_leaverAnimation->animationAt(1));
    animation->setStartValue(QPoint(0, ctrlst));
    animation->setEndValue(QPoint(0, ctrlend));
    m_leaverAnimation->start();
}
